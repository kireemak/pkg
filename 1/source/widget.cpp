#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(400,400);

    color_converter = new QColor();
    spaceId = space_name::rgb;
    spaces = {space_name::rgb, space_name::cmyk, space_name::hsv, space_name::hls, space_name::xyz, space_name::lab};

    ui->ColorRect->setStyleSheet("QLabel{background-color:rgb(0,0,0);border:2px solid black;}");

    ui->Slider_1->setRange(0,255);
    ui->Slider_2->setRange(0,255);
    ui->Slider_3->setRange(0,255);
    ui->Slider_4->setVisible(false);

    connect(ui->Slider_1, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
    connect(ui->Slider_2, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
    connect(ui->Slider_3, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
    connect(ui->Slider_4, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));

    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(chooseColor()));

    ui->Left_1->setRange(0, 255);
    ui->Left_2->setRange(0, 255);
    ui->Left_3->setRange(0, 255);
    ui->Left_4->setVisible(false);

    ui->Mid_1->setReadOnly(true);
    ui->Mid_2->setReadOnly(true);
    ui->Mid_3->setReadOnly(true);
    ui->Mid_4->setReadOnly(true);
    ui->Mid_1->setRange(0, 255);
    ui->Mid_2->setRange(0, 255);
    ui->Mid_3->setRange(0, 255);
    ui->Mid_4->setVisible(true);

    ui->Right_1->setReadOnly(true);
    ui->Right_2->setReadOnly(true);
    ui->Right_3->setReadOnly(true);
    ui->Right_4->setReadOnly(true);
    ui->Right_1->setRange(0, 359);
    ui->Right_2->setRange(0, 255);
    ui->Right_3->setRange(0, 255);
    ui->Right_4->setVisible(false);

    connect(ui->Left_1, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
    connect(ui->Left_2, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
    connect(ui->Left_3, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
    connect(ui->Left_4, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));

    SetLeftNames("RGB");

    ui->LeftCB->addItem("RGB");
    ui->LeftCB->addItem("CMYK");
    ui->LeftCB->addItem("HSV");
    ui->LeftCB->addItem("HLS");
    ui->LeftCB->addItem("XYZ");
    ui->LeftCB->addItem("LAB");

    ui->CentralCB->addItem("CMYK");
    ui->CentralCB->addItem("HSV");
    ui->CentralCB->addItem("RGB");
    ui->CentralCB->addItem("HLS");
    ui->CentralCB->addItem("LAB");
    ui->CentralCB->addItem("XYZ");

    ui->RightCB->addItem("HSV");
    ui->RightCB->addItem("CMYK");
    ui->RightCB->addItem("HLS");
    ui->RightCB->addItem("RGB");
    ui->RightCB->addItem("XYZ");
    ui->RightCB->addItem("LAB");

    connect(ui->LeftCB,SIGNAL(currentTextChanged(QString)),this,SLOT(SetLeftNames(QString)));
    connect(ui->CentralCB,SIGNAL(currentTextChanged(QString)),this,SLOT(SetMidNames(QString)));
    connect(ui->RightCB,SIGNAL(currentTextChanged(QString)),this,SLOT(SetRightNames(QString)));
}

void Widget::slidersMoved(int a)
{
    if(sliderChangedManual)
    {
        sliderChangedManual=false;
        return;
    }
    int val1= ui->Slider_1->value();
    int val2= ui->Slider_2->value();
    int val3= ui->Slider_3->value();
    int val4=-1;
    if(ui->Slider_4->isVisible())
    {
        val4=ui->Slider_4->value();
    }

    SetColor(spaceId, val1, val2, val3, val4);
    setSpacesAndLabel();
}

void Widget::spinsChanged(int a)
{
    if(spinChangedManual)
    {
        spinChangedManual=false;
        return;
    }
    int val1= ui->Left_1->value();
    int val2= ui->Left_2->value();
    int val3= ui->Left_3->value();
    int val4=-1;
    if(ui->Left_4->isVisible())
    {
        val4=ui->Left_4->value();
    }

    SetColor(spaceId, val1, val2, val3, val4);
    setSpinsAndLabel();
    QVector<int> values = {val1, val2, val3, val4};
    setSliders(values);
}



void Widget::SetLeftNames(QString text)
{
    ui->Slider_2->setMaximum(255);
    ui->Slider_3->setMaximum(255);
    if(text=="RGB")
    {
        spaceId = space_name::rgb;
        spaces[0]=space_name::rgb;

        ui->LLabel_1->setText("R:");
        ui->LLabel_2->setText("G:");
        ui->LLabel_3->setText("B:");
        ui->LLabel_4->setText("");

        ui->SliderLabel_1->setText("R:");
        ui->SliderLabel_2->setText("G:");
        ui->SliderLabel_3->setText("B:");
        ui->SliderLabel_4->setText("");

        FirstSliderSetRange();
        FirstSpinSetRange(ui->Left_1);

        if(ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(false);
        }

        if(ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(false);
        }
    }
    if(text=="CMYK")
    {
        spaceId = space_name::cmyk;
        spaces[0]=space_name::cmyk;
        FirstSliderSetRange();
        FirstSpinSetRange(ui->Left_1);
        ui->Left_4->setRange(0, 255);
        ui->LLabel_1->setText("C:");
        ui->LLabel_2->setText("M:");
        ui->LLabel_3->setText("Y:");
        ui->LLabel_4->setText("K:");

        ui->SliderLabel_1->setText("C:");
        ui->SliderLabel_2->setText("M:");
        ui->SliderLabel_3->setText("Y:");
        ui->SliderLabel_4->setText("K:");

        if(!ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(true);
        }

        if(!ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(true);
        }

        ui->Slider_4->setRange(0,255);
    }
    if(text=="HSV")
    {
        spaceId = space_name::hsv;
        spaces[0]=space_name::hsv;
        FirstSliderSetRange(true);
        FirstSpinSetRange(ui->Left_1, true);
        ui->LLabel_1->setText("H:");
        ui->LLabel_2->setText("S:");
        ui->LLabel_3->setText("V:");
        ui->LLabel_4->setText("");

        ui->SliderLabel_1->setText("H:");
        ui->SliderLabel_2->setText("S:");
        ui->SliderLabel_3->setText("V:");
        ui->SliderLabel_4->setText("");

        if(ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(false);
        }

        if(ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(false);
        }
    }
    if(text=="HLS")
    {
        spaceId = space_name::hls;
        spaces[0]=space_name::hls;
        FirstSliderSetRange(true);
        FirstSpinSetRange(ui->Left_1, true);
        ui->LLabel_1->setText("H:");
        ui->LLabel_2->setText("L:");
        ui->LLabel_3->setText("S:");
        ui->LLabel_4->setText("");

        ui->SliderLabel_1->setText("H:");
        ui->SliderLabel_2->setText("L:");
        ui->SliderLabel_3->setText("S:");
        ui->SliderLabel_4->setText("");

        if(ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(false);
        }

        if(ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(false);
        }
    }
    if(text=="XYZ")
    {
        spaceId = space_name::xyz;
        spaces[0]=space_name::xyz;
        ui->Left_1->setMaximum(95);
        ui->Slider_1->setMaximum(95);
        ui->Slider_2->setMaximum(100);
        ui->Slider_3->setMaximum(108);
        ui->LLabel_1->setText("X:");
        ui->LLabel_2->setText("Y:");
        ui->LLabel_3->setText("Z:");
        ui->LLabel_4->setText("");

        ui->SliderLabel_1->setText("X:");
        ui->SliderLabel_2->setText("Y:");
        ui->SliderLabel_3->setText("Z:");
        ui->SliderLabel_4->setText("");

        if(ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(false);
        }

        if(ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(false);
        }
    }
    if(text=="LAB")
    {
        spaceId = space_name::lab;
        ui->Left_1->setRange(0,100);
        ui->Left_2->setRange(-128,127);
        ui->Left_3->setRange(-128,127);
        spaces[0] = space_name::lab;
        ui->LLabel_1->setText("L:");
        ui->LLabel_2->setText("A:");
        ui->LLabel_3->setText("B:");
        ui->LLabel_4->setText("");

        ui->SliderLabel_1->setText("L:");
        ui->SliderLabel_2->setText("A:");
        ui->SliderLabel_3->setText("B:");
        ui->SliderLabel_4->setText("");
        ui->Slider_1->setRange(0,100);
        ui->Slider_2->setRange(-128,127);
        ui->Slider_3->setRange(-128,127);

        if(ui->Left_4->isVisible())
        {
            ui->Left_4->setVisible(false);
        }

        if(ui->Slider_4->isVisible())
        {
            ui->Slider_4->setVisible(false);
        }
    }
    setSliders(getValues(spaceId));
    QVector<int> empty;
    setSpinBoxes(getValues(spaceId),empty,empty);
}

void Widget::SetMidNames(QString text)
{
    ui->Mid_2->setRange(0,255);
    ui->Mid_3->setRange(0,255);
    if(text=="LAB")
    {
        ui->Mid_2->setRange(-128,127);
        ui->Mid_3->setRange(-128,127);
        spaces[1]= space_name::lab;
        ui->MLabel_1->setText("L:");
        ui->MLabel_2->setText("A:");
        ui->MLabel_3->setText("B:");
        ui->MLabel_4->setText("");
        if(ui->Mid_4->isVisible())
        {
            ui->Mid_4->setVisible(false);
        }
    }
    if(text=="RGB")
    {
        spaces[1] = space_name::rgb;
        FirstSpinSetRange(ui->Mid_1);
        ui->MLabel_1->setText("R:");
        ui->MLabel_2->setText("G:");
        ui->MLabel_3->setText("B:");
        ui->MLabel_4->setText("");
        if(ui->Mid_4->isVisible())
        {
            ui->Mid_4->setVisible(false);
        }
    }
    if(text=="CMYK")
    {
        spaces[1]= space_name::cmyk;
        FirstSpinSetRange(ui->Mid_1);
        ui->Mid_4->setRange(0, 255);
        ui->Mid_4->setVisible(true);
        ui->MLabel_1->setText("C:");
        ui->MLabel_2->setText("M:");
        ui->MLabel_3->setText("Y:");
        ui->MLabel_4->setText("K:");
    }
    if(text=="HSV")
    {
        spaces[1] = space_name::hsv;
        FirstSpinSetRange(ui->Mid_1, true);
        ui->MLabel_1->setText("H:");
        ui->MLabel_2->setText("S:");
        ui->MLabel_3->setText("V:");
        ui->MLabel_4->setText("");
        if(ui->Mid_4->isVisible())
        {
            ui->Mid_4->setVisible(false);
        }
    }
    if(text=="XYZ")
    {
        spaces[1]= space_name::xyz;
        ui->MLabel_1->setText("X:");
        ui->MLabel_2->setText("Y:");
        ui->MLabel_3->setText("Z:");
        ui->MLabel_4->setText("");
        if(ui->Mid_4->isVisible())
        {
            ui->Mid_4->setVisible(false);
        }
    }
    if(text=="HLS")
    {
        spaces[1] = space_name::hls;
        FirstSpinSetRange(ui->Mid_1, true);
        ui->MLabel_1->setText("H:");
        ui->MLabel_2->setText("L:");
        ui->MLabel_3->setText("S:");
        ui->MLabel_4->setText("");
        if(ui->Mid_4->isVisible())
        {
            ui->Mid_4->setVisible(false);
        }
    }
}

void Widget::SetRightNames(QString text)
{
    ui->Right_2->setRange(0,255);
    ui->Right_3->setRange(0,255);
    if(text=="LAB")
    {
        ui->Right_2->setRange(-128,127);
        ui->Right_3->setRange(-128,127);
        spaces[2] = space_name::lab;
        ui->RLabel_1->setText("L:");
        ui->RLabel_2->setText("A:");
        ui->RLabel_3->setText("B:");
        ui->RLabel_4->setText("");
        if(ui->Right_4->isVisible())
        {
            ui->Right_4->setVisible(false);
        }
    }

    if(text=="RGB")
    {
        spaces[2] = space_name::rgb;
        FirstSpinSetRange(ui->Right_1);
        ui->RLabel_1->setText("R:");
        ui->RLabel_2->setText("G:");
        ui->RLabel_3->setText("B:");
        ui->RLabel_4->setText("");
        if(ui->Right_4->isVisible())
        {
            ui->Right_4->setVisible(false);
        }
    }
    if(text=="CMYK")
    {
        spaces[2]= space_name::cmyk;
        FirstSpinSetRange(ui->Right_1);
        ui->Right_4->setRange(0, 255);
        ui->Right_4->setVisible(true);
        ui->RLabel_1->setText("C:");
        ui->RLabel_2->setText("M:");
        ui->RLabel_3->setText("Y:");
        ui->RLabel_4->setText("K:");
    }
    if(text=="HSV")
    {
        spaces[2] = space_name::hsv;
        FirstSpinSetRange(ui->Right_1, true);
        ui->RLabel_1->setText("H:");
        ui->RLabel_2->setText("S:");
        ui->RLabel_3->setText("V:");
        ui->RLabel_4->setText("");
        if(ui->Right_4->isVisible())
        {
            ui->Right_4->setVisible(false);
        }
    }
    if(text=="XYZ")
    {
        spaces[2] = space_name::xyz;
        ui->RLabel_1->setText("X:");
        ui->RLabel_2->setText("Y:");
        ui->RLabel_3->setText("Z:");
        ui->RLabel_4->setText("");
        if(ui->Right_4->isVisible())
        {
            ui->Right_4->setVisible(false);
        }
    }
    if(text=="HLS")
    {
        spaces[2] = space_name::hls;
        FirstSpinSetRange(ui->Right_1, true);
        ui->RLabel_1->setText("H:");
        ui->RLabel_2->setText("L:");
        ui->RLabel_3->setText("S:");
        ui->RLabel_4->setText("");
        if(ui->Right_4->isVisible())
        {
            ui->Right_4->setVisible(false);
        }
    }
}

void Widget::FirstSliderSetRange(bool hueSpace)
{
    int max = 255;
    if(hueSpace) max = 359;
    ui->Slider_1->setMaximum(max);
}

void Widget::FirstSpinSetRange(QSpinBox* spin, bool hueSpace)
{
    int max = 255;
    if(hueSpace) max = 359;
    spin->setMaximum(max);
}


void Widget::setSliders(QVector<int> valuesLeft)
{
    sliderChangedManual = true;
    ui->Slider_1->setValue((valuesLeft[0]));
    sliderChangedManual = true;
    ui->Slider_2->setValue((valuesLeft[1]));
    sliderChangedManual = true;
    ui->Slider_3->setValue((valuesLeft[2]));
    if(ui->Slider_4->isVisible())
    {
        sliderChangedManual = true;
        ui->Slider_4->setValue((valuesLeft[3]));
    }
}

QVector <int> Widget::getValues(space_name value_id)
{
    QVector<int> values;
    switch(value_id)
    {
        case space_name::rgb:
        {
            values.push_back(color_converter->red());
            values.push_back(color_converter->green());
            values.push_back(color_converter->blue());
            break;
        }
        case space_name::cmyk:
        {
            int c,m,y,k;
            color_converter->getCmyk(&c,&m,&y,&k);
            values= {c,m,y,k};
            break;
        }
        case space_name::hsv:
        {
            int h,s,v;
            color_converter->getHsv(&h,&s,&v);
            values= {h,s,v};
            break;
        }
        case space_name::hls:
        {
            int h,l,s;
            color_converter->getHsl(&h,&s,&l);
            values= {h,l,s};
            break;
        }
        case space_name::xyz:
        {
            double X,Y,Z;
            double r = color_converter->red();
            double g = color_converter->green();
            double b = color_converter->blue();

            double Rn, Gn, Bn;
            Rn = qMin(qMax(0.0, RGBconvertXYZ (r / 255.0) *100.0), 100.0);
            Gn = qMin(qMax(0.0, RGBconvertXYZ (g / 255.0) *100.0), 100.0);
            Bn = qMin(qMax(0.0, RGBconvertXYZ (b / 255.0) *100.0), 100.0);

            X = 0.412453*Rn + 0.357580*Gn + 0.180423* Bn;
            Y = 0.212671*Rn + 0.715160*Gn + 0.072169*Bn;
            Z = 0.019334*Rn + 0.119193*Gn + 0.950227*Bn;

            values= {int(X),int(Y),int(Z)};
            break;
        }
        case space_name::lab:
        {
            double L,A,B;
            double X,Y,Z;
            double r = color_converter->red();
            double g = color_converter->green();
            double b = color_converter->blue();

            double Rn, Gn, Bn;
            Rn = RGBconvertXYZ (r / 255.0) *100.0;
            Gn = RGBconvertXYZ (g / 255.0) *100.0;
            Bn = RGBconvertXYZ (b / 255.0) *100.0;

            X= 0.412453*Rn + 0.357580*Gn + 0.18042* Bn;
            Y= 0.212671*Rn + 0.715160*Gn + 0.072169*Bn;
            Z= 0.019334*Rn + 0.119193*Gn + 0.950227*Bn;

            double Xw = 95.047;
            double Yw = 100.0;
            double Zw = 108.883;

            L = 116.0 * XYZconvertLAB(Y/Yw) -16.0;
            A = 500.0 *(XYZconvertLAB(X/Xw) - XYZconvertLAB(Y/Yw));
            B = 200.0 *(XYZconvertLAB(Y/Yw) - XYZconvertLAB(Z/Zw));

            values= {int(L),int(A),int(B)};
            break;
        }
    }

    return values;
}

void Widget::setSpinBoxes(QVector<int> valuesLeft, QVector<int> valuesMid, QVector<int> valuesRight)
{
    if(!valuesLeft.empty())
    {
        spinChangedManual = true;
        ui->Left_1->setValue((valuesLeft[0]));
        spinChangedManual = true;
        ui->Left_2->setValue((valuesLeft[1]));
        spinChangedManual = true;
        ui->Left_3->setValue((valuesLeft[2]));
        if(ui->Left_4->isVisible())
        {
            spinChangedManual = true;
            ui->Left_4->setValue((valuesLeft[3]));
        }
    }

    if(valuesMid.empty()) return;
    spinChangedManual = true;
    ui->Mid_1->setValue((valuesMid[0]));
    spinChangedManual = true;
    ui->Mid_2->setValue((valuesMid[1]));
    spinChangedManual = true;
    ui->Mid_3->setValue((valuesMid[2]));
    if(ui->Mid_4->isVisible())
    {
        spinChangedManual = true;
        ui->Mid_4->setValue((valuesMid[3]));
    }

    if(valuesRight.empty()) return;
    spinChangedManual = true;
    ui->Right_1->setValue((valuesRight[0]));
    spinChangedManual = true;
    ui->Right_2->setValue((valuesRight[1]));
    spinChangedManual = true;
    ui->Right_3->setValue((valuesRight[2]));
    if(ui->Right_4->isVisible())
    {
        spinChangedManual = true;
        ui->Right_4->setValue((valuesRight[3]));
    }
}


double Widget::RGBconvertXYZ(double a)
{
    double x=a;
    if(x>= 0.04045)
    {
        return pow((x+0.055)/1.055,2.4);
    }
    else return (x/12.92);

}

double Widget::XYZconvertLAB(double a)
{
    double x=a;
    if(x>= 0.008856)
    {
        return pow(x,1.0/3.0);
    }
    else return (7.787*x + 16.0/116.0);
}

double Widget::XYZconvertRGB(double a)
{
    double x=a;
    if(x >= 0.0031308)
    {
        return (1.055*pow(x,1.0/2.4)-0.055);
    }
    else return 12.92*x;
}

double Widget::LABconvertXYZ(double a)
{
    double x = a;
    if(pow(x,3)>= 0.008856)
    {
        return pow(x,3);
    }
    else return (x-16.0/116.0)/7.787;
}

void Widget::setSpinsAndLabel()
{
    QVector<int> valuesLeft;
    QVector<int> valuesMid=getValues(spaces[1]);
    QVector<int> valuesRight=getValues(spaces[2]);

    setSpinBoxes(valuesLeft, valuesMid, valuesRight);
    setColorLabel();
}

void Widget::setSpacesAndLabel()
{
    QVector<int> valuesLeft=getValues(spaces[0]);
    QVector<int> valuesMid=getValues(spaces[1]);
    QVector<int> valuesRight=getValues(spaces[2]);

    setSpinBoxes(valuesLeft, valuesMid, valuesRight);
    setColorLabel();
}

void Widget::SetColor(space_name value_id, int a,int b,int c, int d)
{
    switch(value_id)
    {
    case space_name::rgb:
    {
        color_converter->setRed(a);
        color_converter->setGreen(b);
        color_converter->setBlue(c);
        break;
    }
    case space_name::cmyk:
    {
        color_converter->setCmyk(a,b,c,d);
        break;
    }
    case space_name::hsv:
    {
        color_converter->setHsv(a,b,c);
        break;
    }
    case space_name::hls:
    {
        color_converter->setHsl(a,c,b);
        break;
    }
    case space_name::xyz:
    {
        double x = a;
        double y_ = b;
        double z = c;
        double Rn = 0.032406 *x - 0.015372*y_ -0.004986* z;
        double Gn = -0.009689 *x + 0.018758 *y_ + 0.000415 * z;
        double Bn= 0.000557 *x - 0.002040 *y_ + 0.010570 * z;


        double R= qMin(qMax(0.0,XYZconvertRGB(Rn)*255), 255.0);
        double G= qMin(qMax(0.0, XYZconvertRGB(Gn)*255), 255.0);
        double B= qMin(qMax(0.0, XYZconvertRGB(Bn)*255), 255.0);

        color_converter->setRed(R);
        color_converter->setGreen(G);
        color_converter->setBlue(B);

        break;
    }
    case space_name::lab:
    {
        double Xw = 95.047;
        double Yw = 100.0;
        double Zw = 108.883;
        double L=a;
        double A=b;
        double B=c;
        double Y = LABconvertXYZ((L+16.0)/116.0)*Yw;
        double X = LABconvertXYZ(A/500.0 + (L+16.0)/116.0)*Xw;
        double Z = LABconvertXYZ((L+16.0)/116.0 - B/200.0)*Zw;

        double Rn = 0.032406 *X - 0.015372*Y -0.004986* Z;
        double Gn = -0.009689 *X + 0.018758 *Y + 0.000415 * Z;
        double Bn = 0.000557 *X - 0.002040 *Y + 0.010570 * Z;

        double R= XYZconvertRGB(Rn)*255;
        double G= XYZconvertRGB(Gn)*255;
        double B_= XYZconvertRGB(Bn)*255;
        color_converter->setRed(R);
        color_converter->setGreen(G);
        color_converter->setBlue(B_);

        break;
    }
    }
}

void Widget::setColorLabel()
{
    r = QString::number(color_converter->red());
    g = QString::number(color_converter->green());
    b = QString::number(color_converter->blue());

    ui->ColorRect->setStyleSheet("QLabel{"
                             "background-color:rgb("+r+","+g+","+b+");"
                                                       "}");
}

void Widget::chooseColor()
{
    QColor temp = QColorDialog::getColor();
    SetColor(space_name::rgb, temp.red(), temp.green(), temp.blue());
    setSpacesAndLabel();
}

Widget::~Widget()
{
    delete ui;
}
