#ifndef SRC_MODEL_GRAPHICSVIEW_H_
#define SRC_MODEL_GRAPHICSVIEW_H_

#include <QGraphicsView>
#include <QWidget>

#include "./model/Labyrinth.h"
#include "cave.h"

class GraphicsView : public QGraphicsView {
 public:
  explicit GraphicsView(QWidget *parent = 0);
  ~GraphicsView();

 public:
  auto drawField(const Cave &value) -> QGraphicsScene *;
  auto drawField(const Labyrinth &value) -> QGraphicsScene *;

  auto drawPath(int rows, int colomns, const vector<pair<int, int>> &line)
      -> QGraphicsScene *;
  auto drawPoint(int row, int column, bool color) -> QGraphicsScene *;

 private:
  auto drawFrame(QPen pen) -> void;
  QGraphicsScene *scene;
};

#endif  // SRC_MODEL_GRAPHICSVIEW_H_
