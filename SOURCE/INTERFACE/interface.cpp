#include "application.h"
#include <QStringConverter>

/**
 * @brief Interface::Interface
 *
 * @param
 * - ipaddress: IP where server will be bounded;
 * - port: bounding port
 *
 */
Interface::Interface(void):applicationInterface(SYSCONFIG->getParam<QString>(SYS_MOTORS_PROCESS_PARAM,SYS_PROCESS_IP),
                                                SYSCONFIG->getParam<int>(SYS_MOTORS_PROCESS_PARAM,SYS_PROCESS_PORT))
{

}

uint Interface::handleReceivedCommand(QList<QString>* frame, QList<QString>* answer){

    if(frame->at(2) == COMMAND_GET_REVISION)  return GetRevision(answer);
    else if(frame->at(2) == COMMAND_TRX_INITIALIZE)  return TrxInitialize(answer);
    return 1;
}

//______________________________ COMMANDS _____________________________________//
uint Interface::GetRevision( QList<QString>* answer){
    answer->clear();
    answer->append(QString("%1").arg(Application::APP_MAJ_REV));
    answer->append(QString("%1").arg(Application::APP_MIN_REV));
    answer->append(QString("%1").arg(Application::APP_SUB_REV));
    return 0;
}

uint Interface::TrxInitialize( QList<QString>* answer){
    answer->clear();
    if(TRX->activateInitialization()) return 0;
    return 2;
}


//______________________________ EVENTS _____________________________________//
void Interface::EVENT_TrxInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_TRX_INIT_COMPLETED, &params);
}



