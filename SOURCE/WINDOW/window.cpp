#include "application.h"
#include "ui_window.h"



debugWindow::debugWindow(QWidget *parent)
    : ui(new Ui::debugWindow)
{
    debugWindow::instance = this;
    ui->setupUi(this);
    generalDebugIndex = 0;

    // Set the View to handle the rotation


    connect(ui->logClearButton, SIGNAL(pressed()), this, SLOT(onLogClearButton()), Qt::UniqueConnection);
    connect(ui->debugClearButton, SIGNAL(pressed()), this, SLOT(onDebugClearButton()), Qt::UniqueConnection);
    connect(ui->logEnableCheck, SIGNAL(stateChanged(int)), this, SLOT(on_logEnableCheck_stateChanged(int)));
    connect(ui->trxInitButton, SIGNAL(pressed()), this, SLOT(onTrxInitButton()), Qt::UniqueConnection);
    connect(ui->slideInitButton, SIGNAL(pressed()), this, SLOT(onSlideInitButton()), Qt::UniqueConnection);

    connect(ui->BodyInitButton, SIGNAL(pressed()), this, SLOT(onBodyInitButton()), Qt::UniqueConnection);
    connect(ui->CarmInitButton, SIGNAL(pressed()), this, SLOT(onCarmInitButton()), Qt::UniqueConnection);
    connect(ui->MvertInitButton, SIGNAL(pressed()), this, SLOT(onMvertInitButton()), Qt::UniqueConnection);

    pollingTimer  = startTimer(500);

}

debugWindow::~debugWindow()
{
    delete ui;
}

void debugWindow::initWindow(void)
{


}

void debugWindow::exitWindow(void)
{

    if(pollingTimer)    killTimer(pollingTimer);

}


void debugWindow::timerEvent(QTimerEvent* ev)
{
    if(ev->timerId() == pollingTimer)
    {


        return;
    }


}


void debugWindow::onLogClearButton(void){
    ui->canText->appendPlainText("");
    ui->canText->clear();
}
void debugWindow::onDebugClearButton(void){
    ui->debugText->appendPlainText("");
    ui->debugText->clear();
}



void debugWindow::on_logEnableCheck_stateChanged(int arg1)
{
    static bool connected = false;

    if((arg1 == Qt::Checked) && (!connected)) {
        connected = true;

    }else if((arg1 == Qt::Unchecked) && (connected)) {
        connected = false;

    }
}

/**
 * @brief This function receives the data coming from the CAN network.
 *
 * The Data packet received from the CAN network is displayed with the message number in the proper panel.
 *
 *
 * @param canId: this is the canId of the can message
 * @param data: this is the data content of the frame
 */
void debugWindow::rxFromCan(ushort canId, QByteArray data){

    QString stringa = QString("%1> FROM CANID:0x%3 - ").arg(((double) clock())/CLOCKS_PER_SEC).arg(canId,1,16);
    for(int i=0; i< 8;i++){
        stringa.append(QString(" 0x%1").arg((uchar) data[i],1,16));
    }
    ui->canText->appendPlainText(stringa);

}

/**
 * @brief This function is activated whenever the Client data are forwarded to the CAN network.
 *
 * The data content is Logged in the Can Data traffic panel
 *
 * @param canId: this is the canId of the can message
 * @param data: this is the data content of the frame
 */
void debugWindow::txToCan(ushort canId, QByteArray data){

    QString stringa = QString("%1> TO CANID:0x%3 - ").arg(((double) clock())/CLOCKS_PER_SEC).arg(canId,1,16);
    for(int i=0; i< data.size();i++){
        stringa.append(QString(" 0x%1").arg((uchar) data[i],1,16));
    }
    ui->canText->appendPlainText(stringa);

}


void debugWindow::debugMessageHandler(QtMsgType type, QString msg){
    if(!debugWindow::instance) return;
    if(debugWindow::instance->ui->debugEnable->isChecked())   debugWindow::instance->ui->debugText->appendPlainText(msg);

}

void debugWindow::onTrxInitButton(void){

    if(TRX->activateInitialization()) qDebug() << "TRX INIT BUTTON ACCEPTED";
    else qDebug() << "TRX INIT BUTTON REJECTED";
};

void debugWindow::onSlideInitButton(void){

    if(SLIDE->activateInitialization()) qDebug() << "SLIDE INIT BUTTON ACCEPTED";
    else qDebug() << "SLIDE INIT BUTTON REJECTED";
};
void debugWindow::onBodyInitButton(void){

    if(BODY->activateInitialization()) qDebug() << "BODY INIT BUTTON ACCEPTED";
    else qDebug() << "BODY INIT BUTTON REJECTED";
};
void debugWindow::onCarmInitButton(void){

    if(CARM->activateInitialization()) qDebug() << "CARM INIT BUTTON ACCEPTED";
    else qDebug() << "CARM INIT BUTTON REJECTED";
};
void debugWindow::onMvertInitButton(void){

    if(MVERT->activateInitialization()) qDebug() << "MVERT INIT BUTTON ACCEPTED";
    else qDebug() << "MVERT INIT BUTTON REJECTED";
};

void debugWindow::updateData(void){

}
void debugWindow::assignData(void){



}

void debugWindow::updateStatus(void){



}

