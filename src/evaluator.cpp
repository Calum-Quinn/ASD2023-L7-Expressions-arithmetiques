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

int evalue(string const& expression ) {

   stack<opData> operateurs;
   stack<valData> valeurs;

   for (const opData& i : expression) {
      if (estOperateur(i)) {
         operateurs.push(i);
      }
      else if (isdigit(i)) {
         valeurs.push(i);
      }
      else if (i == ')') {
         string expr = to_string(valeurs.top()) + to_string(operateurs.top());
         valeurs.pop();
         operateurs.pop();
         expr += to_string(valeurs.top());
         valeurs.push(evalue(expr));
      }

      return valeurs.top();
   }

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