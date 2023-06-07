#include "application.h"


canClient* pd4Nanotec::pCan = nullptr;

pd4Nanotec::pd4Nanotec(uchar ID)
{
    if(pCan == nullptr) pCan = new canClient(0xF80, 0x580,SYSCONFIG->getParam<QString>(SYS_CAN_PROCESS_PARAM, SYS_PROCESS_IP) , SYSCONFIG->getParam<uint>(SYS_CAN_PROCESS_PARAM, SYS_PROCESS_PORT));
    deviceId = ID;
    ready = false;

    // Activation of the communicaitone with the CAN DRIVER SERVER
    connect(pCan, SIGNAL(rxFromCan(ushort , QByteArray )), this, SLOT(rxFromCan(ushort , QByteArray )), Qt::QueuedConnection);
    connect(pCan, SIGNAL(rxAsyncFromCan(ushort , QByteArray )), this, SLOT(rxAsyncFromCan(ushort , QByteArray )), Qt::QueuedConnection);
    connect(this,SIGNAL(txToCan(ushort , QByteArray )), pCan,SLOT(txToCanData(ushort , QByteArray )), Qt::QueuedConnection);
    pCan->ConnectToCanServer();

    // invalidate the status of the digital input
    digital_input_valid = false;

    // Safety Input Mask closed
    setSafetyDigitalInput(0,0);

    registerVectors.configVector = nullptr;
    registerVectors.runtimeVector =nullptr;
    registerVectors.zeroSettingVector = nullptr;



    execCommand = _NO_COMMAND;
    CiAcurrentStatus = CiA402_Undefined;
    zero_setting_ok = false;

    positioningStr.target_ok = false;
    nanojStr.nanoj_program_started = true;
    uploadNanojRequest = false;

    enableDeviceInitialization = false;



    device_workflow = _WORKFLOW_NOT_CONNECTED;
    workflowFase = 0;
    deviceInitialized = false;

    sdoRxTx.sdo_rx_tx_pending = false;
    sdoRxTx.sdo_rx_ok = true;
    sdoRxTx.sdo_rxtx_completed = true;
    sdoRxTx.sdo_attempt = 0;
    sdoRxTx.tmo_attempt = 100;
    QTimer::singleShot(1000,this, SLOT(statusHandler()));
}
pd4Nanotec::~pd4Nanotec()
{

}




void pd4Nanotec::rxFromCan(ushort devId, QByteArray data){

    if((devId - 0x580) != deviceId) return; // Invalid ID
    sdoRxTx.sdo_rxtx_completed = true;

    if(nanojStr.rxblock){
          if( data.at(0) != ((nanojStr.txBlock.at(0)& 0xF0) | 0x20) ){
              //qDebug() << QString("errore:%1 atteso:%2").arg((uchar) data.at(0),1,16).arg((uchar)(nanojStr.txBlock.at(0) | 0x20),1,16);
              return;
          }
          sdoRxTx.sdo_rx_ok = true;
          return;
    }


    // Update the status handler
    sdoRxTx.rxSDO.set(&data);
    if(sdoRxTx.txSDO.getIndex() != sdoRxTx.rxSDO.getIndex()){
        return;
    }
    if(sdoRxTx.txSDO.getSubIndex() != sdoRxTx.rxSDO.getSubIndex()) {
        return;
    }

    // The SDO has been successfully received
    if(sdoRxTx.rxSDO.isError()){
        qDebug() << sdoRxTx.rxSDO.printError();
        return;
    }

    sdoRxTx.sdo_rx_ok = true;
    return;
}

void pd4Nanotec::rxAsyncFromCan(ushort devId, QByteArray data){

    qDebug() << "DEVICE (" << deviceId << ") RECEIVED ASYNC FRAME: " << devId << " - " << data;;
    return;
}

void pd4Nanotec::writeSDO(ushort index, uchar sub, canOpenDictionary::_ODDataType type, uint val){
    if(!pCan) return;
    sdoRxTx.txSDO.setOd(index,sub,type,val);
    sdoRxTx.rxSDO.clear();

    emit txToCan(0x600 + deviceId, sdoRxTx.txSDO.get());

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;
}

