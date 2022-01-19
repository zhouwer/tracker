/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include </home/w/Desktop/all/src/mouse.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *openButton;
    QListWidget *listWidget_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    Mouse *label;
    QLabel *label_4;
    QLabel *label_3;
    QListWidget *listWidget;
    QPushButton *endButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1785, 938);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(openButton, 5, 0, 1, 1);

        listWidget_2 = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setMaximumSize(QSize(555, 16777215));

        gridLayout->addWidget(listWidget_2, 3, 3, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1204, 881));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(399, 22));

        verticalLayout->addWidget(label_2);

        label = new Mouse(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 4, 3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(399, 22));

        gridLayout->addWidget(label_4, 2, 3, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(399, 22));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        listWidget = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(555, 16777215));

        gridLayout->addWidget(listWidget, 1, 3, 1, 1);

        endButton_2 = new QPushButton(centralWidget);
        endButton_2->setObjectName(QStringLiteral("endButton_2"));
        endButton_2->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(endButton_2, 5, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        openButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));

        const bool __sortingEnabled = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_2->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_2->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_2->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_2->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_2->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_2->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_2->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_2->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_2->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_2->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_2->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_2->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        listWidget_2->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("MainWindow", "\345\256\236\346\227\266\347\224\273\351\235\242\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\256\236\346\227\266\347\224\273\351\235\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\211\213\351\200\211\344\277\241\346\201\257\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\344\277\241\346\201\257\357\274\232", Q_NULLPTR));

        const bool __sortingEnabled1 = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem12 = listWidget->item(0);
        ___qlistwidgetitem12->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem13 = listWidget->item(1);
        ___qlistwidgetitem13->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem14 = listWidget->item(2);
        ___qlistwidgetitem14->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem15 = listWidget->item(3);
        ___qlistwidgetitem15->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem16 = listWidget->item(4);
        ___qlistwidgetitem16->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem17 = listWidget->item(5);
        ___qlistwidgetitem17->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem18 = listWidget->item(6);
        ___qlistwidgetitem18->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem19 = listWidget->item(7);
        ___qlistwidgetitem19->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem20 = listWidget->item(8);
        ___qlistwidgetitem20->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem21 = listWidget->item(9);
        ___qlistwidgetitem21->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem22 = listWidget->item(10);
        ___qlistwidgetitem22->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem23 = listWidget->item(11);
        ___qlistwidgetitem23->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem24 = listWidget->item(12);
        ___qlistwidgetitem24->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem25 = listWidget->item(13);
        ___qlistwidgetitem25->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem26 = listWidget->item(14);
        ___qlistwidgetitem26->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem27 = listWidget->item(15);
        ___qlistwidgetitem27->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem28 = listWidget->item(16);
        ___qlistwidgetitem28->setText(QApplication::translate("MainWindow", "id", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem29 = listWidget->item(17);
        ___qlistwidgetitem29->setText(QApplication::translate("MainWindow", "-----------------------------------------------------------------------------------------------------------------------------", Q_NULLPTR));
        listWidget->setSortingEnabled(__sortingEnabled1);

        endButton_2->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
