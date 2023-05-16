#include "evaluator.h"
#include <string>

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

int evalueRecursive(string expression) {
   for (size_t i = 0; i < expression.size(); ++i) {
      int val1;
      int val2;
      char operateur;
      if (expression[i] == '(') {
         int compteur = 0;
         size_t j = 0;
         while (compteur != -1) {
            if (expression[j] == '(') {
               ++compteur;
            } else if (expression[j] == ')') {
               --compteur;
            }
            ++j;
         }
         expression.replace(i, j, evalueRecursive(expression.substr(i, j)));
      }
      else if (isdigit(expression[i])) {
         size_t j = 1;
         while(isdigit(expression[i + j])){
            ++j;
         }

         val1 = stoi(expression.substr((i,j)));
         val2 = evalueRecursive(LaPartieQuiSuit selon le type de caractère qui suit l'opérateur');
      }
      else if (estOperateur(expression[i])) {
         operateur = expression[i];
      }
   }
}

int evalue(string const& expression ) {
   string exprRecursive = expression;
   return stoi(evalueRecursive(expression));
}

