#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QColor>
#include <QApplication>
#include <QComboBox>
#include <QPushButton>
#include <QString>
#include <QSpinBox>
#include <QtMath>
#include <QColorDialog>

enum space_name
{
    rgb=0,
    cmyk,
    hsv,
    xyz,
    hls,
    lab
};

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:

public slots:
    void SetLeftNames(QString text);
    void SetMidNames(QString text);
    void SetRightNames(QString text);
    void spinsChanged(int a);
    void slidersMoved(int a);
    void setSpinsAndLabel();
    void setSpacesAndLabel();
    void setColorLabel();
    void chooseColor();
    void SetColor(space_name value_id, int a,int b,int c, int d = -1);
    void setSliders(QVector<int> valuesLeft);
    QVector <int> getValues(space_name value_id);
    void setSpinBoxes(QVector<int> valuesLeft, QVector<int> valuesMid, QVector<int> valuesRight);


private:
    QColor *color_converter;
    space_name spaceId;
    QVector<space_name> spaces;
    bool spinChangedManual=false;
    bool sliderChangedManual = false;

    QString r;
    QString g;
    QString b;

    double RGBconvertXYZ(double a);
    double XYZconvertLAB(double a);

    double XYZconvertRGB(double a);
    double LABconvertXYZ(double a);

    void FirstSliderSetRange(bool hueSpace = false);
    void FirstSpinSetRange(QSpinBox* spin, bool hueSpace = false);

    Ui::Widget *ui;
};
#endif // WIDGET_H
