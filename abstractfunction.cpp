#include "abstractfunction.h"

#include "function.h"
#include "parametricfunction.h"


AbstractFunction::AbstractFunction(const QString & _id, QWidget *parent)
    : QWidget(parent),
      id(_id),
      is_selected(false),
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
        QPixmap color_Icon(10,8);

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
    setFixedSize(QSize(250, 60));

    QObject::connect(this, SIGNAL(selected(AbstractFunction*)), parentWidget(), SLOT(updateSelected(AbstractFunction*)));


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
   return QSize(250, 50) ;
}

QSize AbstractFunction::minimumSizeHint() const
{
    return QSize(250, 40);
}

void AbstractFunction::mouseReleaseEvent(QMouseEvent *)
{
    is_selected = !is_selected;
    if (is_selected)
        emit selected(this);
    else
        emit selected(nullptr);

    update();
}

void AbstractFunction::new_select(AbstractFunction * new_func)
{
    if (new_func == this)
        is_selected = true;
    else
        is_selected = false;

    update();

}


void AbstractFunction::paintEvent(QPaintEvent *)
{
    QPainter pen(this);
    if (is_selected)
        pen.fillRect(0, 0, width(), height(), Qt::blue);
    else
        pen.fillRect(0, 0, width(), height(), Qt::lightGray);
}



