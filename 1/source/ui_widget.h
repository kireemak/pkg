/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *ColorRect;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *LLabel_1;
    QLabel *LLabel_3;
    QSpinBox *Left_3;
    QComboBox *LeftCB;
    QSpinBox *Left_1;
    QSpinBox *Left_2;
    QLabel *LLabel_2;
    QSpinBox *Left_4;
    QLabel *LLabel_4;
    QGridLayout *gridLayout_2;
    QSpinBox *Mid_4;
    QComboBox *CentralCB;
    QSpinBox *Mid_1;
    QLabel *MLabel_4;
    QLabel *MLabel_1;
    QSpinBox *Mid_2;
    QLabel *MLabel_3;
    QLabel *MLabel_2;
    QSpinBox *Mid_3;
    QGridLayout *gridLayout_3;
    QSpinBox *Right_1;
    QLabel *RLabel_3;
    QComboBox *RightCB;
    QSpinBox *Right_2;
    QLabel *RLabel_2;
    QSpinBox *Right_3;
    QLabel *RLabel_1;
    QLabel *RLabel_4;
    QSpinBox *Right_4;
    QGridLayout *gridLayout_4;
    QLabel *SliderLabel_1;
    QLabel *SliderLabel_2;
    QLabel *SliderLabel_4;
    QLabel *SliderLabel_3;
    QSlider *Slider_3;
    QSlider *Slider_4;
    QSlider *Slider_1;
    QSlider *Slider_2;
    QPushButton *colorButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 482);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        ColorRect = new QLabel(Widget);
        ColorRect->setObjectName("ColorRect");

        verticalLayout->addWidget(ColorRect);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        LLabel_1 = new QLabel(Widget);
        LLabel_1->setObjectName("LLabel_1");

        gridLayout->addWidget(LLabel_1, 2, 0, 1, 1);

        LLabel_3 = new QLabel(Widget);
        LLabel_3->setObjectName("LLabel_3");

        gridLayout->addWidget(LLabel_3, 4, 0, 1, 1);

        Left_3 = new QSpinBox(Widget);
        Left_3->setObjectName("Left_3");

        gridLayout->addWidget(Left_3, 4, 1, 1, 1);

        LeftCB = new QComboBox(Widget);
        LeftCB->setObjectName("LeftCB");

        gridLayout->addWidget(LeftCB, 1, 0, 1, 2);

        Left_1 = new QSpinBox(Widget);
        Left_1->setObjectName("Left_1");

        gridLayout->addWidget(Left_1, 2, 1, 1, 1);

        Left_2 = new QSpinBox(Widget);
        Left_2->setObjectName("Left_2");

        gridLayout->addWidget(Left_2, 3, 1, 1, 1);

        LLabel_2 = new QLabel(Widget);
        LLabel_2->setObjectName("LLabel_2");

        gridLayout->addWidget(LLabel_2, 3, 0, 1, 1);

        Left_4 = new QSpinBox(Widget);
        Left_4->setObjectName("Left_4");

        gridLayout->addWidget(Left_4, 5, 1, 1, 1);

        LLabel_4 = new QLabel(Widget);
        LLabel_4->setObjectName("LLabel_4");

        gridLayout->addWidget(LLabel_4, 5, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        Mid_4 = new QSpinBox(Widget);
        Mid_4->setObjectName("Mid_4");

        gridLayout_2->addWidget(Mid_4, 5, 1, 1, 1);

        CentralCB = new QComboBox(Widget);
        CentralCB->setObjectName("CentralCB");

        gridLayout_2->addWidget(CentralCB, 1, 0, 1, 2);

        Mid_1 = new QSpinBox(Widget);
        Mid_1->setObjectName("Mid_1");

        gridLayout_2->addWidget(Mid_1, 2, 1, 1, 1);

        MLabel_4 = new QLabel(Widget);
        MLabel_4->setObjectName("MLabel_4");

        gridLayout_2->addWidget(MLabel_4, 5, 0, 1, 1);

        MLabel_1 = new QLabel(Widget);
        MLabel_1->setObjectName("MLabel_1");

        gridLayout_2->addWidget(MLabel_1, 2, 0, 1, 1);

        Mid_2 = new QSpinBox(Widget);
        Mid_2->setObjectName("Mid_2");

        gridLayout_2->addWidget(Mid_2, 3, 1, 1, 1);

        MLabel_3 = new QLabel(Widget);
        MLabel_3->setObjectName("MLabel_3");

        gridLayout_2->addWidget(MLabel_3, 4, 0, 1, 1);

        MLabel_2 = new QLabel(Widget);
        MLabel_2->setObjectName("MLabel_2");

        gridLayout_2->addWidget(MLabel_2, 3, 0, 1, 1);

        Mid_3 = new QSpinBox(Widget);
        Mid_3->setObjectName("Mid_3");

        gridLayout_2->addWidget(Mid_3, 4, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        Right_1 = new QSpinBox(Widget);
        Right_1->setObjectName("Right_1");

        gridLayout_3->addWidget(Right_1, 2, 1, 1, 1);

        RLabel_3 = new QLabel(Widget);
        RLabel_3->setObjectName("RLabel_3");

        gridLayout_3->addWidget(RLabel_3, 4, 0, 1, 1);

        RightCB = new QComboBox(Widget);
        RightCB->setObjectName("RightCB");

        gridLayout_3->addWidget(RightCB, 1, 0, 1, 2);

        Right_2 = new QSpinBox(Widget);
        Right_2->setObjectName("Right_2");

        gridLayout_3->addWidget(Right_2, 3, 1, 1, 1);

        RLabel_2 = new QLabel(Widget);
        RLabel_2->setObjectName("RLabel_2");

        gridLayout_3->addWidget(RLabel_2, 3, 0, 1, 1);

        Right_3 = new QSpinBox(Widget);
        Right_3->setObjectName("Right_3");

        gridLayout_3->addWidget(Right_3, 4, 1, 1, 1);

        RLabel_1 = new QLabel(Widget);
        RLabel_1->setObjectName("RLabel_1");

        gridLayout_3->addWidget(RLabel_1, 2, 0, 1, 1);

        RLabel_4 = new QLabel(Widget);
        RLabel_4->setObjectName("RLabel_4");

        gridLayout_3->addWidget(RLabel_4, 5, 0, 1, 1);

        Right_4 = new QSpinBox(Widget);
        Right_4->setObjectName("Right_4");

        gridLayout_3->addWidget(Right_4, 5, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        SliderLabel_1 = new QLabel(Widget);
        SliderLabel_1->setObjectName("SliderLabel_1");

        gridLayout_4->addWidget(SliderLabel_1, 0, 0, 1, 1);

        SliderLabel_2 = new QLabel(Widget);
        SliderLabel_2->setObjectName("SliderLabel_2");

        gridLayout_4->addWidget(SliderLabel_2, 1, 0, 1, 1);

        SliderLabel_4 = new QLabel(Widget);
        SliderLabel_4->setObjectName("SliderLabel_4");

        gridLayout_4->addWidget(SliderLabel_4, 3, 0, 1, 1);

        SliderLabel_3 = new QLabel(Widget);
        SliderLabel_3->setObjectName("SliderLabel_3");

        gridLayout_4->addWidget(SliderLabel_3, 2, 0, 1, 1);

        Slider_3 = new QSlider(Widget);
        Slider_3->setObjectName("Slider_3");
        Slider_3->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(Slider_3, 2, 1, 1, 1);

        Slider_4 = new QSlider(Widget);
        Slider_4->setObjectName("Slider_4");
        Slider_4->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(Slider_4, 3, 1, 1, 1);

        Slider_1 = new QSlider(Widget);
        Slider_1->setObjectName("Slider_1");
        Slider_1->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(Slider_1, 0, 1, 1, 1);

        Slider_2 = new QSlider(Widget);
        Slider_2->setObjectName("Slider_2");
        Slider_2->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(Slider_2, 1, 1, 1, 1);

        colorButton = new QPushButton(Widget);
        colorButton->setObjectName("colorButton");

        gridLayout_4->addWidget(colorButton, 4, 0, 1, 2);


        verticalLayout->addLayout(gridLayout_4);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        ColorRect->setText(QString());
        LLabel_1->setText(QCoreApplication::translate("Widget", "R:", nullptr));
        LLabel_3->setText(QCoreApplication::translate("Widget", "B:", nullptr));
        LLabel_2->setText(QCoreApplication::translate("Widget", "G:", nullptr));
        LLabel_4->setText(QString());
        MLabel_4->setText(QCoreApplication::translate("Widget", "K:", nullptr));
        MLabel_1->setText(QCoreApplication::translate("Widget", "C:", nullptr));
        MLabel_3->setText(QCoreApplication::translate("Widget", "Y:", nullptr));
        MLabel_2->setText(QCoreApplication::translate("Widget", "M:", nullptr));
        RLabel_3->setText(QCoreApplication::translate("Widget", "V:", nullptr));
        RLabel_2->setText(QCoreApplication::translate("Widget", "S:", nullptr));
        RLabel_1->setText(QCoreApplication::translate("Widget", "H:", nullptr));
        RLabel_4->setText(QString());
        SliderLabel_1->setText(QCoreApplication::translate("Widget", "R:", nullptr));
        SliderLabel_2->setText(QCoreApplication::translate("Widget", "G:", nullptr));
        SliderLabel_4->setText(QString());
        SliderLabel_3->setText(QCoreApplication::translate("Widget", "B:", nullptr));
        colorButton->setText(QCoreApplication::translate("Widget", "Choose color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
