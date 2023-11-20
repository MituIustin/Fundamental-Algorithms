/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/cablaj
*/

/*
        Acesta este implementarea
    algoritmului lui Prim. Solutia pastreaza
    o lista de distante de la componenta conexa
    la fiecare nod nevizitat, si o updateaza
    pentru fiecare nod nou adaugat.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("cablaj.in");
ofstream fout("cablaj.out");

int number_of_cities;

struct point
{
    double x, y;
} cities[3002];

// sqrt ( (x1 - x2) ^ 2 + (y1 - y2) ^ 2 )

double distance(int index1, int index2)
{
    return sqrt((cities[index1].x - cities[index2].x) * (cities[index1].x - cities[index2].x) +
                (cities[index1].y - cities[index2].y) * (cities[index1].y - cities[index2].y));
}

double primsAlgorithm()
{
    /*
        visited = vectorul care retine ce noduri au fost adaugate
        distances = distances[i] reprezinta distanta minima de la nodul i la componenta conexa
        root = de unde a plecat fiecare nod adaugat
    */

    vector<bool> visited(number_of_cities, false);
    vector<double> distances(number_of_cities, 999999);
    vector<int> root(number_of_cities, -1);

    // pornim de la nodul 0

    distances[0] = 0;
    visited[0] = true;
    root[0] = 0;

    int last_node = 0;
    double result = 0.0;

    // vom adauga n - 1 noduri

    for (int i = 1; i < number_of_cities; i++)
    {
        /*
                In minimum pastrez distanta dintre
            componenta conexa si cel mai apropiat nod.
            index reprezinta indicele acestui nod.
        */

        double minimum = 999999;
        int index = -1;
        
        for (int j = 0; j < number_of_cities; j++)
        {
            if (!visited[j])
            {
                /*
                        Pt. fiecare nod nevizitat
                    calculam distanta de la el la 
                    ultimul nod adaugat, daca e mai mica
                    decat ultima distanta calculata 
                    updatam distanta si root-ul.
                */

                double dist = distance(last_node,j);
                
                if(distances[j] > dist)
                {
                    distances[j] = dist;
                    root[j] = last_node;
                }

                // aici caut cel mai apropiat nod

                if(distances[j] < minimum)
                {
                    minimum = distances[j];
                    index = j;
                }
            }
        }

        // adaug nodul gasit

        result += minimum;
        visited[index] = true;
        last_node = index;

    }

    return result;
}

int main()
{
    // citire

    fin >> number_of_cities;
    for (int i = 0; i < number_of_cities; i++)
    {
        fin >> cities[i].x >> cities[i].y;
    }

    fout << fixed << setprecision(9) << primsAlgorithm() << "\n";
}
