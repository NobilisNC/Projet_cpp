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
    explicit ParametricFunction(const QString &id, const QString &_x_formula, const QString &_y_formula, const QPointF bornes, QWidget *parent = nullptr);
    ~ParametricFunction();

    virtual inline QString getFormula() const { return QString("%1 %2").arg(x_formula, y_formula); }

    std::pair<unsigned, QPointF*>  getPoints(float min, float max);

    static AbstractFunction* loadFunction(const QString&input, QWidget* parent = nullptr);


public slots :

     void changeX();
     void changeY();


private :

    float getOnePoint(float x);
    void setPoints();

    QPointF* points;
    QString x_formula;
    QString y_formula;
    QPointF bornes;

    QVBoxLayout* layout;
    QLineEdit* x_equation;
    QLineEdit* y_equation;

};

#endif // PARAMETRICFUNCTION_H
