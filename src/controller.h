#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include "graphicsview.h"
#include <QThread>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Controller; }
QT_END_NAMESPACE

class Controller : public QMainWindow
{
    Q_OBJECT

public:
    Controller(QWidget *parent = nullptr);
    ~Controller();

private slots:
    void on_pushButton_clicked();

private:

    Ui::Controller *ui;
    GraphicsView member;
    Cave *test;
    Labyrinth *laba;
    int count = 0;
    unsigned int delay = 300;

//    auto delay() -> void;

};
#endif // CONTROLLER_H
