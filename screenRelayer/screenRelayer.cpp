#include "screenRelayer.h"

screenRelayer::screenRelayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.mainToolBar->setVisible(false);
	timer = new QTimer(this);
	ui.label->setScaledContents(true);
	screen = QGuiApplication::primaryScreen();
	connect(timer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
	timer->start(2);

}

screenRelayer::~screenRelayer()
{}

void screenRelayer::timeoutSlot()
{
	QImage curImg = getScreen(0);

	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");	
	//为这个QImage构造一个QPainter
	QPainter painter(&curImg);
	painter.setCompositionMode(QPainter::RasterOp_SourceAndNotDestination);

	//改变画笔和字体
	QFont font;
	//设置显示字体的大小
	font.setPixelSize(50);
	painter.setPen(Qt::white);
	painter.setFont(font);

	//将Hello写在Image的中心
	painter.drawText(curImg.rect(), Qt::AlignLeft & Qt::AlignBottom, str);

	curPix = QPixmap::fromImage(curImg.mirrored(true, false));
	//curPix = QPixmap::fromImage(curImg);
	//curPix.scaled(ui.label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label->setPixmap(curPix);
}

QImage screenRelayer::getScreen(HWND winId)
{
	screen->size();
	QImage image = grW(0, 0, 0, screen->size().width(), screen->size().height()).toImage();
	//QImage image = screen->grabWindow(0, 0, 0, screen->size().width(), screen->size().height()).toImage();
	//QPixmap pix = QPixmap::fromImage(image.mirrored(true, false));
	return image;
}


void screenRelayer::paintEvent(QPaintEvent* e)
{
	curPix = curPix.scaled(ui.label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label->setPixmap(curPix);
}

void screenRelayer::mouseDoubleClickEvent(QMouseEvent* mouseEvent)
{
	//showFlag为标志位
	if (showFlag) {
		this->showFullScreen();
		showFlag = false;
	}
	else {
		this->showNormal();
		showFlag = true;
	}
}


QPixmap screenRelayer::grW(HWND winId, int x, int y, int w, int h)
{

	RECT r;
	GetClientRect(winId, &r);

	if (w < 0) w = r.right - r.left;
	if (h < 0) h = r.bottom - r.top;

	HDC display_dc = GetDC(winId);
	HDC bitmap_dc = CreateCompatibleDC(display_dc);
	HBITMAP bitmap = CreateCompatibleBitmap(display_dc, w, h);
	HGDIOBJ null_bitmap = SelectObject(bitmap_dc, bitmap);

	BitBlt(bitmap_dc, 0, 0, w, h, display_dc, x, y, SRCCOPY | CAPTUREBLT);

	CURSORINFO ci;
	ci.cbSize = sizeof(CURSORINFO);
	GetCursorInfo(&ci);
	if ((ci.ptScreenPos.x > x) && (ci.ptScreenPos.y > y) && (ci.ptScreenPos.x < (x + w)) && (ci.ptScreenPos.y < (y + h)))
		DrawIcon(bitmap_dc, ci.ptScreenPos.x - x, ci.ptScreenPos.y - y, ci.hCursor);

	// clean up all but bitmap
	ReleaseDC(winId, display_dc);
	SelectObject(bitmap_dc, null_bitmap);
	DeleteDC(bitmap_dc);

	QPixmap pixmap = QtWin::fromHBITMAP(bitmap);

	DeleteObject(bitmap);

	return pixmap;
}
