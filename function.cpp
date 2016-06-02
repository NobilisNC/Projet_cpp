#include "function.h"


Function::Function(const QString& _id, const QString & formula, QWidget* _parent)
    :
    AbstractFunction(_id, _parent),
    equation(nullptr),
    rpn_u(nullptr)
{
  rpn_u = new RPN_utility( formula.toStdString() );


  equation = new QLabel(QString("y=%1").arg(QString::fromLocal8Bit(rpn_u->getRawForm().c_str())));
  bottom_layout->addWidget(equation);

}

Function::~Function()
{
    delete rpn_u;
    delete equation;
}

AbstractFunction *Function::loadFunction(const QString & input, QWidget *parent)
{
    QStringList list = input.split(QChar(' '));
    return  new Function(list[1], list[2], parent);

}

std::pair<unsigned, QPointF *> Function::getPoints(float min, float max)
{
    QPointF* tab = new QPointF[FUNCTION_PRECISION];
    float grad =(  max - min  ) / FUNCTION_PRECISION;

    float x = min;

    for (unsigned i = 0; i < FUNCTION_PRECISION; i ++) {
        tab[i] = QPointF(x, rpn_u->calc(x) );
        x+= grad;
    }

    return std::make_pair(FUNCTION_PRECISION,tab);
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



