#include "abstractfunction.h"

#include "function.h"
#include "parametricfunction.h"


AbstractFunction::AbstractFunction(const QString & _id, QWidget *parent)
    : QPushButton(parent),
      id(_id),
      main_layout(nullptr),
      top_layout(nullptr),
      check(nullptr),
      box(nullptr),
      id_func(nullptr),
      bottom_layout(nullptr)
{

    main_layout = new QVBoxLayout(this);

    top_layout = new QHBoxLayout;
    bottom_layout = new QVBoxLayout;

    //CHECK
    check = new QCheckBox;
    check->setChecked(true);
    //ID_FUNC
    id_func = new QLabel;
    id_func->setText(QString("%1").arg(id));

    //BOX
    box = new QComboBox;
        //PARAMETERS
        QPixmap color_Icon(10,10);

        for (unsigned i = 0; i < 5; i++) {
            color_Icon.fill(COLOR[i]);
            box->insertItem(i, *(new QIcon(color_Icon)) , QString(""));
        }


    setMinimumWidth(250);

    top_layout->addWidget(check,0,Qt::AlignLeft);
    top_layout->addWidget(box,0,Qt::AlignLeft);
    top_layout->addWidget(id_func,0,Qt::AlignLeft);
    top_layout->addSpacing(width() /2 );

    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);

    setLayout(main_layout);

}

AbstractFunction::~AbstractFunction()
{
    delete main_layout;
    delete top_layout;
    delete id_func;
    delete box;
    delete id_func;
    delete bottom_layout;
}

AbstractFunction *AbstractFunction::loadFunction(const QString & input, QWidget *parent)
{
    QStringList list = input.split(QChar(' '));

    if ( list[0] == QString("Function") )
        return Function::loadFunction(input, parent);
    else if (list[0] ==  QString("Parametric"))
        return ParametricFunction::loadFunction(input, parent);
    else
        throw "Une erreur";

}

QSize AbstractFunction::sizeHint() const
{
   return QSize(250, 75) ;
}

QSize AbstractFunction::minimumSizeHint() const
{
    return QSize(250, 55);
}

/*void AbstractFunction::paintEvent(QPaintEvent *)
{

    /*QPainter pen(this);
    pen.fillRect(0, 0, width(), height(), Qt::lightGray);

}*/



