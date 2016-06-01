#include "function.h"


Function::Function(const QString& _id, const QString & formula, QWidget* _parent)
    :
    AbstractFunction(_id, _parent),
    rpn_u(nullptr)
{

  id_func->setText(QString("y=%1").arg(formula));
  rpn_u = new RPN_utility( formula.toStdString() );
}


Function::~Function()
{
}

AbstractFunction *Function::loadFunction(const QString & input, QWidget *parent)
{
    QStringList list = input.split(QChar(' '));
    return  new Function(list[1], list[2], parent);

}

QPoint *Function::getPoints(QPoint min_max)
{

}


/* Enlève le "f(x)" et détecte le paramètre */
void Function::parse_function(QString& raw_formula)
{

/*   QStringList list = raw_formula.split(QRegularExpression("="),QString::SkipEmptyParts);
   raw_formula = list[1]; //On a l'expression de la fonction


   //f(x,y...) --> "f", "x,y..."
   list = list[0].split(QRegularExpression("[\\(\\)=]"),QString::SkipEmptyParts);
   id = list[0];

   //"x,y,..." --> "x","y","..."
   list = list[1].split(QRegularExpression(","),QString::SkipEmptyParts);

   tab_var = new char[list.length()];

   for(unsigned  i = 0; i < list.length(); i++)
        tab_var[i] = QChar(list[i][0]).toLatin1(); */
}



