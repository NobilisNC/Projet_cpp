#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QVector>
#include <QPushButton>

#include <renderarea.h>
#include <abstractfunction.h>



class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea* area;
    QLineEdit* formula;
    QPushButton* bnew_func;
    QWidget* main_label;
    QVBoxLayout* main_layout;
    QHBoxLayout* top_layout;
    QHBoxLayout* bottom_layout;
    QVBoxLayout* func_layout;



public slots :
    void new_func();


private :
    QVector<AbstractFunction*> storage;

};

#endif // MAINWINDOW_H
