#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QGridLayout>
#include <QListView>
#include <QImageWriter>
#include <QTableWidget>
#include <QFileDialog>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool line_changed=false;
    QFileSystemModel *fileSystemModel;
    QGridLayout *backgr;
    QListView *listView;
    QTableWidget *tableViewInfo = nullptr;
    int *sortСolumns = new int[5];

public slots:
    void listDoubleClicked(const QModelIndex &index);
    void sortSelected(int logicalIndex);
    void dialogClose();
    void multiChoice();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
