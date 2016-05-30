#include "function.h"


Function::Function(const std::string & _id, const std::string& raw_formula, const std::string& rpn_formula) : id(_id), rpn_u(raw_formula, rpn_formula)
{}


Function::~Function()
{}

float Function::get_image(float x)
{
    return rpn_u.calc(std::map<char,float>( {{'x',x}} ));

}



