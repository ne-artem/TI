/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditKey;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout;
    QComboBox *comBoxAlgorithm;
    QComboBox *comBoxMode;
    QPushButton *pushButExec;
    QPushButton *pushButExecFile;
    QTextEdit *textEditRes;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(807, 312);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEditKey = new QLineEdit(centralwidget);
        lineEditKey->setObjectName("lineEditKey");
        QFont font;
        font.setPointSize(12);
        lineEditKey->setFont(font);

        verticalLayout_2->addWidget(lineEditKey);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setFont(font);

        verticalLayout_2->addWidget(textEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        comBoxAlgorithm = new QComboBox(centralwidget);
        comBoxAlgorithm->addItem(QString());
        comBoxAlgorithm->addItem(QString());
        comBoxAlgorithm->setObjectName("comBoxAlgorithm");
        QFont font1;
        font1.setPointSize(14);
        comBoxAlgorithm->setFont(font1);

        verticalLayout->addWidget(comBoxAlgorithm);

        comBoxMode = new QComboBox(centralwidget);
        comBoxMode->addItem(QString());
        comBoxMode->addItem(QString());
        comBoxMode->setObjectName("comBoxMode");
        comBoxMode->setFont(font1);

        verticalLayout->addWidget(comBoxMode);

        pushButExec = new QPushButton(centralwidget);
        pushButExec->setObjectName("pushButExec");
        pushButExec->setFont(font1);

        verticalLayout->addWidget(pushButExec);

        pushButExecFile = new QPushButton(centralwidget);
        pushButExecFile->setObjectName("pushButExecFile");
        pushButExecFile->setFont(font1);

        verticalLayout->addWidget(pushButExecFile);


        horizontalLayout->addLayout(verticalLayout);

        textEditRes = new QTextEdit(centralwidget);
        textEditRes->setObjectName("textEditRes");
        textEditRes->setEnabled(true);
        textEditRes->setFont(font);
        textEditRes->setReadOnly(true);

        horizontalLayout->addWidget(textEditRes);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 807, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEditKey->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\273\321\216\321\207", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202</span></p></body></html>", nullptr));
        comBoxAlgorithm->setItemText(0, QCoreApplication::translate("MainWindow", "\320\250\320\270\321\204\321\200 \320\237\320\273\320\265\320\271\321\204\320\265\320\271\321\200\320\260", nullptr));
        comBoxAlgorithm->setItemText(1, QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\222\320\270\320\266\320\265\320\275\320\265\321\200\320\260", nullptr));

        comBoxMode->setItemText(0, QCoreApplication::translate("MainWindow", "\320\250\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        comBoxMode->setItemText(1, QCoreApplication::translate("MainWindow", "\320\224\320\265\321\210\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));

        pushButExec->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        pushButExecFile->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214 \320\264\320\273\321\217 \321\204\320\260\320\271\320\273\320\260", nullptr));
        textEditRes->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
