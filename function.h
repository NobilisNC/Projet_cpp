#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <iostream>

#include <abstractfunction.h>
#include <rpn_utility.h>
#include <defines.h>


class Function : public AbstractFunction
{
    Q_OBJECT
public :
    explicit Function(const QString& _id, const QString & formula, QWidget* _parent = nullptr );

    ~Function();

    virtual float getOnePoint(float x);

    static AbstractFunction* loadFunction(const QString& input, QWidget* parent = nullptr);


    std::pair<unsigned, QPointF*> getPoints(float min, float max);

protected :
    QString id;
    QLabel* equation;
    RPN_utility* rpn_u;



    void parse_function(QString&);


};

#endif // FUNCTION_H
