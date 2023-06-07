#include "application.h"
#include "pd4.h"


bool pd4Nanotec::activateInitialization(void){
    if(!pCan) return false;
    if(device_workflow == _WORKFLOW_NOT_CONNECTED) return false;
    if(device_workflow == _WORKFLOW_INITIALIZATION) return true;
    if(request_initialization) return true;

    request_initialization = true;
    deviceInitialized = false;
    return true;
}

typedef enum{
    _WF_INITIALIZE_INIT = 0,
    _WF_INITIALIZE_READ_USER_PARAM,
    _WF_INITIALIZE_NANOJ_UPLOAD_INIT,
    _WF_INITIALIZE_NANOJ_UPLOAD_LOOP,
    _WF_INITIALIZE_CONFIG_VECTOR_INIT,
    _WF_INITIALIZE_CONFIG_VECTOR_1,
    _WF_INITIALIZE_CONFIG_VECTOR_2,
    _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT,
    _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_1,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_1,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_2,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_4,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_5,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_6,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_7,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_8,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_9,
    _WF_INITIALIZE_VERIFY_PARAM_STORE_10,
    _WF_INITIALIZE_COMPLETED,

}_workflowInitialize_t;

ushort pd4Nanotec::workflowInitializeHandler(void){
    static _workflowInitialize_t fase = _WF_INITIALIZE_INIT;
    static bool changed = false;
    static bool success = false;
    ushort delay;
    uint index;
    static unsigned short chk = 0;


    switch(fase){
    case _WF_INITIALIZE_INIT:
        deviceInitialized = false;
        qDebug() << "DEVICE (" << deviceId << ") INITIALIZATION";
        fase = _WF_INITIALIZE_READ_USER_PARAM;
        readSDO(RESET_USER_PARAM,10); // Read the reset user parameter
        return 5;

    case _WF_INITIALIZE_READ_USER_PARAM:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << "DEVICE (" << deviceId << ") ERROR READING THE USER PARAM";
            break;
        }

        // If the device results in reset status restart the INIT workflow
        if(sdoRxTx.rxSDO.getVal() == RESET_CODE){
           fase = _WF_INITIALIZE_NANOJ_UPLOAD_INIT;
        }else{
           fase = _WF_INITIALIZE_COMPLETED;
        }
        return 1;

    case _WF_INITIALIZE_NANOJ_UPLOAD_INIT:
        if(!nanojStr.vector){
            nanojUploaded = true;
            fase = _WF_INITIALIZE_CONFIG_VECTOR_INIT;
            return 1;
        }

        qDebug() << "DEVICE (" << deviceId << ") UPLOADING NANOJ PROGRAM";
        fase = _WF_INITIALIZE_NANOJ_UPLOAD_LOOP;


    case _WF_INITIALIZE_NANOJ_UPLOAD_LOOP:
        delay = subNanojProgramUpload(false);
        if(delay) return delay;

        if(!nanojUploaded){
            qDebug() << "DEVICE (" << deviceId << ") UPLOADING NANOJ FAILED";
            break;
        }

        fase = _WF_INITIALIZE_CONFIG_VECTOR_INIT;
        return 1;

    case _WF_INITIALIZE_CONFIG_VECTOR_INIT:
        if(registerVectors.configVector == nullptr){
            fase = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
            return 1;
        }

        // Calc the checksum of the vector to evaluate the reload in memory
        index = 0;
        chk = 0;
        while(1){
            if(registerVectors.configVector[index++].type == 0) break;
            chk += (ushort) registerVectors.configVector[index].val;
        }

        readSDO(CONFIG_USER_PARAM,5);
        fase =_WF_INITIALIZE_CONFIG_VECTOR_1;
        return 5;

    case  _WF_INITIALIZE_CONFIG_VECTOR_1:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED DATA READING, ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        // Already uploaded
        if(sdoRxTx.rxSDO.getVal() == chk){
            changed = false;
            fase = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
            return 1;
        }

        changed = true;
        writeSDO(CONFIG_USER_PARAM,chk);
        fase = _WF_INITIALIZE_CONFIG_VECTOR_2;
        return 100;

    case _WF_INITIALIZE_CONFIG_VECTOR_2:
        delay = subRoutineUploadVector(registerVectors.configVector, nullptr, &success);
        if(delay) return delay;

        if(!success){
            qDebug() << "DEVICE (" << deviceId << "): FAILED UPLOADING CONFIG VECTOR!";
            break;
        }
        fase = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
        return 1;

    case _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT:
        if(registerVectors.runtimeVector == nullptr){
            fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT;
            return 1;
        }

        fase = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_1;
        return 1;

    case _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_1:
        delay = subRoutineUploadVector(registerVectors.runtimeVector, nullptr, &success);
        if(delay) return delay;

        if(!success){
            qDebug() << "DEVICE (" << deviceId << "): FAILED UPLOADING RUNTIME VECTOR!";
            break;
        }

        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT;
        return 1;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT:
        if(!changed){
            fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_9;
            return 1;
        }

        writeSDO(RESET_USER_PARAM, RESET_CODE); // Reset the user Param Reset Flag
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_1;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_1:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        // Stores the Object Dictionary parameters
        writeSDO(OD_1010_01, OD_SAVE_CODE);
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_2;
        return 1000;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_2:
        readSDO(OD_1010_01);
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_4;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_4:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        if(sdoRxTx.rxSDO.getVal() != 1){
            fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_2;
            return 100;
        }

        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_5;
        return 1;


    case _WF_INITIALIZE_VERIFY_PARAM_STORE_5:
        writeSDO(SAVE_USER_PARAM, 1);
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_6;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_6:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR STORING THE USER PARAMETERS").arg(deviceId);
            break;
        }

        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_7;
        return 1;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_7:
        readSDO(SAVE_USER_PARAM);
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_8;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_8:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING THE USER PARAM CONTROL REGISTER").arg(deviceId);
            break;
        }

        if(sdoRxTx.rxSDO.getVal()!=0){
            fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_7;
            return 100;
        }

        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_9;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_9:
        writeSDO(RESET_USER_PARAM, 1); // Set to 1 the Reset Flag
        fase = _WF_INITIALIZE_VERIFY_PARAM_STORE_10;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_10:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING THE USER PARAM CONTROL REGISTER").arg(deviceId);
            break;
        }

        qDebug() << "DEVICE (" << deviceId << "): INITIALIZATION COMPLETED " << sdoRxTx.rxSDO.getVal();
        fase = _WF_INITIALIZE_COMPLETED;
        return 1;


    case _WF_INITIALIZE_COMPLETED:
        qDebug() << "DEVICE (" << deviceId << ") INITIALIZED";
        deviceInitialized = true;        
        break;
    }

    fase = _WF_INITIALIZE_INIT;
    initializationCompleted(deviceInitialized);
    return 0;
}
