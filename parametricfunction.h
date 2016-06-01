#ifndef PARAMETRICFUNCTION_H
#define PARAMETRICFUNCTION_H

#include <QString>
#include <QPoint>

#include <abstractfunction.h>

class ParametricFunction : public AbstractFunction
{
    Q_OBJECT
public:
    explicit ParametricFunction(const QString &id, const QString &x_formula, const QString &y_formula, const QPoint bornes, QWidget *parent = nullptr);

    static AbstractFunction* loadFunction(const QString&input, QWidget* parent = nullptr);

    ~ParametricFunction();

    QPoint* getPoints(QPoint min_max);


};

#endif // PARAMETRICFUNCTION_H
