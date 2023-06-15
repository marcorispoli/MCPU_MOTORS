#include "application.h"
#include "pd4.h"


bool pd4Nanotec::activateInitialization(void){
    if(!pCan){
        qDebug() << "activateInitialization: NO PCAN POINTER AVAILABLE";
        return false;
    }
    if(device_workflow == _WORKFLOW_NOT_CONNECTED){
        qDebug() << "activateInitialization: DEVICE NOT CONNECTED";
        return false;
    }
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

    ushort delay;
    uint index;



    switch((_workflowInitialize_t) workflow_steps){
    case _WF_INITIALIZE_INIT:
        deviceInitialized = false;
        qDebug() << "DEVICE (" << deviceId << ") INITIALIZATION";
        workflow_steps = _WF_INITIALIZE_READ_USER_PARAM;
        readSDO(RESET_USER_PARAM,10); // Read the reset user parameter
        return 5;

    case _WF_INITIALIZE_READ_USER_PARAM:

        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << "DEVICE (" << deviceId << ") ERROR READING THE USER PARAM";
            break;
        }        

        // If the device results in reset status restart the INIT workflow
        if((sdoRxTx.rxSDO.getVal() == RESET_CODE) || (sdoRxTx.rxSDO.getVal() == 0)){
           workflow_steps = _WF_INITIALIZE_NANOJ_UPLOAD_INIT;
        }else{
           workflow_steps = _WF_INITIALIZE_COMPLETED;
        }
        return 1;

    case _WF_INITIALIZE_NANOJ_UPLOAD_INIT:
        qDebug() << "VERIFY UPLOAD NANOJ";
        if(!nanojStr.vector){
            nanojUploaded = true;
            workflow_steps = _WF_INITIALIZE_CONFIG_VECTOR_INIT;
            return 1;
        }

        qDebug() << "DEVICE (" << deviceId << ") UPLOADING NANOJ PROGRAM";
        workflow_steps = _WF_INITIALIZE_NANOJ_UPLOAD_LOOP;


    case _WF_INITIALIZE_NANOJ_UPLOAD_LOOP:
        delay = subNanojProgramUpload(false);
        if(delay) return delay;

        if(!nanojUploaded){
            qDebug() << "DEVICE (" << deviceId << ") UPLOADING NANOJ FAILED";
            break;
        }

        workflow_steps = _WF_INITIALIZE_CONFIG_VECTOR_INIT;
        return 1;

    case _WF_INITIALIZE_CONFIG_VECTOR_INIT:
        qDebug() << "VERIFY UPLOAD CONFIG VECTOR";
        if(registerVectors.configVector == nullptr){
            workflow_steps = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
            return 1;
        }

        // Calc the checksum of the vector to evaluate the reload in memory
        qDebug() << "UPLOAD CONFIG VECTOR";
        index = 0;
        chk = 0;
        while(1){
            if(registerVectors.configVector[index++].type == 0) break;
            chk += (ushort) registerVectors.configVector[index].val;
        }

        readSDO(CONFIG_USER_PARAM,5);
        workflow_steps =_WF_INITIALIZE_CONFIG_VECTOR_1;
        return 5;

    case  _WF_INITIALIZE_CONFIG_VECTOR_1:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED DATA READING, ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        // Already uploaded
        if(sdoRxTx.rxSDO.getVal() == chk){
            changed = false;
            workflow_steps = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
            return 1;
        }

        changed = true;
        writeSDO(CONFIG_USER_PARAM,chk);
        workflow_steps = _WF_INITIALIZE_CONFIG_VECTOR_2;
        return 100;

    case _WF_INITIALIZE_CONFIG_VECTOR_2:
        delay = subRoutineUploadVector(registerVectors.configVector, nullptr, &success);
        if(delay) return delay;

        if(!success){
            qDebug() << "DEVICE (" << deviceId << "): FAILED UPLOADING CONFIG VECTOR!";
            break;
        }
        workflow_steps = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT;
        return 1;

    case _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_INIT:
        qDebug() << "VERIFY UPLOAD RUNTIME VECTOR";
        if(registerVectors.runtimeVector == nullptr){
            workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT;
            return 1;
        }
        qDebug() << "UPLOAD RUNTIME VECTOR";
        workflow_steps = _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_1;
        return 1;

    case _WF_INITIALIZE_CONFIG_RUNTIME_VECTOR_1:
        delay = subRoutineUploadVector(registerVectors.runtimeVector, nullptr, &success);
        if(delay) return delay;

        if(!success){
            qDebug() << "DEVICE (" << deviceId << "): FAILED UPLOADING RUNTIME VECTOR!";
            break;
        }

        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT;
        return 1;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_INIT:
        qDebug() << "VERIFY PARAM STORE";
        if(!changed){
            workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_9;
            return 1;
        }
        qDebug() << "VERIFY PARAM STORING..";

        writeSDO(RESET_USER_PARAM, RESET_CODE); // Reset the user Param Reset Flag
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_1;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_1:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        // Stores the Object Dictionary parameters
        writeSDO(OD_1010_01, OD_SAVE_CODE);
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_2;
        return 1000;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_2:
        readSDO(OD_1010_01);
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_4;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_4:
        if(!sdoRxTx.sdo_rx_ok){
            qDebug() << QString("DEVICE (%1): FAILED WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        if(sdoRxTx.rxSDO.getVal() != 1){
            workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_2;
            return 100;
        }

        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_5;
        return 1;


    case _WF_INITIALIZE_VERIFY_PARAM_STORE_5:
        writeSDO(SAVE_USER_PARAM, 1);
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_6;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_6:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR STORING THE USER PARAMETERS").arg(deviceId);
            break;
        }

        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_7;
        return 1;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_7:
        readSDO(SAVE_USER_PARAM);
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_8;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_8:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING THE USER PARAM CONTROL REGISTER").arg(deviceId);
            break;
        }

        if(sdoRxTx.rxSDO.getVal()!=0){
            workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_7;
            return 100;
        }

        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_9;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_9:
        writeSDO(RESET_USER_PARAM, 1); // Set to 1 the Reset Flag
        workflow_steps = _WF_INITIALIZE_VERIFY_PARAM_STORE_10;
        return 5;

    case _WF_INITIALIZE_VERIFY_PARAM_STORE_10:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING THE USER PARAM CONTROL REGISTER").arg(deviceId);
            break;
        }

        qDebug() << "DEVICE (" << deviceId << "): INITIALIZATION COMPLETED " << sdoRxTx.rxSDO.getVal();
        workflow_steps = _WF_INITIALIZE_COMPLETED;
        return 1;


    case _WF_INITIALIZE_COMPLETED:
        qDebug() << "DEVICE (" << deviceId << ") INITIALIZED";
        deviceInitialized = true;        
        break;
    }

    workflow_steps = _WF_INITIALIZE_INIT;
    initializationCompleted(deviceInitialized);
    return 0;
}
