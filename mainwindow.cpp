#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    area(nullptr),
    formula(nullptr),
    bnew_func(nullptr),
    main_label(nullptr),
    main_layout(nullptr),
    top_layout(nullptr),
    bottom_layout(nullptr),
    func_layout(nullptr)
{
    main_label = new QWidget(this);
    main_layout = new QVBoxLayout;
    top_layout = new QHBoxLayout;

    func_layout = new QVBoxLayout;

    //FUNC LAYOUT
        //Parameters




    //TOP LAYOUT
    area = new RenderArea(this);

    top_layout->addLayout(func_layout);
    top_layout->addWidget(area,0, Qt::AlignTop);

    //BOTTOM LAYOUT
    bottom_layout = new QHBoxLayout;

    QLabel* test= new QLabel("Formule :");
    formula = new QLineEdit;
    bnew_func = new QPushButton("Nouvelle fonction");
    bottom_layout->addWidget(test);
    bottom_layout->addWidget(formula);
    bottom_layout->addWidget(bnew_func);





    //MAIN LAYOUT
    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);



    //MAIN_LABEL
    main_label->setLayout(main_layout);




    setCentralWidget(main_label);



    QObject::connect(bnew_func,SIGNAL(clicked(bool)), this, SLOT(new_func()));


}

MainWindow::~MainWindow()
{
    delete area;
    delete main_label;
    delete main_layout;
    delete func_layout;
}


void MainWindow::new_func()
{
    AbstractFunction* f = AbstractFunction::loadFunction(formula->text());
    storage.append(f);
    area->add_function(f);
    func_layout->addWidget(f);


}
