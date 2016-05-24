#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), area(nullptr)
{
    ui->setupUi(this);
    area = new RenderArea(this);
    setMouseTracking(true);
    setCentralWidget(area);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}
