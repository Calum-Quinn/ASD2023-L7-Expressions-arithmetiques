#include "evaluator.h"
#include <string>
#include <algorithm>
#include <cmath>

using opData = char;
using valData = int;

using namespace std;

// a compléter avec une définition récursive de la fonction evalue
// qui n'utilise pas de pile

    /**
     * @name            : estOperateur
     *
     * @but             : définir si un char est un opérateur
     *
     * @param c         : char à vérifier
     * @return          : bool qui vaut true si c est un opérateur
     * @throws          : NIL
     */
bool estOperateur(const opData c) {
   return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

    /**
     * @name            : effectuer
     *
     * @but             : faire le calcul entre deux valeurs avec un opérateur
     *
     * @param val1      : première valeur
     * @param op        : opérateur à effectuer
     * @param val2      : deuxième valeur
     * @return          : valeur du calcul
     * @throws          : NIL
     */
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

    /**
     * @name            : chiffresDansNbr
     *
     * @but             : donner le nombre de chiffres dans un nombre
     *
     * @param nbr       : nombre à vérifier
     * @return          : la quantité de chiffres
     * @throws          : NIL
     */
valData chiffresDansNbr(valData nbr) {
   return valData(log10(nbr)) + 1;
}

    /**
     * @name            : valeurLongue
     *
     * @but             : définir si le chiffre est le début d'un plus lon nombre
     *
     * @param expression: string contenant l'expression
     * @param pos       : pos du chiffre à vérifier
     * @return          : la valeur du nombre
     * @throws          : NIL
     */
valData valeurLongue(string expression, size_t& pos) {
   size_t j = 0;
   //Boucle tant que c'est des chiffres
   while(isdigit(expression[pos + j])){
      ++j;
   }

   valData valeur = stoi(expression.substr(pos,j));

   //Avance dans l'expression pour ne pas contrôler les autre chiffres du même nombre
   pos += size_t(chiffresDansNbr(valeur) - 1);

   return valeur;
}

    /**
     * @name            : evalueRecursive
     *
     * @but             : fonction principale qui calcul le résultat d'une expression
     *                    arithmétique avec un algorithme récursif
     *
     * @param expression: expression à évaluer
     * @return          : valeur de l'expression
     * @throws          : bad_expression
     */
valData evalueRecursive(string expression) {
   for (size_t i = 0; i < expression.size(); ++i) {
      valData val1;
      valData val2;
      opData operateur;
      if (expression[i] == '(') {
         //La parenthèse est suivi directement d'un opérateur
         if (estOperateur(expression[i + 1])) {
            throw bad_expression();
         }
         int compteur = 0;
         size_t j = i;
         //Trouve la bonne parenthèse fermante en comptant les autres
         while (compteur != -1) {
            ++j;
            //Pas de parenthèse fermante
            if (j >= expression.size()) {
               throw bad_expression();
            }
            if (expression[j] == '(') {
               ++compteur;
            } else if (expression[j] == ')') {
               --compteur;
            }
         }
         //On remplace les parenthèses par leur contenu
         expression.replace(i, j + 1, to_string(evalueRecursive(expression.substr(i + 1, j - i - 1))));
         //On recommence au début pour réévaluer val1
         i = size_t(-1);
      }
      else if (isdigit(expression[i])) {
         val1 = valeurLongue(expression,i);
      }
      else if (estOperateur(expression[i]) && i != 0) {
         operateur = expression[i];
         opData apresOp = expression[i + 1];
         //Deux opérateurs à la suite
         if (estOperateur(apresOp)) {
            throw bad_expression();
         }
         //Opérateur suivi d'un nombre
         else if (isdigit(apresOp)) {
            val2 = valeurLongue(expression,++i);
            //Remplace deux valeurs et un opérateur par la valeur calculée
            expression.replace(0, size_t(chiffresDansNbr(val1)) + 1 + size_t(chiffresDansNbr(val2)), to_string(effectuer(val1,operateur,val2)));
         }
      }
   }
   return stoi(expression);
}

    /**
     * @name            : evalue
     *
     * @but             : appeler la fonction evalueRecursive pour évaluer l'expression
     *
     * @param expression: expression à évaluer
     * @return          : valeur de l'expression
     * @throws          : NIL
     */
int evalue(string const& expression ) {
   //On fait une copie pour pouvoir modifier l'expression
   string exprRecursive = expression;
   //Retire les espaces vide
   exprRecursive.erase(remove_if(exprRecursive.begin(), exprRecursive.end(), (int(*)(int))(isspace)), exprRecursive.end());
   return evalueRecursive(exprRecursive);
}