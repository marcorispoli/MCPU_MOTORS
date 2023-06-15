
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Include supporto per Qt Network (moduli TCP/IP)
QT += network

FORMS += \
    $${TARGET_SOURCE}/WINDOW/window.ui \

RESOURCES += \
    $${TARGET_RESOURCE}/assets.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

SOURCES += \
    $${TARGET_SOURCE}/main.cpp \
    $${SHARED}/APPLICATION_INTERFACE/applicationInterface.cpp \
    $${SHARED}/CAN_CLIENT/canclient.cpp \
    $${SHARED}/APPLOG/applog.cpp \
    $${SHARED}/CONFIGFILE/configfile.cpp \   
    $${TARGET_SOURCE}/INTERFACE/interface.cpp \   
    $${TARGET_SOURCE}/WINDOW/window.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/cia_standard_proc.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/dictionary.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/nanoj.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4_subroutines.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4_positioning.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4_zero_setting.cpp \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4_initialization.cpp \
    $${TARGET_SOURCE}/DRIVER/TRX/trx.cpp \
    $${TARGET_SOURCE}/DRIVER/SLIDE/slide.cpp \
    $${TARGET_SOURCE}/DRIVER/CARM/carm.cpp \
    $${TARGET_SOURCE}/DRIVER/BODY/body.cpp \
    $${TARGET_SOURCE}/DRIVER/MVERT/mvert.cpp \




HEADERS += \
    $${TARGET_SOURCE}/application.h \
    $${SHARED}/APPLICATION_INTERFACE/applicationInterface.h \
    $${SHARED}/CAN_CLIENT/canclient.h \
    $${SHARED}/APPLOG/applog.h \
    $${SHARED}/CONFIGFILE/sysconfig.h \
    $${SHARED}/CONFIGFILE/configfile.h \
    $${SHARED}/ERRORS/syserr.h \
    $${TARGET_SOURCE}/INTERFACE/interface.h \    
    $${TARGET_SOURCE}/WINDOW/window.h \
    $${TARGET_SOURCE}/CONFIGURATION/boardconfig.h \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/dictionary.h \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4.h \
    $${TARGET_SOURCE}/DRIVER/NANOTEC/pd4_dictionary.h \
    $${TARGET_SOURCE}/DRIVER/TRX/trx.h \
    $${TARGET_SOURCE}/DRIVER/TRX/nanoj_trx.h \
    $${TARGET_SOURCE}/DRIVER/SLIDE/slide.h \
    $${TARGET_SOURCE}/DRIVER/CARM/carm.h \
    $${TARGET_SOURCE}/DRIVER/BODY/body.h \
    $${TARGET_SOURCE}/DRIVER/MVERT/mvert.h \




# Aggiunge tutti i path di progetto
INCLUDEPATH += \
    $${SHARED}/APPLICATION_INTERFACE \
    $${SHARED}/CAN_CLIENT \
    $${SHARED}/APPLOG \
    $${SHARED}/CONFIGFILE \
    $${SHARED}/ERRORS \
    $${TARGET_SOURCE} \
    $${TARGET_SOURCE}/INTERFACE \
    $${TARGET_SOURCE}/PROTOCOL \
    $${TARGET_SOURCE}/WINDOW  \
    $${TARGET_SOURCE}/CONFIGURATION  \
    $${TARGET_SOURCE}/DRIVER \
    $${TARGET_SOURCE}/DRIVER/NANOTEC \
    $${TARGET_SOURCE}/DRIVER/TRX \
    $${TARGET_SOURCE}/DRIVER/SLIDE \
    $${TARGET_SOURCE}/DRIVER/CARM \
    $${TARGET_SOURCE}/DRIVER/BODY \
    $${TARGET_SOURCE}/DRIVER/MVERT \
