#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include "cave.h"
#include "./model/Labyrinth.h"

class GraphicsView : public QGraphicsView
{
public:
    explicit GraphicsView(QWidget * parent = 0);
    ~GraphicsView();

public:
    QGraphicsScene *scense;

public:
    auto draw(const Cave& value) -> QGraphicsScene*;
    auto draw(const Labyrinth& value) -> QGraphicsScene*;
};

#endif // GRAPHICSVIEW_H
