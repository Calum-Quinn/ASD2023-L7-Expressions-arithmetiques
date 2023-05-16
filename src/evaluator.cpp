#include "evaluator.h"
#include <stack> // std::stack
#include <cctype>
#include <string>

#include <iostream>

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
//         //On fait - '0' pour utiliser la valeur représentée par i
//         valeurs.push(i-'0');
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

   if (valeurs.size() || operateurs.size()) {
      throw bad_expression();
   }


   return temp;

//   Dijkstra
//
//   fonction évaluer(expression):
//   pileOp ← Pile vide
//   pileVal ← Pile vide
//   tant qu’il reste des éléments à lire
//   e ← lire un élément(expression)
//   si e est '('
//   ignorer
//   sinon, si e est un opérateur
//   pileOp.push(e)
//   sinon, si e est une valeur numérique
//   pileVal.push(e)
//   sinon, si e est ')'
//   v2 ← pileVal.pop()
//   v1 ← pileVal.pop()
//   op ← pileOp.pop()
//   r ← évaluer v1 op v2
//   pileVal.push(r)
//   retourner pileVal.pop()


}