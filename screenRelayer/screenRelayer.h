#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_screenRelayer.h"
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QString>
#include <QPainter>
#include "windows.h"
#include <QDebug>
#include <QtWinExtras>

#include "QtWinExtras/qwinfunctions.h"

class screenRelayer : public QMainWindow
{
    Q_OBJECT

public:
    screenRelayer(QWidget *parent = nullptr);
    ~screenRelayer();

private:
    Ui::screenRelayerClass ui;
    QTimer *timer;
    QScreen* screen;
    QPixmap curPix;
    bool showFlag = true;

private slots:
    void timeoutSlot();
    QImage getScreen(HWND winId);
    void screenRelayer::paintEvent(QPaintEvent* e);
    void screenRelayer::mouseDoubleClickEvent(QMouseEvent* mouseEvent);
    QPixmap screenRelayer::grW(HWND winId, int x, int y, int w, int h);
};
