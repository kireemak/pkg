#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPoint>
#include <QPair>
#include <QPainter>
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <QException>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_activated(int index);

    void on_selectDirectoryB_clicked();

private:
    Ui::MainWindow *ui;

    QVector<QPair<QPointF,QPointF>> segments;
    QVector<QPointF> polygon;
    double Xmin, Ymin, Xmax, Ymax;
    QVector<QVector<QPair<QPointF,QPointF>>> cutSegments(QVector<QPair<QPointF,QPointF>>);
    QVector<QPointF> cutPolygon(QVector<QPointF>);
    QVector<QPair<QPointF, QPointF>> clipSegmentsMidpoint(const QPointF& P1, const QPointF& P2, int regionCode1, int regionCode2);
    int getCode(QPointF);
    QPointF intersectionPoint(QPointF P1, QPointF P2, int border = -1);
    bool clipMidpoint(QPointF P1, QPointF P2);
    bool isValidIntersection(QPointF intersection, QPointF P1, QPointF P2);
    void paintEvent(QPaintEvent*);
    int scale;
    bool ready_ = 0;

};
#endif // MAINWINDOW_H
