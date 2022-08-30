#include "controller.h"
#include "ui_view.h"

Controller::Controller(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Controller)
{
    ui->setupUi(this);
    test = new Cave(50,6,3);
    test->generateField();

    laba = new Labyrinth;
    laba->createLabyrinth(4, 4);
}

Controller::~Controller()
{
    delete ui;
    delete test;
}

//void Controller::delay()
//{
//    QTime dieTime= QTime::currentTime().addMSecs(200);
//    while (QTime::currentTime() < dieTime){
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    }
//}

void Controller::on_pushButton_clicked()
{
    auto delay = [](unsigned int ms)->void {
        QTime dieTime= QTime::currentTime().addMSecs(ms);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    };

//    while (!count) {
//        test->killFrame();
//        test->writeNeighbours();
//        count = test->checkEquals();
//        ui->graphicsView->setScene(member.draw(*test));
//        delay(300);
//        test->lifeYear();
//    }
    ui->graphicsView->setScene(member.draw(*laba));
    for(int i = 0; i < laba->getLabyrinth().first.size(); ++i) {
        for(int j = 0; j < laba->getLabyrinth().first.size(); ++j) {
            std::cout << laba->getLabyrinth().second.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < laba->getLabyrinth().first.size(); ++i) {
        for(int j = 0; j < laba->getLabyrinth().first.size(); ++j) {
            std::cout << laba->getLabyrinth().first.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}