void pd4Nanotec::writeSDO(canOpenDictionary od){
    if(!pCan) return;
    sdoRxTx.txSDO.setOd(od.getIndex(),od.getSubIndex(),od.getType(),od.getVal());
    sdoRxTx.rxSDO.clear();

    emit txToCan(0x600 + deviceId, sdoRxTx.txSDO.get());

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;
}


void pd4Nanotec::readSDO(ushort index, uchar sub, uchar type, uint repeat){
    if(!pCan) return;

    sdoRxTx.txSDO.setOd(index,sub,canOpenDictionary::RD_COMMAND,0);
    sdoRxTx.rxSDO.clear();

    T1START;
    emit txToCan(0x600 + deviceId, sdoRxTx.txSDO.get());

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;
    sdoRxTx.sdo_attempt = repeat;

}

void pd4Nanotec::readSDO(canOpenDictionary od){
    if(!pCan) return;

    sdoRxTx.txSDO.setOd(od.getIndex(),od.getSubIndex(),canOpenDictionary::RD_COMMAND,0);
    sdoRxTx.rxSDO.clear();

    emit txToCan(0x600 + deviceId, sdoRxTx.txSDO.get());

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;

}

void pd4Nanotec::resetNode(void){
    if(!pCan) return;

    sdoRxTx.rxSDO.clear();

    QByteArray frame;
    frame.append(0x81);
    frame.append(deviceId);

    emit txToCan(0, frame);

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = true;
    sdoRxTx.sdo_rxtx_completed = true;
    sdoRxTx.sdo_rx_tx_pending = false;

}


void pd4Nanotec::sendAgainSDO(void){
    if(!pCan) return;

    sdoRxTx.rxSDO.clear();

    emit txToCan(0x600 + deviceId, sdoRxTx.txSDO.get());

    // Activate the timeout handler, in case no answer should be received
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;

}



void pd4Nanotec::statusHandler(void){
    ushort delay;

    // Data Reception management
    if(sdoRxTx.sdo_rx_tx_pending){
        if(!sdoRxTx.sdo_rxtx_completed){
            if(sdoRxTx.tmo_attempt){
                sdoRxTx.tmo_attempt--;
                QTimer::singleShot(1,this, SLOT(statusHandler()));
                return;
            }
            sdoRxTx.sdo_rx_ok = false;
            sdoRxTx.sdo_rxtx_completed = true;
        }
        sdoRxTx.tmo_attempt = 100; // ms of waiting the reception

        // In case of unsuccess try again for a maximum time
        if((!sdoRxTx.sdo_rx_ok) && (sdoRxTx.sdo_attempt) ){
             sdoRxTx.sdo_attempt--;
             sendAgainSDO();
             QTimer::singleShot(100,this, SLOT(statusHandler()));
             return;
        }

    }else{
        sdoRxTx.sdo_rx_ok = true;
        sdoRxTx.sdo_rxtx_completed = true;
    }
    sdoRxTx.sdo_rx_tx_pending = false;
    sdoRxTx.tmo_attempt = 100; // ms of waiting the reception

    switch(device_workflow){
        case  _WORKFLOW_NOT_CONNECTED: // Wait for the CAN-CLIENT READY CONDITION
            deviceInitialized = false;
            if((!pCan) ||(!pCan->isCanReady())){
                QTimer::singleShot(100,this, SLOT(statusHandler()));
                return;
            }

            // The CAN driver has been connected and registered
            device_workflow = _WORKFLOW_WAIT_INITIALIZATION;
            request_initialization = false;
            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;

        case  _WORKFLOW_WAIT_INITIALIZATION:
            if(request_initialization){
                device_workflow = _WORKFLOW_INITIALIZATION;
                request_initialization = false;
            }

            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;

        case  _WORKFLOW_INITIALIZATION:
            delay = workflowInitializeHandler();
            if(delay){
                QTimer::singleShot(delay,this, SLOT(statusHandler()));
                return;
            }

            if(deviceInitialized){
                device_workflow = _WORKFLOW_IDLE;
                qDebug() << "DEVICE (" << deviceId << ") SET THE IDLE ";
            }else{
                device_workflow = _WORKFLOW_WAIT_INITIALIZATION;
                qDebug() << "DEVICE (" << deviceId << ") SET THE WAIT INITIALIZATION ";

            }

            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;

        case _WORKFLOW_IDLE:
            if(request_initialization){
                device_workflow = _WORKFLOW_INITIALIZATION;
                request_initialization = false;
            }

            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;
    }

}




