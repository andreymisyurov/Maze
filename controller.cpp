#include "controller.h"

#include <QFileDialog>

#include "ui_view.h"

Controller::Controller(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Controller) {
  ui->setupUi(this);

  cave = new Cave(25, 25, 4, 4, 50);
  cave->generateField();
  cave->writeNeighbours();

  maze = new Labyrinth;
  maze->createLabyrinth(m_columns, m_rows);

  ui->button_open_file->setEnabled(false);
  on_mode_maze_clicked();
}

Controller::~Controller() {
  delete ui;
  delete cave;
  delete maze;
}

void Controller::showCave() {
  ui->graphicsView->setScene(drawer.drawField(*cave));
}

void Controller::showMaze() {
  ui->graphicsView->setScene(drawer.drawField(*maze));
}

void Controller::autoModeCave() {
  m_equal = 0;

  auto delay = [](unsigned int ms) -> void {
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  };

  while (!m_equal) {
    cave->writeNeighbours();
    m_equal = cave->checkEquals();
    ui->graphicsView->setScene(drawer.drawField(*cave));
    delay(m_delay);
    cave->lifeYear();
  }
}

void Controller::on_button_build_clicked() {
  if (ui->mode_cave->isChecked()) {
    if (ui->check_open->isChecked()) {
      cave->writeNeighbours();
      showCave();
    } else {
      delete cave;
      cave = new Cave(m_rows, m_columns, m_born, m_dead, m_random);
      cave->generateField();
      cave->writeNeighbours();
      showCave();
    }
  } else {
    resetLabyrinth();
    if (!ui->check_open->isChecked()) {
      maze->createLabyrinth(m_columns, m_rows);
    } else {
      m_rows = maze->getLabyrinth().first.size();
      m_columns = maze->getLabyrinth().first[0].size();
    }

    showMaze();
  }
}

void Controller::on_mode_maze_clicked() { changeUiSet(true); }

void Controller::on_mode_cave_clicked() { changeUiSet(false); }

void Controller::changeUiSet(bool value) {
  ui->mode_maze->setChecked(value);
  ui->mode_cave->setChecked(!value);
  ui->label_born->setVisible(!value);
  ui->slider_chance_for_born->setVisible(!value);
  ui->proc_born->setVisible(!value);
  ui->slider_life->setVisible(!value);
  ui->slider_dead->setVisible(!value);
  ui->slider_delay->setVisible(!value);
  ui->label_delay->setVisible(!value);
  ui->label_dead->setVisible(!value);
  ui->label_life->setVisible(!value);
  ui->label_cell_to_life->setVisible(!value);
  ui->label_cell_to_dead->setVisible(!value);
  ui->cave_auto->setVisible(!value);
  ui->cave_auto->setChecked(true);
  ui->label_begin->setVisible(value);
  ui->label_end->setVisible(value);
  ui->label_x_finish->setVisible(value);
  ui->label_y_finish->setVisible(value);
  ui->label_x_start->setVisible(value);
  ui->label_y_start->setVisible(value);
  ui->button_save->setVisible(value);
}

void Controller::on_h_size_actionTriggered() {
  m_columns = ui->h_size->value();
  ui->label_h->setText(QString::number(m_columns));
  if (ui->mode_maze->isChecked()) on_button_build_clicked();
}

void Controller::on_w_size_actionTriggered() {
  m_rows = ui->w_size->value();
  ui->label_w->setText(QString::number(m_rows));
  if (ui->mode_maze->isChecked()) on_button_build_clicked();
}

void Controller::on_slider_chance_for_born_actionTriggered() {
  m_random = ui->slider_chance_for_born->value();
  ui->proc_born->setText(QString::number(m_random));
}

void Controller::on_cave_auto_stateChanged() {
  if (ui->cave_auto->checkState()) {
    ui->slider_delay->setEnabled(true);
  } else {
    ui->slider_delay->setEnabled(false);
  }
}

void Controller::on_slider_life_actionTriggered() {
  m_born = ui->slider_life->value();
  ui->label_life->setText(QString::number(m_born));
}

