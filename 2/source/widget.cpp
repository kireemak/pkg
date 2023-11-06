#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget),
    fileSystemModel(new QFileSystemModel(this)),
    tableViewInfo(nullptr)
{
    fileSystemModel->setRootPath("");
    fileSystemModel->setFilter(QDir::AllEntries);

    for(int i = 0; i < 5; i++)
        sortСolumns[i] = 0;

    ui->setupUi(this);
    ui->listView->setModel(fileSystemModel);
    ui->lineEdit->setText(" ");
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(listDoubleClicked(QModelIndex)));
    connect(ui->multiChoice, SIGNAL(clicked()), this, SLOT(multiChoice()));
}

void Widget::listDoubleClicked(const QModelIndex &index)
{
    QListView* listView = qobject_cast<QListView*>(sender());
    if (!listView) return;

    QFileInfo fileInfo = fileSystemModel->fileInfo(index);
    ui->lineEdit->setText(fileSystemModel->filePath(index));

    if (fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        fileSystemModel->setRootPath(dir.absolutePath());
        listView->setRootIndex(fileSystemModel->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName() == ".")
    {
        fileSystemModel->setRootPath("");
        listView->setRootIndex(fileSystemModel->index(""));
    }
    else if(fileInfo.isDir())
    {
        listView->setRootIndex(index);
    }
    else if(!fileInfo.isDir())
    {
        QString fileExt = fileSystemModel->fileName(index);
        QImageWriter a(fileSystemModel->filePath(index));
        QString resolution = "";
        QImage img (fileSystemModel->filePath(index));

        for(int i = fileExt.lastIndexOf('.'); i < fileExt.size(); i++)
        {
            resolution.append(fileExt[i]);
        }
        if (resolution == ".JPG" || resolution == ".jpg" || resolution == ".gif" || resolution == ".tif" || resolution == ".bmp" ||
                resolution == ".png" || resolution == ".pcx" || resolution == ".BMP")
        {
            ui->FileName->setText(fileSystemModel->fileName(index));
            ui->Size->setText(QString::number(img.size().width() )+ "x" + QString::number(img.size().height() ));
            ui->Contraction->setText(QString::number(a.compression()));
            ui->Color_depth->setText(QString::number(img.bitPlaneCount()));
            ui->Resolution->setText(QString::number(img.physicalDpiX()));
        }
    }
}

void Widget::multiChoice()
{
    QFileDialog *files = new QFileDialog;
    files->setWindowTitle("Open the files");
    QList<QUrl> list = files->getOpenFileUrls();
    QDialog *table = new QDialog();
    table->setWindowTitle("Table");
    table->setWindowIcon(QPixmap(":/img/folder.png"));
    QGridLayout *tableLayout = new QGridLayout(table);
    table->setMinimumSize(700,700);
    tableViewInfo = new QTableWidget(table);
    tableLayout->addWidget(tableViewInfo);
    tableViewInfo->setColumnCount(5);
    tableViewInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableViewInfo->setRowCount(list.size());
    QStringList headers = {"Name", "Size", "Extension", "Color Depth", "Compression"};
    tableViewInfo->setHorizontalHeaderLabels(headers);
    tableViewInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < list.size(); i++)
    {
        QFile temp(list[i].toLocalFile());
        QString resolution = "";

        if (temp.fileName().lastIndexOf('.') == -1)
        {
            tableViewInfo->setRowCount(tableViewInfo->rowCount()-1);
            continue;
        }

        for(int i = temp.fileName().lastIndexOf('.'); i < temp.fileName().size(); i++)
        {
            resolution.append(temp.fileName()[i]);
        }

        if (resolution != ".jpg" && resolution != ".gif" && resolution != ".tif" && resolution != ".bmp" &&
                resolution != ".png" && resolution != ".pcx" && resolution != ".BMP")
        {
            tableViewInfo->setRowCount(tableViewInfo->rowCount()-1);
            continue;
        }

        tableViewInfo->setItem(i, 2, new QTableWidgetItem(resolution));
        QString fileName = "";
        for(int i = temp.fileName().lastIndexOf('/') + 1; i < temp.fileName().lastIndexOf('.'); i++)
        {
            fileName.append(temp.fileName()[i]);
        }
        tableViewInfo->setItem(i,0,new QTableWidgetItem(fileName));

        QImage im(list[i].toLocalFile());
        QImageWriter a(list[i].toLocalFile());
        tableViewInfo->setItem(i, 1, new QTableWidgetItem(QString::number(im.size().width())+"x"+QString::number(im.size().height())));
        tableViewInfo->setItem(i, 3, new QTableWidgetItem(QString::number(im.bitPlaneCount())));
        tableViewInfo->setItem(i, 4, new QTableWidgetItem(QString::number(a.compression())));
    }
    if (tableViewInfo->rowCount() == 0)
    {
        return;
    }
    table->show();


    connect(table, SIGNAL(rejected()), this, SLOT(dialogClose()));
    connect(tableViewInfo->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortSelected(int)));

    this->hide();
}

