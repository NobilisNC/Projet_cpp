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
    RPN_utility(const std::string& raw, const std::string& rpn = std::string(""));





    float calc(float x);

    void setFormula(const std::string& new_form);
    inline std::string getRawForm() const {return raw_formula;}




    /* Parser */
    std::string parse(std::string);
    static bool isnumber(const std::string&);
    static bool isoperator(const char);

private :
    std::string raw_formula;
    std::string rpn_formula;



    void first_parser(std::string&);
    void second_parser(std::string&);
    void third_parser(std::string&);
    std::string main_parser(const std::string& formula);

    static std::map< char, float(*)(const float& a, const float& b) > OPERATION;
    static std::map <char, std::pair<int, associativity>> TAB_OP;
    static std::map< std::string, float(*)(const float& a) > COMMON_FUNCTION;


};

#endif // RPN_utility_H