void Controller::on_slider_dead_actionTriggered() {
  m_dead = ui->slider_dead->value();
  ui->label_dead->setText(QString::number(m_dead));
}

void Controller::on_slider_delay_actionTriggered() {
  m_delay = ui->slider_delay->value();
  ui->label_delay->setText(QString::number(m_delay));
}

void Controller::on_check_open_stateChanged() {
  if (ui->check_open->checkState()) {
    ui->button_open_file->setEnabled(true);
  } else {
    ui->button_open_file->setEnabled(false);
  }
}

void Controller::on_button_open_file_clicked() {
  QString path;

  if (ui->mode_cave->isChecked()) {
    path = QFileDialog::getOpenFileName(0, "OpenDialog", "", "*_cave.txt");
    if (!path.isEmpty()) {
      auto transit = path.toLocal8Bit().data();
      *cave = Cave::loadCave(transit);
    }
  } else {
    path = QFileDialog::getOpenFileName(0, "OpenDialog", "", "*_maze.txt");
    if (!path.isEmpty()) {
      maze->createLabyrinthFromFile(path.toStdString());
    }
  }
}

void Controller::on_pushButton_play_clicked() {
  if (ui->mode_cave->isChecked()) {
    if (ui->cave_auto->isChecked()) {
      autoModeCave();
    } else {
      handModeCave();
    }
  } else {
    if (m_selecter == 2 &&
        !((m_pathXstart == m_pathXfinish) && (m_pathYstart == m_pathYfinish))) {
      Finder path;
      auto l = maze->getLabyrinth();
      ui->graphicsView->setScene(
          drawer.drawPath(m_rows, m_columns,
                          path.getPath(l, m_pathXstart, m_pathYstart,
                                       m_pathXfinish, m_pathYfinish)));
    }
  }
}

void Controller::handModeCave() {
  cave->lifeYear();
  cave->writeNeighbours();
  ui->graphicsView->setScene(drawer.drawField(*cave));
}

void Controller::resetLabyrinth() {
  m_pathXstart = 0;
  m_pathYstart = 0;
  m_pathXfinish = 0;
  m_pathYfinish = 0;
  ui->label_x_start->setText("none");
  ui->label_y_start->setText("none");
  ui->label_x_finish->setText("none");
  ui->label_y_finish->setText("none");
  m_selecter = 0;
}

void Controller::mousePressEvent(QMouseEvent *e) {
  if (ui->mode_maze->isChecked()) {
    if (m_selecter == 0 && e->pos().y() > 35 && e->pos().y() < 525 &&
        e->pos().x() > 25 && e->pos().x() < 515) {
      m_pathXstart = (e->pos().y() - 30.) / (500. / m_rows);
      m_pathYstart = (e->pos().x() - 20.) / (500. / m_columns);
      ui->label_x_start->setText(QString::number(m_pathXstart));
      ui->label_y_start->setText(QString::number(m_pathYstart));
      ui->graphicsView->setScene(
          drawer.drawPoint(e->pos().x(), e->pos().y(), true));

      ++m_selecter;
    } else if (m_selecter == 1 && e->pos().y() > 35 && e->pos().y() < 525 &&
               e->pos().x() > 25 && e->pos().x() < 515) {
      m_pathXfinish = (e->pos().y() - 30.) / (500. / m_rows);
      m_pathYfinish = (e->pos().x() - 20.) / (500. / m_columns);
      ui->label_x_finish->setText(QString::number(m_pathXfinish));
      ui->label_y_finish->setText(QString::number(m_pathYfinish));
      ui->graphicsView->setScene(
          drawer.drawPoint(e->pos().x(), e->pos().y(), false));
      ++m_selecter;
    } else if (e->pos().y() > 35 && e->pos().y() < 525 && e->pos().x() > 25 &&
               e->pos().x() < 515) {
      resetLabyrinth();
      showMaze();
    }
  }
}

void Controller::on_button_save_clicked() {
  std::string path = ((QDir::homePath()).toStdString() + "/output.txt");
  maze->saveToFile(path);
}