/*
void pd4Nanotec::statusHandler(void){
    ushort delay;
    if(!pCan) return;

    // Wait for the CANCLIENT READY CONDITION
    if(!pCan->isCanReady()){
        wStatus = 0;
        wSubStatus = 0;
        workflowStatus = 0;

        digital_input_valid = false;
        sdoRxTx.sdo_rx_tx_pending = false;
        nanojStr.rxblock = false;
        workflow = _DEVICE_STOP_MODE;
        CiAcurrentStatus = CiA402_Undefined;
        QTimer::singleShot(100,this, SLOT(statusHandler()));
        return;
    }


    // Wait any transaction completion
    if(sdoRxTx.sdo_rx_tx_pending){
        if(!sdoRxTx.sdo_rxtx_completed){
            if(sdoRxTx.tmo_attempt){
                sdoRxTx.tmo_attempt--;
                QTimer::singleShot(1,this, SLOT(statusHandler()));
                return;
            }
            sdoRxTx.sdo_rx_ok = false;
            sdoRxTx.sdo_rxtx_completed = true;
        }
        sdoRxTx.tmo_attempt = 100; // ms of waiting the reception

        // In case of unsuccess try again for a maximum time
        if((!sdoRxTx.sdo_rx_ok) && (sdoRxTx.sdo_attempt) && (!nanojStr.rxblock)){
             sdoRxTx.sdo_attempt--;
             sendAgainSDO();
             QTimer::singleShot(100,this, SLOT(statusHandler()));
             return;
        }

    }else{
        sdoRxTx.sdo_rx_ok = true;
        sdoRxTx.sdo_rxtx_completed = true;
        nanojStr.rxblock = false;
    }

    sdoRxTx.sdo_rx_tx_pending = false;
    nanojStr.rxblock = false;
    sdoRxTx.sdo_attempt = 10;
    sdoRxTx.tmo_attempt = 100;


    switch(workflow){

    case _DEVICE_STOP_MODE:
        if(workflowStatus==0){
            qDebug() << "DEVICE (" << deviceId << ") STOP MODE ACTIVE";
            workflowStatus++;
        }

        if(!stopMode){
            workflow =_DEVICE_NOT_CONNECTED;
            workflowStatus = 0;
            wStatus =0;
            wSubStatus =0;
            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;
        }

        QTimer::singleShot(100,this, SLOT(statusHandler()));
        return;

    case _DEVICE_NOT_CONNECTED:
        if(stopMode){
            workflow = _DEVICE_STOP_MODE;
            workflowStatus = 0;
            wStatus =0;
            wSubStatus =0;
            QTimer::singleShot(100,this, SLOT(statusHandler()));
            return;
        }

        switch(workflowStatus){
        case 0:
            qDebug() << "DEVICE (" << deviceId << ") NOT CONNECTED";
            digital_input_valid = false;
            workflowStatus++;

        case 1:
            readSDO(RESET_USER_PARAM); // Read the reset user parameter
            workflowStatus++;
            QTimer::singleShot(5,this, SLOT(statusHandler()));
            return;

        case 2:
            if(!sdoRxTx.sdo_rx_ok){
                workflowStatus--;
                QTimer::singleShot(1000,this, SLOT(statusHandler()));
                return ;
            }

            qDebug() << "DEVICE (" << deviceId << ") CONNECTED";
            wStatus = 0;
            wSubStatus = 0;
            workflowStatus = 0;

            // If the device results in reset status restart the INIT workflow
            if(sdoRxTx.rxSDO.getVal() == RESET_CODE){
               workflow = _DEVICE_INIT;
            }else{
               workflow = _HANDLE_DEVICE_STATUS;
            }
            QTimer::singleShot(0,this, SLOT(statusHandler()));
            return;

        default:
            workflowStatus = 1;
            QTimer::singleShot(1000,this, SLOT(statusHandler()));
            return;
        }

        return;

    case _DEVICE_INIT: // Device Initialization procedures

        switch(workflowStatus){

            case 0:
                qDebug() << "DEVICE ID(" << this->deviceId << ") WAIT INITIALIZATION ..";
                deviceInitialized = false;
                zero_setting_ok = false;
                workflowStatus++;
                QTimer::singleShot(0,this, SLOT(statusHandler()));
                return;

            case 1:
                 if(enableDeviceInitialization){
                    workflowStatus++;
                    QTimer::singleShot(0,this, SLOT(statusHandler()));
                    return;
                 }

                 QTimer::singleShot(100,this, SLOT(statusHandler()));
                 return;

            case 2:
                delay = workflowInitCallback();
                if(delay==0) {
                    wStatus = 0;
                    wSubStatus = 0;
                    workflowStatus =0;
                    delay=100;
                    enableDeviceInitialization = false;

                    // If the initialization process completes successfully, the workflow changes
                    if(deviceInitialized){
                          workflow = _HANDLE_DEVICE_STATUS;
                    }
                }

                QTimer::singleShot(delay,this, SLOT(statusHandler()));
                return;

            default:
                enableDeviceInitialization = false;
                qDebug() << "DEVICE ID(" << this->deviceId << ") WRONG INITIALIZATION STATUS";
                workflowStatus = 0;
                QTimer::singleShot(100,this, SLOT(statusHandler()));
                return;

        }  

    case _UPLOAD_NANOJ:
        if(workflowStatus == 0){
            qDebug() << "DEVICE ID(" << this->deviceId << ") UPLOAD NANOJ PROGRAM";
            workflowStatus++;
            delay = 1;
        }else{
            delay = workflowUploadNanoj();
            if(delay==0) {
                workflow = _HANDLE_DEVICE_STATUS;
                wStatus = 0;
                wSubStatus = 0;
                workflowStatus=0;
                delay=100;
            }
        }

        QTimer::singleShot(delay,this, SLOT(statusHandler()));
        return;

    case _HANDLE_DEVICE_STATUS:

        switch(workflowStatus){
        case 0:
                if(stopMode){
                    // A request to stop Mode has been received
                    workflow = _DEVICE_STOP_MODE;
                    wStatus = 0;
                    wSubStatus = 0;
                    workflowStatus = 0;
                    QTimer::singleShot(100,this, SLOT(statusHandler()));
                    return;
                }

                if(enableDeviceInitialization){
                    // A request to initialize has been received
                    workflow = _DEVICE_INIT;
                    wStatus = 0;
                    wSubStatus = 0;
                    workflowStatus = 0;
                    QTimer::singleShot(100,this, SLOT(statusHandler()));
                    return;
                }

                // Verifies if the device has been reset reading the proper User parameter
                readSDO(RESET_USER_PARAM);
                workflowStatus++;
                QTimer::singleShot(5,this, SLOT(statusHandler()));
                return;
        case 1:
            if(!sdoRxTx.sdo_rx_ok){
                workflow = _DEVICE_NOT_CONNECTED;
                wStatus = 0;
                wSubStatus = 0;
                workflowStatus =0;
                QTimer::singleShot(100,this, SLOT(statusHandler()));
                return ;
            }

            if(sdoRxTx.rxSDO.getVal() == RESET_CODE){
                workflow = _DEVICE_INIT;
                qDebug() << "DEVICE ID(" << this->deviceId << ") DEVICE HAS BEEN RESET";

                // Initialize the status workflow for the given CiA status.
                wStatus = 0;
                wSubStatus = 0;
                workflowStatus=0;
                QTimer::singleShot(0,this, SLOT(statusHandler()));
                return;
            }
            workflowStatus++;
            QTimer::singleShot(0,this, SLOT(statusHandler()));
            return;

        case 2:
            // Reads the digital inputs
            delay = subReadDigitalInputs();
            if(!delay){
                workflowStatus++;
            }
            QTimer::singleShot(delay,this, SLOT(statusHandler()));
            return;

        case 3:
            readSDO(OD_6041_00); // Read the status
            workflowStatus++;
            QTimer::singleShot(5,this, SLOT(statusHandler()));
            return;

        case 4:
            if(!sdoRxTx.sdo_rx_ok){
                workflow = _DEVICE_NOT_CONNECTED;
                wStatus = 0;
                wSubStatus = 0;
                workflowStatus=0;
                QTimer::singleShot(100,this, SLOT(statusHandler()));
                return ;
            }

            wStatus = 0;
            wSubStatus = 0;

            if( getCiAStatus(&sdoRxTx.rxSDO) != CiAcurrentStatus ) {
                CiAcurrentStatus = getCiAStatus(&sdoRxTx.rxSDO);
                qDebug() << "DEVICE ID(" << this->deviceId << ") STATUS CHANGE IN:" << getCiAStatusString(CiAcurrentStatus);
            }

            workflowStatus++;
            QTimer::singleShot(0,this, SLOT(statusHandler()));
            return;

         case 5:
                switch(CiAcurrentStatus){

                case CiA402_NotReadyToSwitchOn:
                    delay =0;
                    break;

                case CiA402_QuickStopActive:
                case CiA402_SwitchOnDisabled:
                    delay = CiA402_SwitchOnDisabledCallback();
                    break;
                case CiA402_ReadyToSwitchOn:
                    delay = CiA402_ReadyToSwitchOnCallback();
                    break;
                case CiA402_SwitchedOn:
                    if(uploadNanojRequest){
                        uploadNanojRequest = false;
                        nanojUploaded = false;
                        workflow = _UPLOAD_NANOJ;
                        wStatus = 0;
                        wSubStatus = 0;
                        workflowStatus =0;
                        QTimer::singleShot(1,this, SLOT(statusHandler()));
                        return;
                    }

                    delay = CiA402_SwitchedOnCallback();
                    break;
                case CiA402_OperationEnabled: delay = CiA402_OperationEnabledCallback(); break;
                case CiA402_Fault:
                    delay = CiA402_FaultCallback();

                    // In fault the initialization or the Stop mode shall be executed
                    if(stopMode) delay = 0;
                    if(enableDeviceInitialization) delay =0;

                    break;

                default:
                    delay = 0;
                }

                if(delay==0) {
                    workflowStatus =0;
                    wStatus = 0;
                    wSubStatus = 0;
                    delay=1;
                }

                QTimer::singleShot(delay,this, SLOT(statusHandler()));
                return;

        }

    }

    QTimer::singleShot(1,this, SLOT(statusHandler()));
}

*/

