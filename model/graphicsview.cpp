#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
  scene = new QGraphicsScene;
}

GraphicsView::~GraphicsView() { delete scene; }

auto GraphicsView::drawField(const Cave &value) -> QGraphicsScene * {
  scene->clear();

  QPen penRed(Qt::red);
  penRed.setWidth(1);
  QBrush brush = QBrush(Qt::red);

  int rows = value.getRows();
  int columns = value.getColumns();
  float heightCell = static_cast<float>(490) / rows;
  float widthCell = static_cast<float>(490) / columns;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (value.getField().at(i).at(j).status) {
        scene->addRect(widthCell * j, heightCell * i, widthCell, heightCell,
                       penRed, brush);
      }
    }
  }

  return scene;
}

auto GraphicsView::drawField(const Labyrinth &value) -> QGraphicsScene * {
  scene->clear();

  QPen penRed(Qt::red);
  penRed.setWidth(2);
  drawFrame(penRed);

  auto pair = value.getLabyrinth();

  int columns = pair.first.size();
  int rows = pair.second[0].size();
  float heightCell = static_cast<float>(490) / columns;
  float widthCell = static_cast<float>(490) / rows;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (pair.first.at(j).at(i))
        scene->addLine(widthCell * i + widthCell, heightCell * j,
                       widthCell * i + widthCell, heightCell * j + heightCell,
                       penRed);

      if (pair.second.at(j).at(i))
        scene->addLine(widthCell * i, heightCell * j + heightCell,
                       widthCell * i + widthCell, heightCell * j + heightCell,
                       penRed);
    }
  }

  return scene;
}

auto GraphicsView::drawPath(int rows, int columns,
                            const vector<pair<int, int>> &value)
    -> QGraphicsScene * {
  QPen penBlue(Qt::blue);
  penBlue.setWidth(2);

  float heightCell = static_cast<float>(490) / rows;
  float widthCell = static_cast<float>(490) / columns;
  float temp_x = 0.0;
  float temp_y = 0.0;
  bool flag = 1;

  for (auto el : value) {
    for (int i = 0; i < columns; ++i) {
      for (int j = 0; j < rows; ++j) {
        if (el.first == j && el.second == i) {
          if (flag) {
            temp_x = widthCell * i + widthCell / 2;
            temp_y = heightCell * j + heightCell / 2;
            flag = 0;
          }

          scene->addLine(temp_x, temp_y, widthCell * i + widthCell / 2,
                         heightCell * j + heightCell / 2, penBlue);
          temp_x = widthCell * i + widthCell / 2;
          temp_y = heightCell * j + heightCell / 2;
        }
      }
    }
  }

  return scene;
}

auto GraphicsView::drawPoint(int row, int column, bool color)
    -> QGraphicsScene * {
  QPen colorPoint = color ? QPen(Qt::white) : QPen(Qt::yellow);
  colorPoint.setWidth(4);
  scene->addLine(row - 25, column - 35, row - 25, column - 35, colorPoint);
  return scene;
}

auto GraphicsView::drawFrame(QPen pen) -> void {
  scene->addLine(0, 490, 0, 0, pen);
  scene->addLine(0, 0, 490, 0, pen);
  scene->addLine(0, 490, 490, 490, pen);
  scene->addLine(490, 0, 490, 490, pen);
}
