/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *gameLayout;
    QVBoxLayout *setLayout;
    QHBoxLayout *controlLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *clearButton;
    QLabel *label;
    QSpinBox *cellsControl;
    QLabel *label2;
    QSpinBox *iterInterval;
    QHBoxLayout *fileLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *colorButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        gameLayout = new QVBoxLayout();
        gameLayout->setSpacing(6);
        gameLayout->setObjectName(QString::fromUtf8("gameLayout"));

        mainLayout->addLayout(gameLayout);

        setLayout = new QVBoxLayout();
        setLayout->setSpacing(6);
        setLayout->setObjectName(QString::fromUtf8("setLayout"));
        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(6);
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        controlLayout->addWidget(startButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        controlLayout->addWidget(stopButton);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        controlLayout->addWidget(clearButton);


        setLayout->addLayout(controlLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        setLayout->addWidget(label);

        cellsControl = new QSpinBox(centralWidget);
        cellsControl->setObjectName(QString::fromUtf8("cellsControl"));
        cellsControl->setMinimum(10);
        cellsControl->setMaximum(400);
        cellsControl->setValue(50);

        setLayout->addWidget(cellsControl);

        label2 = new QLabel(centralWidget);
        label2->setObjectName(QString::fromUtf8("label2"));

        setLayout->addWidget(label2);

        iterInterval = new QSpinBox(centralWidget);
        iterInterval->setObjectName(QString::fromUtf8("iterInterval"));
        iterInterval->setMinimum(50);
        iterInterval->setMaximum(100000);
        iterInterval->setSingleStep(10);
        iterInterval->setValue(100);

        setLayout->addWidget(iterInterval);

        fileLayout = new QHBoxLayout();
        fileLayout->setSpacing(6);
        fileLayout->setObjectName(QString::fromUtf8("fileLayout"));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        fileLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        fileLayout->addWidget(saveButton);


        setLayout->addLayout(fileLayout);

        colorButton = new QPushButton(centralWidget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));

        setLayout->addWidget(colorButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        setLayout->addItem(verticalSpacer);


        mainLayout->addLayout(setLayout);


        horizontalLayout->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Conway's Game of Life", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Universe Size", nullptr));
        cellsControl->setSuffix(QCoreApplication::translate("MainWindow", " cells", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Generation interval (in msec)", nullptr));
        iterInterval->setSuffix(QCoreApplication::translate("MainWindow", " ms", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        colorButton->setText(QCoreApplication::translate("MainWindow", "Select color for cells", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
