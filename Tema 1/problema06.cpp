/*
    Mitu Iustin Aurelian 251
    https://leetcode.com/problems/satisfiability-of-equality-equations/
*/

/*
        Algoritmul are un singur vector numit root.
    Initial toate valorile din root sunt -1.
    Am parcurs intai toate egalitatile "==" si am
    pus toate variabilele in numarul minim de grupuri. 
    Pentru fiecare grup am ales un "lider", practic asta
    reprezinta root[i], cine este liderul lui i. 
        Am tratat toate cele 4 cazuri pe care le voi 
    detalia jos. 
        Apoi am parcurs toate inegalitatile "!=" si 
    daca 2 variabile aveau lideri diferiti inseamna 
    ca nu putem satisface toate conditiile.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
        Cu ajutorul acestor 2 functii am putut
    implementa un vector de frecventa. Practic
    'a' inseamna elementul 0, 'b' = 1, etc.
        Prima functie im preia variabila din stanga
    si intoarce int-ul potrivit, iar a doua functie
    face acelasi lucru pentru variabila din dreapta.
*/

int fst(string equation)
{
    return equation[0] - 'a';
}

int snd(string equation)
{
    return equation[3] - 'a';
}

bool equationsPossible(vector<string>& equations) 
{
    // acesta este vectorul de lider (care e si de frecventa)

    vector<int> root(26, -1);
    
    for(auto equation : equations)
    {
        // aici parcurg toate ecuatiile "=="

        if(equation[1] == '=')
        {
            // cazul 1: variabila 1 are lider, variabila 2 nu are

            if(root[fst(equation)] != -1 && root[snd(equation)] == -1)
            {
                // adaugam variabila 2 la grupul variabilei 1

                root[snd(equation)] = root[fst(equation)];
            }
            else 
            
            // cazul 2: variabila 1 nu are lider, variabila 2 are

            if(root[fst(equation)] == -1 && root[snd(equation)] != -1)
            {
                // adaugam variabila 1 la grupul variabilei 2

                root[fst(equation)] = root[snd(equation)];
            }
            else 
            
            // cazul 3: nicio variabila nu are lider
            
            if(root[fst(equation)] == -1 && root[snd(equation)] == -1)
            {
                // facem prima variabila liderul ambelor variabile

                root[fst(equation)] = fst(equation);
                root[snd(equation)] = fst(equation);
            }
            else 
            
            //cazul 4 ambele variante au un lider (si sunt lideri diferiti)

            if(root[fst(equation)] != -1 && root[snd(equation)] != -1 && root[fst(equation)] != root[snd(equation)])
            {
                // am adaugat toate variabilele din grupul 2 in grupul 1

                int value = root[snd(equation)];
                for(int i = 0; i < 26; i++)
                {
                    if(root[i] == value)
                    {
                        root[i] = root[fst(equation)];
                    }
                }
            }
        }
    }

    for(auto equation : equations)
    {
        if(equation[1] == '!')
        {
            // cazul "a!=a"

            if(fst(equation) == snd(equation))
            {
                return false;
            }

            // daca 2 variabile au lideri diferiti inseamna ca nu se pot satisface conditiile

            if((root[fst(equation)] == root[snd(equation)]) && root[fst(equation)] != -1)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // citirea

    int number_of_equations;
    vector<string> equations;
    cout << "Number of equations = ";
    cin >> number_of_equations;

    for(int i = 0; i < number_of_equations; i++)
    {
        cout << "Equation " << i + 1 << " : ";
        string equation;
        cin >> equation;
        equations.push_back(equation);
    }

    if(equationsPossible(equations))
    {
        cout << "The equations can be satisfied !";
    }
    else
    {
        cout << "The equations can't be satisfied !";
    }
}

