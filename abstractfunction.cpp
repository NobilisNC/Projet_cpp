#include "abstractfunction.h"

#include "function.h"
#include "parametricfunction.h"


const int COLOR[] = {Qt::red, Qt::green, Qt::blue, Qt::lightGray, Qt::yellow };





AbstractFunction::AbstractFunction(const QString & _id, QWidget *parent)
    : QPushButton(parent),
      id(_id),
      layout(nullptr),
      check(nullptr),
      box(nullptr),
      id_func(nullptr)
{
    layout = new QHBoxLayout(this);

    //CHECK
    check = new QCheckBox;
    check->setChecked(true);
    //ID_FUNC
    id_func = new QLabel(this);

    //BOX
    box = new QComboBox(this);
        //PARAMETERS
        QPixmap color_Icon(10,10);

        for (unsigned i = 0; i < 5; i++) {
            color_Icon.fill(COLOR[i]);
            box->insertItem(i, *(new QIcon(color_Icon)) , QString(""));
        }


    setMinimumSize(QSize(250, 50));

    layout->addWidget(check);
    layout->addWidget(box);
    layout->addWidget(id_func);

    setLayout(layout);

}

AbstractFunction::~AbstractFunction()
{
    delete layout;
    delete id_func;
    delete box;
    delete id_func;
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



QPoint *AbstractFunction::getPoints(QPoint min_max)
{

}
