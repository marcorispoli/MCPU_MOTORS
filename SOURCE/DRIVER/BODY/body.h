#ifndef BODY_H
#define BODY_H

/*!
 * \defgroup  bodyModule Body Motor communication protocol module.
 *
 * This Module implements thecommunication with the BODY.
 *
 *
 */

#include <QtCore>
#include "pd4.h"


class bodyModule: public pd4Nanotec
{
    Q_OBJECT

public:
    explicit bodyModule();
    ~bodyModule(){};


signals:


public slots:


private slots:

public:

protected:


private:
    void initializationCompleted(bool result);

};



#endif // BODY_H
