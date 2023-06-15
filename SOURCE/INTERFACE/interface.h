#ifndef INTERFACE_H
#define INTERFACE_H

#include "QObject"
#include "applicationInterface.h"

/*!
 * \defgroup  interfaceModule Application Command Interface Module.
 *
 * This Module implements the communication protocol with the Gantry.
 *
 * # CONNECTION DETAILS
 *
 * The Server IP address is: 127.0.0.1@10004.
 *
 * # EVENTS FROM GANTRY DESCRIPTION
 *
 * The Events from Gantry are considered *Commands* to be executed;
 *
 * Follows the list of the Implemented Commands:
 *
 *
 *  > The Application will acknowledge the command ONLY to the client that sent the command;
 *
 *
 * # EVENTS TO GANTRY DESCRIPTION
 *
 * The Events to Gantry are considered *Events* to be notified to the Gantry;
 *
 * Follows a list of the implemented Events:
 *
 *
 *  > The Application will forward the EVENTS to all the connected clients.
 *
 */


/**
 * @brief This class resides into the Main Thread and implements the
 * communication protocol with the Gantry.
 *
 * The class starts listening an incoming Client connection and creates\n
 * for any individual connection a given socket handler (SocketItem class). \n
 * Every Socket is assigned to a unique ID so that the Server can redirect the
 * answer frame with the sender client.
 *
 * The Reception and Transmission are implemented into the  QTcpServer library
 * that runs in a separate thread and exchanges data only through the SIgnal/Slot
 * mechanism.
 *
 *
 * \ingroup InterfaceModule
 */
class Interface : public applicationInterface
{
    Q_OBJECT

public:

    explicit Interface(void);
    ~Interface(){};

    uint handleReceivedCommand(QList<QString>* frame, QList<QString>* answer); //!< Reimplement the handler for the received Commmands


    #define EVENT_TRX_INIT_COMPLETED "EVENT_TRX_InitCompleted"
    void EVENT_TrxInitCompleted(bool result);
    #define EVENT_SLIDE_INIT_COMPLETED "EVENT_SLIDE_InitCompleted"
    void EVENT_SlideInitCompleted(bool result);
    #define EVENT_CARM_INIT_COMPLETED "EVENT_CARM_InitCompleted"
    void EVENT_CarmInitCompleted(bool result);
    #define EVENT_BODY_INIT_COMPLETED "EVENT_BODY_InitCompleted"
    void EVENT_BodyInitCompleted(bool result);
    #define EVENT_MVERT_INIT_COMPLETED "EVENT_MVERT_InitCompleted"
    void EVENT_MvertInitCompleted(bool result);


private slots:


private:
    typedef uint (Interface::*funcPtr)(QList<QString>*);
    QMap<QString, funcPtr> interfaceCommands;

    // List of the available Interface commands
    uint interfaceNotRecognizedCommand( QList<QString>* answer);
    uint GetRevision( QList<QString>* answer);      //!< Command Revision request handling
    uint TrxInitialize( QList<QString>* answer);    //!< Command TRX Initialize handling
    uint SlideInitialize( QList<QString>* answer);  //!< Command SLIDE Initialize handling
    uint CarmInitialize( QList<QString>* answer);  //!< Command CARM Initialize handling
    uint BodyInitialize( QList<QString>* answer);  //!< Command BODY Initialize handling
    uint MvertInitialize( QList<QString>* answer);  //!< Command MVert Initialize handling


};

#endif // SERVER_H
