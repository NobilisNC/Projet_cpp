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


    func_layout->setAlignment(func_layout, Qt::AlignTop);

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

    file_menu = new QMenu("Fichier",this);
    open_file = new QAction("Ouvrir", this);
    open_file->setShortcut(QKeySequence::Open);

    file_menu->addAction(open_file);


    menuBar()->addMenu(file_menu);





    QObject::connect(bnew_func,SIGNAL(clicked(bool)), this, SLOT(new_func()));
    QObject::connect(open_file, SIGNAL(triggered(bool)), this, SLOT(load_file()));

}

MainWindow::~MainWindow()
{
    delete area;
    delete main_label;
    delete main_layout;
    delete func_layout;
    delete file_menu;
    delete quit;
    delete open_file;
}


void MainWindow::new_func()
{
    create_function(formula->text());
}

void MainWindow::load_file()
{
    QString path = QFileDialog::getOpenFileName(this,"Ouvrir un fichier fonction");

    if (path.isEmpty())
        return;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        create_function(line);
    }




}

void MainWindow::create_function(const QString &input)
{
    try {

    AbstractFunction* f = AbstractFunction::loadFunction(input,this);
    storage.append(f);
    area->add_function(f);


    func_layout->addWidget(f);

    //func_layout->setAlignment(f, Qt::AlignTop);


    } catch (...) {
        std::cerr << "CACA" << std::endl;
    }

}
