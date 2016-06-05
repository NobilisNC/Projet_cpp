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
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QErrorMessage>
#include <QListWidget>
#include <QScrollArea>
#include <QGroupBox>

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
    QScrollArea* func_list;
    QGroupBox* func_box;
    QVBoxLayout* caca_layout;

    QMenu* file_menu;
    QAction* open_file;
    QAction* quit;


public slots :
    void new_func();
    void load_file();
    void updateFunction();


private :
    QVector<AbstractFunction*> storage;

    void create_function(const QString& input);

public slots :
    void updateSelected(AbstractFunction* func);
    void delete_func(AbstractFunction *func);


};

#endif // MAINWINDOW_H
