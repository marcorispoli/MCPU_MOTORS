#include "application.h"
#include "pd4.h"

void pd4Nanotec::nanojWritedata(void){


    if(nanojStr.txBlock.size() < 8){
        nanojStr.txBlock[0] |= 1; // End of data block
        nanojStr.txBlock[0] |= (8 - nanojStr.txBlock.size()) * 2; // Ignore ll the data bit

        for(int i = nanojStr.txBlock.size(); i<8; i++ ) nanojStr.txBlock.append((uchar) 0);
    }

    emit txToCan(0x600 + deviceId, nanojStr.txBlock);

    // Activate the timeout handler, in case no answer should be received
    nanojStr.rxblock = true;
    sdoRxTx.sdo_rx_ok = false;
    sdoRxTx.sdo_rxtx_completed = false;
    sdoRxTx.sdo_rx_tx_pending = true;

}

#define NANOJ_CONTROL   OD_1F51_02
#define NANOJ_DATA      OD_1F50_02_INIT
#define NANOJ_STATUS    OD_1F57_02



/**
 * @brief pd4Nanotec::subNanojProgramUpload
 * @param force
 * @param init
 * @return
 *  + 0: the subroutine is completed;
 *  + != 0: this is the delay for the next call
 */
ushort pd4Nanotec::subNanojProgramUpload(bool force){
    static unsigned short vmmchk = 0;
    static bool flag;
    static uint fase = 0;


    switch(fase){
    case 0:
        nanojUploaded = false;
        vmmchk = 0;

        // Calculate the checksum
        for(unsigned int i=0; i < nanojStr.sizeofNanoj;i++) vmmchk += (ushort) nanojStr.vector[i];

        readSDO(NANOJ_USER_PARAM,10); // Reads the user parameter containing the stored nanoj checksum
        fase++;
        return 5;

    case 1:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        if(( sdoRxTx.rxSDO.getVal() == vmmchk) && (!force)){
            nanojUploaded = true;
            qDebug() << QString("DEVICE (%1): NANOJ-PROGRAM ALREADY UPLOADED").arg(deviceId);
            break;
        }

        writeSDO(NANOJ_CONTROL, VMM_INIT); // initialize flash
        fase++;
        return 5;


    case 2:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        qDebug() << QString("DEVICE (%1): DELETE FLASH").arg(deviceId);
        writeSDO(NANOJ_CONTROL, VMM_DELETE); // Delete flash
        fase++;
        return 5;

    case 3:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());
            break;
        }

        // Reset Node
        resetNode();
        qDebug() << QString("DEVICE (%1): RESET NODE").arg(deviceId);
        fase++;
        return 2000; // Arbitrary delay time

    case 4:
        readSDO(OD_2700_02,10); // Read an arbitrary register to be sure that the reset node is completed
        fase++;
        return 5;

    case 5:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());            
            break;
        }


        writeSDO(NANOJ_CONTROL, VMM_INIT); // Initialize again the Flash
        fase++;
        return 5;

    case 6:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());            
            break;
        }

        nanojStr.vector_index = 0;
        fase++;
        return 1;

    case 7:
        writeSDO(NANOJ_DATA,0); // Initialize the  Data Ram  -----------------------------------------------------------------------------------------------
        fase++;
        return 5;

    case 8:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING OD %2.%3").arg(deviceId).arg(sdoRxTx.txSDO.getIndex(),1,16).arg(sdoRxTx.txSDO.getSubIndex());           
            break;
        }

        nanojStr.num_block_items = 0;
        flag = false;
        fase++;
        return 1;

    case 9: // Writes max 1024 the data in ram -------------------
        nanojStr.txBlock.clear();
        if(flag) nanojStr.txBlock.append((uchar) 0x10);
        else nanojStr.txBlock.append((uchar) 0x00);
        flag = !flag;

        for(int i=0; i<7; i++){
            if(nanojStr.vector_index < nanojStr.sizeofNanoj){
                nanojStr.txBlock.append((uchar) nanojStr.vector[nanojStr.vector_index]);
                nanojStr.num_block_items++;
                nanojStr.vector_index++;
                if(nanojStr.num_block_items == 1024) break;
            }else break;
        }

        nanojWritedata();
        fase++;
        return 5;

    case 10:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING NANOJ BLOCK").arg(deviceId);            
            break;
        }
        fase++;
        return 1;

    case 11:
        if((nanojStr.vector_index == nanojStr.sizeofNanoj) || (nanojStr.num_block_items == 1024)){
            fase = 12;
            return 1;
        }

        fase = 9;
        return 1;

    case 12: // Store Data ram in Flash
        writeSDO(NANOJ_CONTROL, VMM_WRITE);
        fase++;
        return 5;

    case 13:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR STORING DATA IN FLASH").arg(deviceId);           
            break;
        }

        readSDO(NANOJ_CONTROL);
        fase++;
        return 5;

    case 14:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR STORING DATA IN FLASH (READ CONTROL)").arg(deviceId);
            break;
        }

        if(sdoRxTx.rxSDO.getVal() != 0){
            fase--;
            return 100;
        }

        readSDO(NANOJ_STATUS);
        fase++;
        return 5;

    case 15:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR STORING DATA IN FLASH (READ STATUS)").arg(deviceId);
            break;
        }

        if(sdoRxTx.rxSDO.getVal() != 0){
            qDebug() << QString("DEVICE (%1): ERROR READING STATUS").arg(deviceId);
            break;
        }

        if(nanojStr.vector_index == nanojStr.sizeofNanoj){
            // Transfer completed
            fase++;
            return 1;
        }
        fase = 7;
        return 1;

     case 16:
        qDebug() << "SAVE THE CHECKSUM OF THE NANOJ PROGRAM";
        writeSDO(NANOJ_USER_PARAM, vmmchk);
        fase++;
        return 5;

    case 17:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR SAVING THE CHECKSUM").arg(deviceId);
            break;
        }

        writeSDO(RESET_USER_PARAM,RESET_CODE); // Reset the User param of the Reset flag
        fase++;
        return 5;

     case 18:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR WRITING THE RESET FLAG IN USER PARAM").arg(deviceId);
            break;
        }

        // Saves the User parameters
        writeSDO(SAVE_USER_PARAM, 1);
        fase++;
        return 5;

    case 19:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR SAVING THE CHECKSUM").arg(deviceId);
            break;
        }

        fase++;
        return 1;

    case 20:
        readSDO(SAVE_USER_PARAM);
        fase++;
        return 5;

    case 21:
        if(!sdoRxTx.sdo_rx_ok) {
            qDebug() << QString("DEVICE (%1): ERROR READING THE USER PARAM CONTROL REGISTER").arg(deviceId);
            break;
        }

        if(sdoRxTx.rxSDO.getVal()!=0){
            fase--;
            return 100;
        }


        qDebug() << "NANOJ PROGRAM SUCCESSFULLY UPLOADED";
        nanojUploaded = true;
        break;

    }

    fase = 0;
    return 0;
}

