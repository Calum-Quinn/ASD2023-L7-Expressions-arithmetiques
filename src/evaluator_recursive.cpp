#include "evaluator.h"
#include <string>
#include <algorithm>
#include <cmath>

using opData = char;
using valData = int;

using namespace std;

// a compléter avec une définition récursive de la fonction evalue
// qui n'utilise pas de pile

bool estOperateur(const opData c) {
   return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

valData effectuer (valData val1, opData op, valData val2) {
   switch (op) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case '%': return val1 % val2;
   }
}

int chiffresDansNbr(int nbr) {
   return int(log10(nbr)) + 1;
}

int valeurLongue(string expression, size_t& pos) {
   size_t j = 0;
   while(isdigit(expression[pos + j])){
      ++j;
   }

   int valeur = stoi(expression.substr(pos,j));

   //Avance dans l'expression pour ne pas contrôler les autre chiffres du même nombre
   pos += chiffresDansNbr(valeur) - 1;

   return valeur;
}

int evalueRecursive(string expression) {
   for (size_t i = 0; i < expression.size(); ++i) {
      int val1;
      int val2;
      char operateur;
      if (expression[i] == '(') {
         int compteur = 0;
         size_t j = i;
         while (compteur != -1) {
            ++j;
            if (expression[j] == '(') {
               ++compteur;
            } else if (expression[j] == ')') {
               --compteur;
            }
         }
         //On remplace les parenthèses par leur contenu
         expression.replace(i, j + 1, to_string(evalueRecursive(expression.substr(i + 1, j - i - 1))));
         //On recommence au début pour trouver val1
         i = -1;
      }
      else if (isdigit(expression[i])) {
         val1 = valeurLongue(expression,i);
      }
      else if (estOperateur(expression[i])) {
         operateur = expression[i];
         char apresOp = expression[i + 1];
         if (isdigit(apresOp)) {
            val2 = valeurLongue(expression,++i);
            expression.replace(0, chiffresDansNbr(val1) + 1 + chiffresDansNbr(val2), to_string(effectuer(val1,operateur,val2)));
         }
      }
   }
   return stoi(expression);
}

int evalue(string const& expression ) {
   string exprRecursive = expression;
   //Retire les espaces vide
   exprRecursive.erase(remove_if(exprRecursive.begin(), exprRecursive.end(), (int(*)(int))(isspace)), exprRecursive.end());
   return evalueRecursive(exprRecursive);
}