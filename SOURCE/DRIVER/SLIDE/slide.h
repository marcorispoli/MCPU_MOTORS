#ifndef SLIDE_H
#define SLIDE_H

/*!
 * \defgroup  trxModule TRX communication protocol module.
 *
 * This Module implements thecommunication with the TRX.
 *
 *
 */

#include <QtCore>
#include "pd4.h"


class slideModule: public pd4Nanotec
{
    Q_OBJECT

public:
    explicit slideModule();
    ~slideModule(){};


signals:


public slots:


private slots:

public:

protected:


private:
    void initializationCompleted(bool result);

};



#endif // SLIDE_H
