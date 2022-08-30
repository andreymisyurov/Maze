#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
    scense = new QGraphicsScene;
}


GraphicsView::~GraphicsView() {
    delete scense;
}


auto GraphicsView::draw(const Cave& value) -> QGraphicsScene* {
//    scense.setSceneRect(500,500,500,500);
    scense->clear();
    QPen penRed(Qt::red);
    QPen penBlack(Qt::black);
    QBrush temp(Qt::blue);
    int n = value.m_field.size();
    int alpha = 500 / n;
//    int m = 9;
//    scense->backgroundBrush();
//    for(int i = 1; i < 3; ++i) {
//        scense->addLine(alpha * i, 0,alpha * i, 500);
//        scense->addLine(0, alpha * i, 500,alpha * i);
//    }


    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(value.m_field.at(i).at(j).status){
                scense->addRect(alpha * i, alpha * j, alpha, alpha, penRed);
            } else {
//                scense->addRect(alpha * i, alpha * j, alpha, alpha, penBlack);
            }
//            scense->addRect(0, alpha, alpha, alpha, penRed);
//            scense->addRect(0, alpha, alpha, alpha, penRed);
//            scense->addRect(0, 0, alpha, alpha, penRed);
//            scense->addLine(0, alpha * i, 500,alpha * i);

        }
    }

//    scense->addRect(0, 0, 10, 10, penRed, temp);
//    scense->addRect(-500, -500, 10, 10, penRed, temp);
//    scense->addRect();

    return scense;
}

auto GraphicsView::draw(const Labyrinth& value) -> QGraphicsScene* {

    scense->clear();
    QPen penRed(Qt::red);
    QPen penBlack(Qt::black);
    QPen penBlue(Qt::black);
    QBrush temp(Qt::blue);
    auto pair = value.getLabyrinth();

    int n = pair.first.size();

    int alpha = 500 / n;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(pair.first.at(j).at(i)){
//                scense->addRect(alpha * i, alpha * j, alpha, alpha, penRed);
                  scense->addLine(alpha * i + alpha, alpha * j, alpha * i + alpha, alpha * j + alpha, penRed);
            }

            if(pair.second.at(j).at(i)){
//                scense->addRect(alpha * i, alpha * j, alpha, alpha, penRed);
                scense->addLine(alpha * i, alpha * j + alpha, alpha * i + alpha, alpha * j + alpha, penRed);
            } else {
                scense->addLine(alpha * i, alpha * j + alpha, alpha * i + alpha, alpha * j + alpha, penBlack);
            }

        }
    }


    return scense;
}









