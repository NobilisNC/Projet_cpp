#include "parametricfunction.h"


ParametricFunction::ParametricFunction(const QString& id, const QString& x_formula, const QString& y_formula, const QPointF bornes, QWidget* parent)
    : AbstractFunction(id, parent),
      points(nullptr),
      x_label(nullptr),
      y_label(nullptr)
{

    setMinimumSize(QSize(250, 80));

    points = new QPointF[PARAMETRIC_PRECISION];
    float grad = ( bornes.y() - bornes.x() ) / PARAMETRIC_PRECISION;

    RPN_utility* rpn = new RPN_utility(x_formula);

    float t = grad + bornes.x();
    for (unsigned i = 0; i < PARAMETRIC_PRECISION; i++) {
        points[i].setX(rpn->calc(t));
        t += grad;
    }
    //x_formula = rpn->getRawForm().utf16();
    delete rpn;
    rpn = new RPN_utility(y_formula);

    t = grad + bornes.x();
    for (unsigned i = 0; i < PARAMETRIC_PRECISION; i++) {
        points[i].setY(rpn->calc(t));
        t += grad;
    }
    //y_formula = &QString(rpn->getRawForm());
    delete rpn;

    x_label = new QLabel(QString("y=%1").arg(y_formula), this);
    y_label = new QLabel(QString("x=%1").arg(x_formula), this);

    bottom_layout->addWidget(x_label);
    bottom_layout->addWidget(y_label);


    setFixedSize(250, 75);


}

AbstractFunction *ParametricFunction::loadFunction(const QString & input, QWidget *parent)
{
    QStringList list = input.split(QChar(' '));
    QStringList list_bornes = list[4].split(QRegularExpression("[[\\;\\]]"), QString::SkipEmptyParts);


    return  new ParametricFunction(list[1], list[2], list[3], QPointF(list_bornes[0].toFloat(), list_bornes[1].toFloat()), parent);
}

ParametricFunction::~ParametricFunction()
{
    delete[] points;
    delete x_label;
    delete y_label;
}

std::pair<unsigned, QPointF*> ParametricFunction::getPoints(float min, float max)
{
    Q_UNUSED(min)
    Q_UNUSED(max)
    return std::make_pair( PARAMETRIC_PRECISION, points) ;
}

float ParametricFunction::getOnePoint(float x)
{
    Q_UNUSED(x)
    return .0f;
}
