#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <QDir>
#include <QMainWindow>
#include <QMouseEvent>
#include <QThread>
#include <QTime>

#include "./model/finder.h"
#include "./model/graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

class Controller : public QMainWindow {
  Q_OBJECT

 public:
  explicit Controller(QWidget *parent = nullptr);
  ~Controller();

 private:
  void autoModeCave();
  void handModeCave();
  void showMaze();
  void showCave();
  void resetLabyrinth();
  void changeUiSet(bool value);
  void mousePressEvent(QMouseEvent *value) override;

 private slots:
  void on_button_build_clicked();
  void on_pushButton_play_clicked();
  void on_button_open_file_clicked();
  void on_mode_maze_clicked();
  void on_mode_cave_clicked();
  void on_slider_chance_for_born_actionTriggered();
  void on_cave_auto_stateChanged();
  void on_slider_life_actionTriggered();
  void on_slider_dead_actionTriggered();
  void on_slider_delay_actionTriggered();
  void on_h_size_actionTriggered();
  void on_w_size_actionTriggered();
  void on_check_open_stateChanged();

  void on_button_save_clicked();

 private:
  Ui::Controller *ui;
  GraphicsView drawer;
  Cave *cave;
  Labyrinth *maze;

  int m_rows = 25;
  int m_columns = 25;
  int m_born = 4;
  int m_dead = 4;
  int m_random = 50;
  unsigned int m_delay = 300;

  int m_equal = 0;
  int m_selecter = 0;

  int m_pathXstart = 0;
  int m_pathYstart = 0;
  int m_pathXfinish = 0;
  int m_pathYfinish = 0;
};
#endif  // SRC_CONTROLLER_H_
