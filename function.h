#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <iostream>

#include <abstractfunction.h>
#include <rpn_utility.h>


class Function : public AbstractFunction
{
    Q_OBJECT
public :
    explicit Function(const QString& _id, const QString & formula, QWidget* _parent = nullptr );

    ~Function();

    static AbstractFunction* loadFunction(const QString& input, QWidget* parent = nullptr);


    QPoint* getPoints(QPoint min_max);

protected :
    QString id;
    RPN_utility* rpn_u;



    void parse_function(QString&);


};

#endif // FUNCTION_H
