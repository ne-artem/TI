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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBoxQ;
    QLabel *label_2;
    QSpinBox *spinBoxP;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBoxB;
    QLabel *label_4;
    QSpinBox *spinBoxN;
    QTextEdit *textEditM;
    QVBoxLayout *verticalLayout_2;
    QComboBox *CmbBox;
    QPushButton *ButExec;
    QPushButton *ButFile;
    QTextEdit *textEditC;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(626, 288);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        spinBoxQ = new QSpinBox(centralwidget);
        spinBoxQ->setObjectName("spinBoxQ");
        spinBoxQ->setMaximum(65535);

        horizontalLayout_2->addWidget(spinBoxQ);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        spinBoxP = new QSpinBox(centralwidget);
        spinBoxP->setObjectName("spinBoxP");
        spinBoxP->setMaximum(65535);

        horizontalLayout_2->addWidget(spinBoxP);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_3);

        spinBoxB = new QSpinBox(centralwidget);
        spinBoxB->setObjectName("spinBoxB");
        spinBoxB->setMaximum(65535);

        horizontalLayout->addWidget(spinBoxB);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_4);

        spinBoxN = new QSpinBox(centralwidget);
        spinBoxN->setObjectName("spinBoxN");
        spinBoxN->setEnabled(false);
        spinBoxN->setMaximum(65535);

        horizontalLayout->addWidget(spinBoxN);


        verticalLayout->addLayout(horizontalLayout);

        textEditM = new QTextEdit(centralwidget);
        textEditM->setObjectName("textEditM");

        verticalLayout->addWidget(textEditM);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        CmbBox = new QComboBox(centralwidget);
        CmbBox->addItem(QString());
        CmbBox->addItem(QString());
        CmbBox->setObjectName("CmbBox");

        verticalLayout_2->addWidget(CmbBox);

        ButExec = new QPushButton(centralwidget);
        ButExec->setObjectName("ButExec");

        verticalLayout_2->addWidget(ButExec);

        ButFile = new QPushButton(centralwidget);
        ButFile->setObjectName("ButFile");

        verticalLayout_2->addWidget(ButFile);


        horizontalLayout_3->addLayout(verticalLayout_2);

        textEditC = new QTextEdit(centralwidget);
        textEditC->setObjectName("textEditC");
        textEditC->setReadOnly(true);

        horizontalLayout_3->addWidget(textEditC);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 626, 21));
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
        label->setText(QCoreApplication::translate("MainWindow", "Q", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        CmbBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        CmbBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\224\320\265\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));

        ButExec->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        ButFile->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