QString pd4Nanotec::getErrorClass1001(uint val){
    uchar cval = (uchar) val;
    QString errstr = "";
    if(cval & OD_1001_00_GENERAL_ERROR) errstr += "[GENERAL]";
    if(cval & OD_1001_00_I_ERROR) errstr += "[I]";
    if(cval & OD_1001_00_VOLTAGE_ERROR) errstr += "[VOLTAGE]";
    if(cval & OD_1001_00_TEMP_ERROR) errstr += "[TEMP]";
    if(cval & OD_1001_00_COM_ERROR) errstr += "[COM]";
    if(cval & OD_1001_00_PROFILE_ERROR) errstr += "[PROFILE]";
    if(cval & OD_1001_00_RESERVED_ERROR) errstr += "[RESERVED]";
    if(cval & OD_1001_00_MANUFACT_ERROR) errstr += "[MANUFACTURER]";
    return errstr;
}

QString pd4Nanotec::getErrorClass1003(uint val){
    return getErrorClass1001 (val >> 16);
}

QString pd4Nanotec::getErrorCode1003(uint val){
    ushort sval = (ushort) (val & 0xFFFF);

    switch(sval){
        case 0x1000: return "General error";
        case 0x2300: return "Current at the controller output too large";
        case 0x3100: return "Overvoltage/undervoltage at controller input";
        case 0x4200: return "Temperature error within the controller";
        case 0x6010: return "Software reset (watchdog)";
        case 0x6100: return "Internal software error, generic";
        case 0x6320: return "Rated current must be set (203Bh:01h)";
        case 0x7121: return "Motor blocked";
        case 0x7305: return "Incremental encoder or Hall sensor faulty";
        case 0x7600: return "Nonvolatile memory full or corrupt; restart the controller for cleanup work";
        case 0x8000: return "Error during fieldbus monitoring";
        case 0x8130: return "CANopen only: Life Guard error or Heartbeat error";
        case 0x8200: return "CANopen only: Slave took too long to send PDO messages.";
        case 0x8210: return "CANopen only: PDO was not processed due to a length error";
        case 0x8220: return "CANopen only: PDO length exceeded";
        case 0x8611: return "Position monitoring error: Following error too large";
        case 0x8612: return "Position monitoring error: Limit switch and tolerance zone exceeded";
        case 0x9000: return "EtherCAT: Motor running while EtherCAT changes from OP -> SafeOp, PreOP, etc.";
    }
}


