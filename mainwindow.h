#ifndef MAINWINDOW_H
#include "bmp.h"
#include "jpeg.h"
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void MainWindow::paintEvent(QPaintEvent *e);
    explicit MainWindow(QWidget *parent = 0);
    //Bmp bmp;
	uchar*  transData;
	long iwidth;
	long iheight;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
