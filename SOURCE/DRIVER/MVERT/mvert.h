#ifndef MVERT_H
#define MVERT_H

/*!
 * \defgroup  trxModule TRX communication protocol module.
 *
 * This Module implements thecommunication with the TRX.
 *
 *
 */

#include <QtCore>
#include "pd4.h"


class mvertModule: public pd4Nanotec
{
    Q_OBJECT

public:
    explicit mvertModule();
    ~mvertModule(){};


signals:


public slots:


private slots:

public:

protected:


private:
    void initializationCompleted(bool result);

};



#endif // MVERT_H