pd4Nanotec::_CiA402Status pd4Nanotec::getCiAStatus(canOpenDictionary* od){
    uchar val = (uchar) (od->getVal() & 0xFF);
    if((val & 0x4F) == 0 ) return  CiA402_NotReadyToSwitchOn;
    else if((val & 0x4F) == 0x40 ) return  CiA402_SwitchOnDisabled;
    else if((val & 0x6F) == 0x21 ) return  CiA402_ReadyToSwitchOn;
    else if((val & 0x6F) == 0x23 ) return  CiA402_SwitchedOn;
    else if((val & 0x6F) == 0x27 ) return  CiA402_OperationEnabled;
    else if((val & 0x6F) == 0x7 ) return  CiA402_QuickStopActive;
    else if((val & 0x4F) == 0xF ) return  CiA402_FaultReactionActive;
    else if((val & 0x4F) == 0x8 ) return  CiA402_Fault;
    return CiA402_NotReadyToSwitchOn;
}

QString pd4Nanotec::getCiAStatusString(_CiA402Status status){
    switch(status){
        case CiA402_NotReadyToSwitchOn: return QString("CiA402_NotReadyToSwitchOn"); break;
        case CiA402_SwitchOnDisabled: return QString("CiA402_SwitchOnDisabled"); break;
        case CiA402_ReadyToSwitchOn: return QString("CiA402_ReadyToSwitchOn"); break;
        case CiA402_SwitchedOn: return QString("CiA402_SwitchedOn"); break;
        case CiA402_OperationEnabled: return QString("CiA402_OperationEnabled"); break;
        case CiA402_QuickStopActive: return QString("CiA402_QuickStopActive"); break;
        case CiA402_FaultReactionActive: return QString("CiA402_FaultReactionActive"); break;
        case CiA402_Fault: return QString("CiA402_Fault"); break;
    }
}


