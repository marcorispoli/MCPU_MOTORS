#ifndef CARM_H
#define CARM_H

/*!
 * \defgroup  trxModule TRX communication protocol module.
 *
 * This Module implements thecommunication with the TRX.
 *
 *
 */

#include <QtCore>
#include "pd4.h"


class carmModule: public pd4Nanotec
{
    Q_OBJECT

public:
    explicit carmModule();
    ~carmModule(){};


signals:


public slots:


private slots:

public:

protected:


private:
    void initializationCompleted(bool result);

};



#endif // CARM_H
