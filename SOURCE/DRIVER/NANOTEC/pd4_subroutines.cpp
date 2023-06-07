#include "application.h"
#include "pd4.h"


ushort pd4Nanotec::subRoutineUploadVector(_OD_InitVector* pVector, bool* changed, bool* uploadOk){
    static ushort i;
    static ushort fase = 0;

    switch(fase){
    case 0:
        if(pVector == nullptr) {
            if(changed) *changed = false;
            if(uploadOk) *uploadOk = true;
            break;
        }

        i=0;
        fase++;
        return 1;

    case 1:
        readSDO(pVector[i].index, pVector[i].subidx, pVector[i].type);
        fase++;
        return 5;

    case 2:
        if(!sdoRxTx.sdo_rx_ok){
            if(uploadOk) *uploadOk = false;
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(pVector[i].index,1,16).arg(pVector[i].subidx);
            break;
        }

        if(sdoRxTx.rxSDO.getVal() == sdoRxTx.rxSDO.formatVal(pVector[i].val)){
            fase = 5;
            return 1;
        }

        if(changed) *changed = true;
        fase++;
        return 1;

    case 3:
        writeSDO(pVector[i].index, pVector[i].subidx, pVector[i].type, pVector[i].val);
        fase++;
        return 5;

    case 4:
        if(!sdoRxTx.sdo_rx_ok){
            if(uploadOk) *uploadOk = false;
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(pVector[i].index,1,16).arg(pVector[i].subidx);
            break;
        }

        fase++;
        return 1;

    case 5:
        i++;
        if(pVector[i].type == 0){
            if(uploadOk) *uploadOk = true;
            break;
        }

        fase = 1;
        return 1;

    default:
        if(uploadOk) *uploadOk = false;
        qDebug() << QString("DEVICE (%1): INVALID wSubStatus = %2").arg(deviceId).arg(fase);
        break;

    }

    fase =0;
    return 0;
}


ushort pd4Nanotec::subRoutineWriteRegisterList(QList<canOpenDictionary>* pOdList, bool* uploadOk){
    static ushort i;
    static ushort wSubStatus = 0;

    canOpenDictionary od;
    switch(wSubStatus){
    case 0:
        if(pOdList == nullptr) {
            if(uploadOk) *uploadOk = true;
            wSubStatus = 0;
            break;
        }

        i=0;
        wSubStatus++;
        return 1;

    case 1:
        writeSDO(pOdList->at(i));
        wSubStatus++;
        return 5;

    case 2:
        if(!sdoRxTx.sdo_rx_ok){
            if(uploadOk) *uploadOk = false;
            od = pOdList->at(i);
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(od.getIndex(),1,16).arg(od.getSubIndex());
            wSubStatus = 0;
            break;
        }

        wSubStatus++;
        return 1;

    case 3:
        i++;
        if(i >= pOdList->size()){
            if(uploadOk) *uploadOk = true;
            wSubStatus = 0;
            break;
        }

        wSubStatus = 1;
        return 1;

    default:
        if(uploadOk) *uploadOk = false;
        qDebug() << QString("DEVICE (%1): INVALID wSubStatus = %2").arg(deviceId).arg(wSubStatus);
        wSubStatus = 0;
        break;
    }

    wSubStatus =0;
    return 0;
}

ushort pd4Nanotec::subReadDigitalInputs(void){

    static ushort wSubStatus = 0;


    switch(wSubStatus){
    case 0:
        readSDO(OD_3240_05); // Reads the digital inputs
        wSubStatus++;
        return 5;

    case 1:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            digital_input_valid = false;
            wSubStatus = 0;
            break;
        }

        digital_input_valid = true;
        digital_input_val =  sdoRxTx.rxSDO.getVal();
        wSubStatus = 0;
        break;
    }

    wSubStatus =0;
    return 0;
}

ushort pd4Nanotec::subDisableNanojProgram(void){
    static ushort wSubStatus = 0;


    switch(wSubStatus){
    case 0:
        writeSDO(OD_2300_00, 0); // Disable the Nanoj program
        wSubStatus++;
        return 5;

    case 1:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            wSubStatus = 0;
            break;
        }

    case 2:
        readSDO(OD_2301_00); // Read the Nanoj Status register
        wSubStatus++;
        return 5;

    case 3:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            wSubStatus = 0;
            break;
        }

        if(sdoRxTx.rxSDO.getVal() & 0x1 ){
             qDebug() << QString("DEVICE (%1): ERROR STOPPING THE NANOJ  PROGRAM").arg(deviceId);
             wSubStatus = 0;
             break;
        }

        qDebug() << QString("DEVICE (%1): NANOJ  PROGRAM STOPPED").arg(deviceId);
        nanojStr.nanoj_program_started = false;
        wSubStatus = 0;
        break;
    }

    wSubStatus =0;
    return 0;
}

ushort pd4Nanotec::subReadPositionEncoder(void){
    static ushort wSubStatus = 0;


    switch(wSubStatus){
    case 0:
        readSDO(OD_6064_00); // Reads the Encoder value
        wSubStatus++;
        return 5;

    case 1:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            wSubStatus = 0;
            break;
        }

        position_encoder_val =  sdoRxTx.rxSDO.getVal();
        wSubStatus = 0;
        break;
    }

    wSubStatus =0;
    return 0;
}

ushort pd4Nanotec::subActivateQuickStopCommand(void){
    ushort ctrlw;
    static ushort wSubStatus = 0;

    switch(wSubStatus){
    case 0:
        readSDO(OD_6040_00); // Reads the control word
        wSubStatus++;
        return 5;

    case 1:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            wSubStatus = 0;
            break;
        }

        wSubStatus++;
        return 1;

    case 2:

        ctrlw = sdoRxTx.rxSDO.getVal();
        ctrlw &=~ OD_MASK(OD_6040_00_QUICKSTOP);
        ctrlw |= OD_VAL(OD_6040_00_QUICKSTOP);
        writeSDO(OD_6040_00, ctrlw);
        wSubStatus++;
        return 5;

    case 3:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
        }

        wSubStatus = 0;
        break;
    }

    wSubStatus =0;
    return 0;
}
