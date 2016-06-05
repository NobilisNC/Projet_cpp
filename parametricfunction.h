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

    static AbstractFunction* loadFunction(const QString&input, QWidget* parent = nullptr);

    virtual inline QString getFormula() const { return QString("%1 %2").arg(x_formula, y_formula); }


    ~ParametricFunction();

   std::pair<unsigned, QPointF*>  getPoints(float min, float max);

private :
    QPointF* points;
    QString x_formula;
    QString y_formula;
    QPointF bornes;

    QVBoxLayout* layout;
    QLineEdit* x_equation;
    QLineEdit* y_equation;

    float getOnePoint(float x);
    void setPoints();


public slots :
     void changeX();
     void changeY();


};

#endif // PARAMETRICFUNCTION_H
