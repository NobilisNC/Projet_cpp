#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <rpn_utility.h>


class Function
{
public :
    Function(const std::string& /*id*/,
             const std::string& /*raw_formula*/,
             const std::string& /*rpn_formula*/ = std::string("")   );

    virtual ~Function();

    virtual float get_image(float x);


    inline std::string getID() const {return id;}
    inline void setID(const std::string& _id) {id=_id;}




private :
    std::string id;
    RPN_utility rpn_u;


};

#endif // FUNCTION_H
