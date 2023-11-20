/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/rusuoaica
*/

/*
        Programul foloseste algoritmul lui
    Kruskal. Acesta sorteaza toate muchiile
    grafului (care au costul mai mic decat 
    construirea unui nou tunel). Apoi muchiile
    se parcurg si adauga pe rand.
        Initial sunt creati N arbori, deoarece
    vectorul de tati este scris astfel : root[i] = i;
        In continuare, cand gasim 2 noduri care au tati 
    diferiti, unim cele 2 grafuri, practic face union find.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("rusuoaica.in");
ofstream fout("rusuoaica.out");

int number_of_edges;    // drumurile cu costul mai mic de tunnel_price
int number_of_nodes;    // numarul de statii
int tunnel_price;       // costul construirii unui nou tunel
int all_edges;          // toate drumurile
int result = 0;         // rezultatul final


vector<int> root(100002);

struct edge
{
    int start, finish, cost;
} edges[400005];

/*
    Functia de comparare pentru a sorta elemente de tip struct.
*/

bool cmp(edge first_edge, edge second_edge)
{
    return first_edge.cost < second_edge.cost;
}

/*
    Functia pentru union find.
*/

int getRoot(int x){
    if(root[x] != x){
        root[x] = getRoot(root[x]);
    }
    return root[x];
}

int KruskalsAlgorithm()
{
    sort(edges + 1, edges + number_of_edges + 1, cmp);

    // aici creez cei N arbori

    for(int i = 1; i <= number_of_nodes; i++)
    {
        root[i] = i;
    }    
   
    int added_nodes = 0;

    /*
            Pentru fiecare muchie verific daca punctele 
        care o formeaza au "lider" sau "tati" diferiti.
        In caz afirmatic unesc arborii.
    */ 


    for(int i = 1; i <= number_of_edges; i++)
    {   getRoot(edges[i].start);
        getRoot(edges[i].finish);
        if(root[edges[i].start] != root[edges[i].finish])
        {
            root[root[edges[i].finish]] = edges[i].start;
            added_nodes ++;
            result += 2 * edges[i].cost;
        }
    }

    /*
            Catre restul de noduri nevizitate voi
        construi tuneluri.
    */
    
    int nodes_to_add = number_of_nodes - added_nodes;
    if(nodes_to_add)
    {   
        result += (nodes_to_add - 1) * tunnel_price;
    }

    return result;
}

int main()
{
    fin >> number_of_nodes;
    fin >> all_edges;
    fin >> tunnel_price;

    int start_node, finish_node, price;
    number_of_edges = 0;

    for(int i = 1; i <= all_edges; i++)
    {
        fin >> start_node >> finish_node >> price;
        if(price <= tunnel_price)
        {
            number_of_edges++;
            edges[number_of_edges].start =  start_node;
            edges[number_of_edges].finish = finish_node;
            edges[number_of_edges].cost = price;
        }
        result -= price;
    }

    fout << KruskalsAlgorithm();

   

}
