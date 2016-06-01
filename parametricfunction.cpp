#include "parametricfunction.h"

ParametricFunction::ParametricFunction(const QString& id, const QString& x_formula, const QString& y_formula, const QPoint bornes, QWidget* parent)
    : AbstractFunction(id, parent)
{

}

AbstractFunction *ParametricFunction::loadFunction(const QString & input, QWidget *parent)
{
    QStringList list = input.split(QChar(' '));
    return  new ParametricFunction(list[1], list[1], list[2], QPoint(0,0), parent);
}

ParametricFunction::~ParametricFunction()
{

}

QPoint *ParametricFunction::getPoints(QPoint min_max)
{

}
