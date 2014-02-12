/********************************************************************************
** Form generated from reading UI file 'uploaderwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADERWINDOW_H
#define UI_UPLOADERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UploaderWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *uploaderTab;
    QGridLayout *gridLayout_3;
    QGridLayout *uploaderLayout;
    QPushButton *uploadButton;
    QProgressBar *uploadProgressBar;
    QLineEdit *uploadStatusEdit;
    QHBoxLayout *filePickerLayout;
    QLabel *filePickerLabel;
    QPushButton *filePickerButton;
    QWidget *downloaderTab;
    QGridLayout *gridLayout_4;
    QVBoxLayout *downloaderLayout;
    QLineEdit *downloadPickerEdit;
    QPushButton *downloadButton;
    QProgressBar *downloadProgressBar;
    QWidget *logTab;
    QTextBrowser *logBrowser;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UploaderWindow)
    {
        if (UploaderWindow->objectName().isEmpty())
            UploaderWindow->setObjectName(QStringLiteral("UploaderWindow"));
        UploaderWindow->setEnabled(true);
        UploaderWindow->resize(423, 279);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UploaderWindow->sizePolicy().hasHeightForWidth());
        UploaderWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(UploaderWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        uploaderTab = new QWidget();
        uploaderTab->setObjectName(QStringLiteral("uploaderTab"));
        gridLayout_3 = new QGridLayout(uploaderTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        uploaderLayout = new QGridLayout();
        uploaderLayout->setSpacing(6);
        uploaderLayout->setObjectName(QStringLiteral("uploaderLayout"));
        uploadButton = new QPushButton(uploaderTab);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));

        uploaderLayout->addWidget(uploadButton, 1, 0, 1, 1);

        uploadProgressBar = new QProgressBar(uploaderTab);
        uploadProgressBar->setObjectName(QStringLiteral("uploadProgressBar"));
        uploadProgressBar->setValue(100);

        uploaderLayout->addWidget(uploadProgressBar, 2, 0, 1, 1);

        uploadStatusEdit = new QLineEdit(uploaderTab);
        uploadStatusEdit->setObjectName(QStringLiteral("uploadStatusEdit"));

        uploaderLayout->addWidget(uploadStatusEdit, 3, 0, 1, 1);

        filePickerLayout = new QHBoxLayout();
        filePickerLayout->setSpacing(6);
        filePickerLayout->setObjectName(QStringLiteral("filePickerLayout"));
        filePickerLabel = new QLabel(uploaderTab);
        filePickerLabel->setObjectName(QStringLiteral("filePickerLabel"));

        filePickerLayout->addWidget(filePickerLabel);

        filePickerButton = new QPushButton(uploaderTab);
        filePickerButton->setObjectName(QStringLiteral("filePickerButton"));

        filePickerLayout->addWidget(filePickerButton);


        uploaderLayout->addLayout(filePickerLayout, 0, 0, 1, 1);


        gridLayout_3->addLayout(uploaderLayout, 0, 0, 1, 1);

        tabWidget->addTab(uploaderTab, QString());
        downloaderTab = new QWidget();
        downloaderTab->setObjectName(QStringLiteral("downloaderTab"));
        gridLayout_4 = new QGridLayout(downloaderTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        downloaderLayout = new QVBoxLayout();
        downloaderLayout->setSpacing(6);
        downloaderLayout->setObjectName(QStringLiteral("downloaderLayout"));
        downloadPickerEdit = new QLineEdit(downloaderTab);
        downloadPickerEdit->setObjectName(QStringLiteral("downloadPickerEdit"));

        downloaderLayout->addWidget(downloadPickerEdit);

        downloadButton = new QPushButton(downloaderTab);
        downloadButton->setObjectName(QStringLiteral("downloadButton"));

        downloaderLayout->addWidget(downloadButton);

        downloadProgressBar = new QProgressBar(downloaderTab);
        downloadProgressBar->setObjectName(QStringLiteral("downloadProgressBar"));
        downloadProgressBar->setValue(100);

        downloaderLayout->addWidget(downloadProgressBar);


        gridLayout_4->addLayout(downloaderLayout, 0, 0, 1, 1);

        tabWidget->addTab(downloaderTab, QString());
        logTab = new QWidget();
        logTab->setObjectName(QStringLiteral("logTab"));
        logBrowser = new QTextBrowser(logTab);
        logBrowser->setObjectName(QStringLiteral("logBrowser"));
        logBrowser->setGeometry(QRect(0, 0, 591, 471));
        tabWidget->addTab(logTab, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        UploaderWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(UploaderWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UploaderWindow->setStatusBar(statusBar);

        retranslateUi(UploaderWindow);
        QObject::connect(downloadButton, SIGNAL(clicked()), UploaderWindow, SLOT(performDownload()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(UploaderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UploaderWindow)
    {
        UploaderWindow->setWindowTitle(QApplication::translate("UploaderWindow", "File Uploader", 0));
        uploadButton->setText(QApplication::translate("UploaderWindow", "Upload", 0));
#ifndef QT_NO_TOOLTIP
        uploadProgressBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        filePickerLabel->setText(QApplication::translate("UploaderWindow", "No file chosen...", 0));
        filePickerButton->setText(QApplication::translate("UploaderWindow", "Choose file...", 0));
        tabWidget->setTabText(tabWidget->indexOf(uploaderTab), QApplication::translate("UploaderWindow", "Upload", 0));
        downloadPickerEdit->setPlaceholderText(QApplication::translate("UploaderWindow", "paste token here", 0));
        downloadButton->setText(QApplication::translate("UploaderWindow", "Download", 0));
        tabWidget->setTabText(tabWidget->indexOf(downloaderTab), QApplication::translate("UploaderWindow", "Download", 0));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QApplication::translate("UploaderWindow", "Log", 0));
    } // retranslateUi

};

namespace Ui {
    class UploaderWindow: public Ui_UploaderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADERWINDOW_H
