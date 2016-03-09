#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("Ñ¡ÔñÍ¼Ïñ"),
		"",
		tr("Images (*.jpg *.jpeg *.bmp)"));
	QRegExp isBmp("*.bmp");
	if (isBmp.exactMatch(filename))
	{
		Bmp bmp;
		bmp.readBmp(filename.toLatin1().data());
		bmp.setPixels();
		QByteArray imageByteArray = QByteArray((char*)bmp.pBmpBuf, bmp.size); 
		transData = (unsigned char*)imageByteArray.data();
		iwidth = bmp.bmpWidth;
		iheight = bmp.bmpHeight;
	}
	else {
		Jpeg* jpeg = new Jpeg(filename.toLatin1().data());
		transData = jpeg->buffer;
		iwidth = jpeg->imgwidth;
		iheight = jpeg->imgheight;
	}
	ui->setupUi(this);
	this->setFixedSize(iwidth, iheight);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    //QByteArray imageByteArray = QByteArray( (char*)bmp.pBmpBuf, bmp.size);
    //uchar*  transData = (unsigned char*)imageByteArray.data();
	//uchar*  transData = bmp.pBmpBuf;
	QImage image(transData, iwidth, iheight, QImage::Format_RGB888);
	image = image.mirrored(false, true);
    paint.drawImage(QPoint(0, 0), image);
    paint.end();
}