void pd4Nanotec::setConfigVector(_OD_InitVector* p){
    registerVectors.configVector = p;
}
void pd4Nanotec::setRuntimeVector(_OD_InitVector* p){
    registerVectors.runtimeVector = p;
}

void pd4Nanotec::setZerosettingVector(_OD_InitVector* p){
    registerVectors.zeroSettingVector = p;
}

void pd4Nanotec::setMotorConfig(float gearratio, float speed_denominator){
    this->motorConfig.gearratio = gearratio;
    this->motorConfig.speed_denominator = speed_denominator;
}


void pd4Nanotec::setSafetyDigitalInput(uchar mask, uchar val){
    safety.digital_input_mask = mask;
    safety.digital_input_val = val;
};

bool pd4Nanotec::isSafetyDigitalInputOn(){
    if(!digital_input_valid ) return false;
    if(!safety.digital_input_mask) return false;
    return ( (digital_input_val & safety.digital_input_mask) == (safety.digital_input_val & safety.digital_input_mask));
}

uchar pd4Nanotec::getDigitalInputs(void){
    return (uchar) digital_input_val;
}

void pd4Nanotec::enableConfiguration(void){
    enableDeviceInitialization = true;

}

void pd4Nanotec::immediateStop(void){
    safety.immediate_stop_command = true;
}
void pd4Nanotec::quickStop(void){
    safety.quick_stop_command = true;
}

uint   pd4Nanotec::convert_cGRADsec_TO_ROT_min(float x){
    return (uint) (x  * motorConfig.gearratio * motorConfig.speed_denominator / 36000);
}

int   pd4Nanotec::convert_cGRAD_TO_EncoderUnit(float x){
    return (int) (x  * motorConfig.gearratio * 10 / 180);
}

int   pd4Nanotec::convert_EncoderUnit_TO_cGRAD(float x){
    return (int) (x  * 180 / (motorConfig.gearratio * 10));
}

void pd4Nanotec::setNanojVector(uchar* p, uint size){
    nanojStr.vector = p;
    nanojStr.sizeofNanoj = size;
}

void pd4Nanotec::uploadNanojProgram(void){
    uploadNanojRequest = true;
}

