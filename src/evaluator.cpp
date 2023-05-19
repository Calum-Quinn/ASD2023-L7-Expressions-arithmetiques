#include "evaluator.h"
#include <stack> // std::stack
#include <cctype>
#include <string>

using namespace std;

using opData = char;
using valData = int;

// a compléter avec une définition de la fonction evalue qui met en
// oeuvre l'algorithme à 2 piles

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
      default : return 0;
   }
}

int evalue(string const& expression ) {

   stack<opData> operateurs;
   stack<valData> valeurs;
   string valActuel;

   for (const char& i : expression) {
      if (estOperateur(i)) {
         if (!valActuel.empty()) {
            valeurs.push(stoi(valActuel));
            valActuel = "";
         }
         operateurs.push(i);
      }
      else if (isdigit(i)) {
         valActuel += i;
      }
      else if (i == ')') {
         if (!valActuel.empty()) {
            valeurs.push(stoi(valActuel));
            valActuel = "";
         }

         //Contrôle s'il y a deux valeurs
         if (valeurs.size() <= 1) {
            throw bad_expression();
         }

         valData val2 = valeurs.top();
         valeurs.pop();
         opData op = operateurs.top();
         operateurs.pop();
         valData  val1 = valeurs.top();
         valeurs.pop();

         valeurs.push(effectuer(val1,op,val2));
      }
   }

   valData temp = valeurs.top();
   valeurs.pop();

   if (!valeurs.empty() || !operateurs.empty()) {
      throw bad_expression();
   }

   return temp;
}