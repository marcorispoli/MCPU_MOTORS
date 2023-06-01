#ifndef DEVICE_PROTOCOL_H
#define DEVICE_PROTOCOL_H

#include "QObject"
#include "can_device_protocol.h"
#include "can_bootloader_protocol.h"

/*!
 * \defgroup  deviceModule Device Protocol implementation
 *
 *
 */


class deviceProtocol: public canDeviceProtocol
{
    Q_OBJECT

public:
    explicit deviceProtocol();
    ~deviceProtocol(){};

    // Workflow handling
    typedef enum{
        _WORKFLOW_NONE = 0,

    }PROTOCOL_WORKFLOW_e;


    inline canDeviceProtocolFrame::CAN_REGISTER_t getParam(uint8_t data){return deviceParamRegisters[data];};
    inline canDeviceProtocolFrame::CAN_REGISTER_t getData(uint8_t data){return deviceDataRegisters[data];};
    inline canDeviceProtocolFrame::CAN_REGISTER_t getStatus(uint8_t data){return deviceStatusRegisters[data];};
    void setData(uint8_t idx, uint8_t data, uint8_t mask, bool stat){
        uchar b = deviceDataRegisters[idx].d[data] &=~ mask;
        if(stat) deviceDataRegisters[idx].d[data] = b | mask;
        else deviceDataRegisters[idx].d[data] = b;
    };


signals:


public slots:


private slots:



public:
    uchar execCmd;
    uchar execParam[4];
    bool  abortCmd;

protected:



private:
    PROTOCOL_WORKFLOW_e workflow;
    uchar subWorkflow;
    uchar sequence;
    bool  rxOk;



};
#endif // DEVICE_PROTOCOL_H
