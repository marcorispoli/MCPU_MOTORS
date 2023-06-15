/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_debugWindow
{
public:
    QFrame *mainFrame;
    QFrame *connectionFrame_4;
    QPlainTextEdit *canText;
    QPushButton *logClearButton;
    QCheckBox *logEnableCheck;
    QPlainTextEdit *debugText;
    QPushButton *debugClearButton;
    QLabel *label_16;
    QCheckBox *debugEnable;
    QLabel *label_17;
    QPushButton *trxInitButton;
    QPushButton *slideInitButton;
    QPushButton *BodyInitButton;
    QPushButton *CarmInitButton;
    QPushButton *MvertInitButton;

    void setupUi(QWidget *debugWindow)
    {
        if (debugWindow->objectName().isEmpty())
            debugWindow->setObjectName(QString::fromUtf8("debugWindow"));
        debugWindow->resize(540, 600);
        debugWindow->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(85, 170, 255);"));
        mainFrame = new QFrame(debugWindow);
        mainFrame->setObjectName(QString::fromUtf8("mainFrame"));
        mainFrame->setGeometry(QRect(0, 0, 931, 600));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        mainFrame->setFont(font);
        mainFrame->setStyleSheet(QString::fromUtf8("border-width: 1px;\n"
"border-style: solid; \n"
"border-color: darkblue;\n"
"border-color: rgb(0, 0, 127);"));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Raised);
        connectionFrame_4 = new QFrame(mainFrame);
        connectionFrame_4->setObjectName(QString::fromUtf8("connectionFrame_4"));
        connectionFrame_4->setGeometry(QRect(10, 30, 361, 561));
        connectionFrame_4->setStyleSheet(QString::fromUtf8("border-width: 1px;\n"
"border-style: solid; \n"
"border-color: darkblue;\n"
"border-color: rgb(0, 0, 127);\n"
""));
        connectionFrame_4->setFrameShape(QFrame::StyledPanel);
        connectionFrame_4->setFrameShadow(QFrame::Raised);
        canText = new QPlainTextEdit(connectionFrame_4);
        canText->setObjectName(QString::fromUtf8("canText"));
        canText->setGeometry(QRect(10, 50, 341, 211));
        QFont font1;
        font1.setPointSize(6);
        canText->setFont(font1);
        canText->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        logClearButton = new QPushButton(connectionFrame_4);
        logClearButton->setObjectName(QString::fromUtf8("logClearButton"));
        logClearButton->setGeometry(QRect(10, 10, 121, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        logClearButton->setFont(font2);
        logClearButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        logEnableCheck = new QCheckBox(connectionFrame_4);
        logEnableCheck->setObjectName(QString::fromUtf8("logEnableCheck"));
        logEnableCheck->setGeometry(QRect(170, 11, 71, 31));
        debugText = new QPlainTextEdit(connectionFrame_4);
        debugText->setObjectName(QString::fromUtf8("debugText"));
        debugText->setGeometry(QRect(10, 340, 341, 211));
        debugText->setFont(font1);
        debugText->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        debugClearButton = new QPushButton(connectionFrame_4);
        debugClearButton->setObjectName(QString::fromUtf8("debugClearButton"));
        debugClearButton->setGeometry(QRect(10, 300, 121, 31));
        debugClearButton->setFont(font2);
        debugClearButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        label_16 = new QLabel(connectionFrame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(270, 320, 71, 20));
        label_16->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        debugEnable = new QCheckBox(connectionFrame_4);
        debugEnable->setObjectName(QString::fromUtf8("debugEnable"));
        debugEnable->setGeometry(QRect(170, 300, 71, 31));
        debugEnable->setChecked(true);
        label_17 = new QLabel(connectionFrame_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(270, 30, 81, 20));
        label_17->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        trxInitButton = new QPushButton(mainFrame);
        trxInitButton->setObjectName(QString::fromUtf8("trxInitButton"));
        trxInitButton->setGeometry(QRect(400, 40, 131, 31));
        trxInitButton->setFont(font2);
        trxInitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        slideInitButton = new QPushButton(mainFrame);
        slideInitButton->setObjectName(QString::fromUtf8("slideInitButton"));
        slideInitButton->setGeometry(QRect(400, 80, 131, 31));
        slideInitButton->setFont(font2);
        slideInitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        BodyInitButton = new QPushButton(mainFrame);
        BodyInitButton->setObjectName(QString::fromUtf8("BodyInitButton"));
        BodyInitButton->setGeometry(QRect(400, 120, 131, 31));
        BodyInitButton->setFont(font2);
        BodyInitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        CarmInitButton = new QPushButton(mainFrame);
        CarmInitButton->setObjectName(QString::fromUtf8("CarmInitButton"));
        CarmInitButton->setGeometry(QRect(400, 160, 131, 31));
        CarmInitButton->setFont(font2);
        CarmInitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));
        MvertInitButton = new QPushButton(mainFrame);
        MvertInitButton->setObjectName(QString::fromUtf8("MvertInitButton"));
        MvertInitButton->setGeometry(QRect(400, 200, 131, 31));
        MvertInitButton->setFont(font2);
        MvertInitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: rgb(255, 255, 255);\n"
"border-width: 0px;\n"
""));

        retranslateUi(debugWindow);

        QMetaObject::connectSlotsByName(debugWindow);
    } // setupUi

    void retranslateUi(QWidget *debugWindow)
    {
        debugWindow->setWindowTitle(QCoreApplication::translate("debugWindow", "GENERATOR DEBUG WINDOW", nullptr));
        canText->setPlainText(QCoreApplication::translate("debugWindow", "-----\n"
"", nullptr));
        logClearButton->setText(QCoreApplication::translate("debugWindow", "CLEAR", nullptr));
        logEnableCheck->setText(QCoreApplication::translate("debugWindow", "ENABLE", nullptr));
        debugText->setPlainText(QCoreApplication::translate("debugWindow", "-----\n"
"", nullptr));
        debugClearButton->setText(QCoreApplication::translate("debugWindow", "CLEAR", nullptr));
        label_16->setText(QCoreApplication::translate("debugWindow", "DEBUG TEXT", nullptr));
        debugEnable->setText(QCoreApplication::translate("debugWindow", "ENABLE", nullptr));
        label_17->setText(QCoreApplication::translate("debugWindow", "CAN FRAMES", nullptr));
        trxInitButton->setText(QCoreApplication::translate("debugWindow", "TRX INITIALIZE", nullptr));
        slideInitButton->setText(QCoreApplication::translate("debugWindow", "SLIDE INITIALIZE", nullptr));
        BodyInitButton->setText(QCoreApplication::translate("debugWindow", "BODY INITIALIZE", nullptr));
        CarmInitButton->setText(QCoreApplication::translate("debugWindow", "CARM INITIALIZE", nullptr));
        MvertInitButton->setText(QCoreApplication::translate("debugWindow", "VERT INITIALIZE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class debugWindow: public Ui_debugWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
