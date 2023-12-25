#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>

//#include<iostream>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



//this class stores and transforms the points
class Point3D
{
    //Point coordinates will be stored there
    double* coordinates;

public:
    //constructors (default and by coordinates)
    Point3D();
    Point3D(double x, double y, double z);
    Point3D(Point3D& otherPoint);
    ~Point3D();

    //setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    void setAll(double x, double y, double z);

    //getters
    double x();
    double y();
    double z();

    //multiplies the point on transformation matrix to get its new value
    void transform(double** transformMatrix/*, int rows, int cols*/);
};

class Point2D
{
    //Point coordinates will be stored there
    double* coordinates;

public:
    //constructors (default and by coordinates)
    Point2D();
    Point2D(double x, double y);
    ~Point2D();

    //setters
    void setX(double x);
    void setY(double y);

    void setAll(double x, double y);



    //getters
    double x() {return coordinates[0];}
    double y() {return coordinates[1];}

    //gets a projection of a 3D point (the default plane is "Z=0")
    void getFromPoint3D (Point3D point);
};



//this class prints out the image (the camera plane is "Z=0")
class Viewport : public QWidget
{
private:

    void paintEvent(QPaintEvent*);

public:

    //coordinates issues
    double zeroX, zeroY;
    double scaleValue;

    //transformation matrix
    double** transformMatrix;
    //double** tempMatrix;

    Point3D centerPoint;    //information about the center of the point
    Point3D* carcassPoints;   //basic points to draw lines between them to get the figure
    Point2D* projectionCarcassPoints; //the projections of basic points will be there

    Viewport(QWidget *parent = nullptr);
    ~Viewport();

    friend class MainWindow;

};




class MainWindow : public QMainWindow

{
    Q_OBJECT

public:

    Viewport* viewPtr;

    //arguments input addresses
    QDoubleSpinBox* arg1;
    QDoubleSpinBox* arg2;
    QDoubleSpinBox* arg3;

    //transformation flags
    bool move = true;
    bool rotate = false;
    bool scale = false;

    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    void processButtonClicked();

    void movingOptButtonClicked();
    void rotatingOptButtonClicked();
    void scalingOptButtonClicked();
};


#endif // MAINWINDOW_H
