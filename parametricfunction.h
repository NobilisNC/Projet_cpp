#ifndef PARAMETRICFUNCTION_H
#define PARAMETRICFUNCTION_H

#include <QString>
#include <QPoint>
#include <QDebug>
#include <abstractfunction.h>
#include <rpn_utility.h>
#include <defines.h>


class ParametricFunction : public AbstractFunction
{
    Q_OBJECT
public:
    explicit ParametricFunction(const QString &id, const QString &x_formula, const QString &y_formula, const QPointF bornes, QWidget *parent = nullptr);

    static AbstractFunction* loadFunction(const QString&input, QWidget* parent = nullptr);

    ~ParametricFunction();

   std::pair<unsigned, QPointF*>  getPoints(float min, float max);

private :
    QPointF* points;

    QVBoxLayout* layout;
    QLabel* x_label;
    QLabel* y_label;


};

#endif // PARAMETRICFUNCTION_H
