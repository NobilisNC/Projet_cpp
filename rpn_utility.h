#ifndef RPN_utility_H
#define RPN_utility_H

#include <stack>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cmath>


enum associativity { NONE, LEFT, RIGHT };

class RPN_utility
{
public:
    RPN_utility(const std::string&, const std::string& = std::string("") );





    float calc(std::map<char, float>);

    void setFormula(const std::string& new_form);
    inline std::string getRawForm() const {return raw_formula;}




    /* Parser */
    static std::string parse(std::string);
    static bool isnumber(const std::string&);
    static bool isoperator(const char);

private :
    std::string raw_formula;
    std::string rpn_formula;



    static void first_parser(std::string&);
    static void second_parser(std::string&);
    static void third_parser(std::string&);
    static std::string main_parser(const std::string& formula);


};

#endif // RPN_utility_H
