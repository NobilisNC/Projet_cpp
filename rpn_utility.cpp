#include "rpn_utility.h"





std::map <char, std::pair<int, associativity>> TAB_OP =
        {
            {'+', {2, LEFT}},
            {'-', {2, LEFT}},
            {'*', {3, LEFT}},
            {'/', {3, LEFT}},
            {'^', {4, RIGHT}}
       };


std::map< char, float(*)(const float& a, const float& b) > OPERATION = {
    {'+', [](const float& a, const float& b ){return a+b;}},
    {'-', [](const float& a, const float& b ){return a-b;}},
    {'/', [](const float& a, const float& b ){return a/b;}},
    {'*', [](const float& a, const float& b ){return a*b;}},
    {'^', [](const float& a, const float& b ){return float(pow(a,b));}}
    };



bool RPN_utility::isoperator(const char c)
{
    return c == '*' || c == '/' || c == '+' || c == '-' || c =='^' ;

}

bool RPN_utility::isnumber(const std::string& s)
{
    if (s.empty() || (s[0] != '-' && s[0] != '+' && !std::isdigit(s[0]) ))
        return false;

    if (s.length() == 1 && ( s[0] == '-' || s[0] == '+' ) )
        return false;

    for ( auto i : s )
    {
        if (i != '-' && i != '.' && !std::isdigit(i) ) {
            return false;
        }

    }

    return true;

}


/* Parser permettant l'ajout des * entre
 *  - Constante * variable
 *  - Constante/variable * (...)
 */
void RPN_utility::first_parser(std::string& form)
{
    //On supprime les blancs
    form.erase(std::remove_if(form.begin(),
                              form.end(),
                              [](char x){return std::isspace(x);}),
               form.end());


    std::string copy(form);

    unsigned modif = 0;

    for(unsigned i = 1; i < form.length(); i++) {

        //On détecte si c'est un caractère
        if ( form[i] >= 'a' && std::isalpha(form[i])) {
            //On check si le caractère précédant est un chiffre et on ajoute une étoile
            if(std::isdigit(form[i-1]) ) {
                    copy.insert(i + modif,"*");
                    modif++;
            }
       //On detecte si c'est une parenthèse ouvrante
         } else if (form[i] == '(' ) {
            //On check si le carartère précedant est un chiffre
            if(std::isdigit(form[i-1]) ) {
                copy.insert(i + modif,"*");
                modif++;
            }
        }
    }


    form = copy;

}

/* Parser ajoutant les espaces entre les operateurs/tokens
 *  - 2*x --> 2 * x
 *
 */
void RPN_utility::second_parser(std::string& form)
{
    std::string copy(form);
    unsigned modif = 0;

    for (unsigned i = 0; i < form.length(); i++) {

        if (isoperator(form[i]) || form[i] == '(' || form[i] == ')' || form[i] == ',')
        {
            copy.insert(i+modif, " " );
            modif ++;
            copy.insert(i+modif+1, " ");
            modif ++;
        }

    }

    form = copy;
}


void RPN_utility::third_parser(std::string& form )
{
    std::stringstream iss(form);
    std::stringstream output;
    std::string before, current;

    while(!iss.eof()) {
        iss >> current;
        if (current == "-" && !std::isdigit(before[0]) )  {
           output << current;

        } else {
          output << current << " ";
        }

        before = current;
        current = "";
    }

    form = output.str();

}


std::string RPN_utility::main_parser(const std::string& formula) {
    std::stringstream iss;
    iss << formula;

    std::stringstream output;
    std::stack <std::string> s;

    std::string token;
    int i = 0;
    while(!iss.eof())
    {
        iss >> token;

        //If token is a number
        if( isnumber(token) || ( token.length() == 1 &&  std::isalpha(token[0]) ) ) {
            output << token << " ";

        //if function separator
        } else if (token[0] ==  ',') {

            while (s.top() != "(" ) {
                output << s.top() << " ";
                s.pop();
            }

        //If token is an operator
        } else if( token.length() == 1 && isoperator(token[0]) ) {

                       while ( !s.empty() && ( TAB_OP[token[0]].second == LEFT && TAB_OP[token[0]].first <= TAB_OP[s.top()[0]].first
                                        ||
                                    TAB_OP[token[0]].second == RIGHT && TAB_OP[token[0]].first < TAB_OP[s.top()[0]].first
                                  )
                  ) {
                output << s.top() << " ";
                s.pop();
            }
            s.push(token);

       //Si c'est une fonction
       } else if (token.length() > 1 ) {
        s.push(token);


       //Si c'est une parenthèse ouvrante
       } else if (token == "(" ) {
            s.push(token);

       //Si c'est une parenthèse fermante
       } else if (token == ")" ) {

            while (s.top() != "(" ) {
                output << s.top() << " ";
                s.pop();
            }
            s.pop();

            if ( !s.empty() && s.top().length() > 1 ) {
                output << s.top() << " ";
                s.pop();
            }


        }
        std::cerr << "----" << std::endl;
        token = "";



    }
    std::cerr << "----><-----" << std::endl;

    while (!s.empty()) {
        output << s.top() << " ";
        s.pop();
    }

    return output.str();

}


RPN_utility::RPN_utility(const std::string & raw, const std::string & rpn) :
    raw_formula(raw), rpn_formula(rpn)
{
    if (rpn_formula.empty())
        rpn_formula = parse(raw);

}

float RPN_utility::calc(std::map<char, float> var)
{
    std::stack<float> stack;
    std::stringstream ss(rpn_formula);

    while(!ss.eof())
    {
        std::string token;
        ss >> token;

        if ( isnumber(token) )
            stack.push(std::stof(token));
        else if ( token.length() == 1 && std::isalpha(token[0]) )
            stack.push( var[token[0]] );
        else if ( isoperator(token[0]) ) {
            float b = stack.top();
            stack.pop();
            float a = stack.top();
            stack.pop();

            stack.push ( OPERATION[ token[0] ](a,b) );
        }

    }

    return stack.top();
}

void RPN_utility::setFormula(const std::string &new_form)
{

}

std::string RPN_utility::parse(std::string formula)
{


       first_parser(formula);
       second_parser(formula);
       third_parser(formula);
       std::string RPN_formula = main_parser(formula);

       return RPN_formula;
}