bool column1(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text() > item2->text();
}

bool column2(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    QStringList string1 = item1->text().split('x');
    QStringList string2 = item2->text().split('x');
    if (string1[0].toInt() > string2[0].toInt())
    {
        return true;
    }
    return false;
}

bool column3(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text() > item2 -> text();
}

bool column4(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text().toInt() > item2->text().toInt();
}

bool column5(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text().toInt() > item2->text().toInt();
}

void Widget::sortSelected(int columnIndex)
{
    QVector<std::function<bool(QTableWidgetItem*, QTableWidgetItem*)>> functions = {column1, column2, column3, column4, column5};

    if (sortСolumns[columnIndex] == 0)
    {
        for(int i = 0; i < tableViewInfo->rowCount(); i++)
        {
            for(int j = 0; j < tableViewInfo->rowCount() - 1; j++)
            {
                if (functions[columnIndex](tableViewInfo->item(j, columnIndex), tableViewInfo->item(j + 1, columnIndex)))
                {
                    for(int k = 0; k < tableViewInfo->columnCount(); k++)
                    {
                        QString temp1 = tableViewInfo->item(j, k)->text();
                        QString temp2 = tableViewInfo->item(j + 1, k) -> text();
                        tableViewInfo->setItem(j+1, k, new QTableWidgetItem(temp1));
                        tableViewInfo->setItem(j, k, new QTableWidgetItem(temp2));
                    }
                }
            }
        }

        for(int k = 0; k < 5; k++)
        {
            sortСolumns[k] = 0;
        }
        sortСolumns[columnIndex] = 1;
    }
    else
    {
        if (sortСolumns[columnIndex] == 1)
        {
            for(int i = 0; i < tableViewInfo->rowCount(); i++)
            {
                for(int j = 0; j < tableViewInfo->rowCount() - 1; j++)
                {
                    if (!functions[columnIndex](tableViewInfo->item(j, columnIndex), tableViewInfo->item(j + 1, columnIndex)))
                    {
                        for(int k = 0; k < tableViewInfo->columnCount(); k++)
                        {
                            QString temp1 = tableViewInfo->item(j, k)->text();
                            QString temp2 = tableViewInfo->item(j + 1, k) -> text();
                            tableViewInfo->setItem(j+1, k, new QTableWidgetItem(temp1));
                            tableViewInfo->setItem(j, k, new QTableWidgetItem(temp2));
                        }
                    }
                }
            }

            for(int k = 0; k < 5; k++)
            {
                sortСolumns[k] = 0;
            }
            sortСolumns[columnIndex] = 2;
        }
        else
        {
            for(int i = 0; i < tableViewInfo->rowCount(); i++)
            {
                for(int j = 0; j < tableViewInfo->rowCount() - 1; j++)
                {
                    if (functions[columnIndex](tableViewInfo->item(j, columnIndex), tableViewInfo->item(j + 1, columnIndex)))
                    {
                        for(int k = 0; k < tableViewInfo->columnCount(); k++)
                        {
                            QString temp1 = tableViewInfo->item(j, k)->text();
                            QString temp2 = tableViewInfo->item(j + 1, k) -> text();
                            tableViewInfo->setItem(j+1, k, new QTableWidgetItem(temp1));
                            tableViewInfo->setItem(j, k, new QTableWidgetItem(temp2));
                        }
                    }
                }
            }

            for(int k = 0; k < 5; k++)
            {
                sortСolumns[k] = 0;
            }
            sortСolumns[columnIndex] = 1;
        }
    }
}

void Widget::dialogClose()
{
    this->show();
}

Widget::~Widget()
{
    delete ui;
}
