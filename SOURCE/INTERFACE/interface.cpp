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
    // Add the COMMANDS list
    interfaceCommands.insert("GetRevision" ,&Interface::GetRevision);
    interfaceCommands.insert("TrxInitialize" ,&Interface::TrxInitialize);
    interfaceCommands.insert("SlideInitialize" ,&Interface::SlideInitialize);
    interfaceCommands.insert("CarmInitialize" ,&Interface::CarmInitialize);
    interfaceCommands.insert("BodyInitialize" ,&Interface::BodyInitialize);
    interfaceCommands.insert("MvertInitialize" ,&Interface::MvertInitialize);
}

uint Interface::handleReceivedCommand(QList<QString>* frame, QList<QString>* answer){

    funcPtr function = interfaceCommands.value(frame->at(2),&Interface::interfaceNotRecognizedCommand);
    if(function == 0) return interfaceNotRecognizedCommand(answer);
    return (this->*function)(answer);

}

//______________________________ COMMANDS _____________________________________//
uint Interface::interfaceNotRecognizedCommand(QList<QString>* answer){
    return 1;
}

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

uint Interface::SlideInitialize( QList<QString>* answer){
    answer->clear();
    if(SLIDE->activateInitialization()) return 0;
    return 2;
}

uint Interface::BodyInitialize( QList<QString>* answer){
    answer->clear();
    qDebug() << "BODY INITIALIZE";
    if(BODY->activateInitialization()) return 0;
    return 2;
}

uint Interface::CarmInitialize( QList<QString>* answer){
    answer->clear();
    if(CARM->activateInitialization()) return 0;
    return 2;
}

uint Interface::MvertInitialize( QList<QString>* answer){
    answer->clear();
    if(MVERT->activateInitialization()) return 0;
    return 2;
}

//______________________________ EVENTS _____________________________________//
void Interface::EVENT_TrxInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_TRX_INIT_COMPLETED, &params);
}

void Interface::EVENT_SlideInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_SLIDE_INIT_COMPLETED, &params);
}

void Interface::EVENT_CarmInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_CARM_INIT_COMPLETED, &params);
}

void Interface::EVENT_BodyInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_BODY_INIT_COMPLETED, &params);
}

void Interface::EVENT_MvertInitCompleted(bool result){
    QList<QString> params;

    if(result) params.append(QString("1"));
    else params.append(QString("0"));
    sendEvent(EVENT_MVERT_INIT_COMPLETED, &params);
}



