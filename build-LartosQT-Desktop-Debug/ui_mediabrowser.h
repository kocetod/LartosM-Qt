/********************************************************************************
** Form generated from reading UI file 'mediabrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIABROWSER_H
#define UI_MEDIABROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaBrowser
{
public:
    QListView *imageBrowser;
    QLabel *imgViewer;
    QPushButton *btnCopy;
    QPushButton *btnBack;
    QLabel *label;
    QPushButton *btnCopyAll;

    void setupUi(QWidget *MediaBrowser)
    {
        if (MediaBrowser->objectName().isEmpty())
            MediaBrowser->setObjectName(QStringLiteral("MediaBrowser"));
        MediaBrowser->resize(1280, 800);
        MediaBrowser->setStyleSheet(QStringLiteral("background: rgb(170, 170,  170);"));
        imageBrowser = new QListView(MediaBrowser);
        imageBrowser->setObjectName(QStringLiteral("imageBrowser"));
        imageBrowser->setGeometry(QRect(10, 10, 311, 771));
        imageBrowser->setFocusPolicy(Qt::StrongFocus);
        imageBrowser->setStyleSheet(QLatin1String("background: rgb(196, 196, 196);\n"
"border: 5px solid black;\n"
"border-radius: 10px;"));
        imageBrowser->setIconSize(QSize(150, 150));
        imageBrowser->setMovement(QListView::Static);
        imageBrowser->setSpacing(150);
        imageBrowser->setGridSize(QSize(130, 150));
        imageBrowser->setViewMode(QListView::IconMode);
        imgViewer = new QLabel(MediaBrowser);
        imgViewer->setObjectName(QStringLiteral("imgViewer"));
        imgViewer->setGeometry(QRect(340, 50, 920, 575));
        btnCopy = new QPushButton(MediaBrowser);
        btnCopy->setObjectName(QStringLiteral("btnCopy"));
        btnCopy->setGeometry(QRect(330, 690, 281, 91));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(30);
        font.setBold(false);
        font.setWeight(50);
        btnCopy->setFont(font);
        btnCopy->setStyleSheet(QLatin1String("border: 5px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: solid white;\n"
"color: black;"));
        btnBack = new QPushButton(MediaBrowser);
        btnBack->setObjectName(QStringLiteral("btnBack"));
        btnBack->setGeometry(QRect(1060, 690, 211, 91));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(30);
        btnBack->setFont(font1);
        btnBack->setStyleSheet(QLatin1String("border: 5px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: solid white;\n"
"color: black;"));
        label = new QLabel(MediaBrowser);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(670, 730, 291, 51));
        QFont font2;
        font2.setPointSize(30);
        label->setFont(font2);
        btnCopyAll = new QPushButton(MediaBrowser);
        btnCopyAll->setObjectName(QStringLiteral("btnCopyAll"));
        btnCopyAll->setGeometry(QRect(620, 690, 281, 91));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(26);
        btnCopyAll->setFont(font3);
        btnCopyAll->setStyleSheet(QLatin1String("border: 5px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: solid white;\n"
"color: black;"));

        retranslateUi(MediaBrowser);

        QMetaObject::connectSlotsByName(MediaBrowser);
    } // setupUi

    void retranslateUi(QWidget *MediaBrowser)
    {
        MediaBrowser->setWindowTitle(QApplication::translate("MediaBrowser", "Form", nullptr));
        imgViewer->setText(QString());
        btnCopy->setText(QApplication::translate("MediaBrowser", "Copy", nullptr));
        btnBack->setText(QApplication::translate("MediaBrowser", "Back", nullptr));
        label->setText(QString());
        btnCopyAll->setText(QApplication::translate("MediaBrowser", "Copy All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MediaBrowser: public Ui_MediaBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIABROWSER_H
