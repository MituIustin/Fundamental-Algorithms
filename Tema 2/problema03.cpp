/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/camionas/
*/

/*
        Programul foloseste algoritmul lui Dijkstra.
    Fiecare drum care are rezistenta mai mica decat
    greutatea camionului va lua valoarea 1, iar cele 
    care au rezistenta >= greutatea camionului valoarea 0.
        Astfel eu voi afla drumul de cost minim din 
    satul 1 in satul n.
        Aici am abordat varianta care foloseste Priority Queue.
    Coada va mentine in ordine vecinii nodului curent in functie
    de costul acestora, deci intai voi fi vecinii cu cost 0, apoi 
    cei de cost 1.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("camionas.in");
ofstream fout("camionas.out");

#define infinity 2147483647

int number_of_nodes;
int number_of_edges;
int weight;

vector<bool> in_queue(50001, false);                // vector de frecventa
vector<int> minimum_distance(50001, infinity);      // vectorul de distante 
vector<vector<pair<int,int>>> nodes(50001);         // matricea de adiacenta

/*
        Aceasta structura permite
    cozii de prioritati sa stie cum
    sa sorteze nodurile.
*/

struct cmp
{
    bool operator()(int x, int y)
    {
        return minimum_distance[x] > minimum_distance[y];
    }
};

priority_queue<int, vector<int>, cmp> p_queue;


void DijkstrasAlgorithm(int start_node)
{
    // adaug doar nodul de start in coada

    minimum_distance[start_node] = 0;
    p_queue.push(start_node);
    in_queue[start_node] = true;

    while(!p_queue.empty())
    {
        /*
                Avand o coada de prioritati, nodul catre 
            care se ajunge cu costul cel mai mic va fi
            in capul cozii.
        */

        int current_node = p_queue.top();
        p_queue.pop();
        in_queue[current_node] = false;
        int edges_size = nodes[current_node].size();

        // parcurgem muchiile care pleaca din nodul preluat

        for(int i = 0; i < edges_size; i++)
        {
            int node_to_update = nodes[current_node][i].first;      // vecin
            int price_of_node = nodes[current_node][i].second;      // costul pana la vecin

            // aici updatez costul in cazul in care am gasit un path mai putin costisitor

            if(minimum_distance[current_node] + price_of_node < minimum_distance[node_to_update])
            {
                minimum_distance[node_to_update] = minimum_distance[current_node] + price_of_node;
                if(in_queue[node_to_update] == false)
                {
                    p_queue.push(node_to_update);
                    in_queue[node_to_update] = true;
                }
            }
        }
    }
}

int main()
{
    // citire

    fin >> number_of_nodes;
    fin >> number_of_edges;
    fin >> weight;

    int start, finish, path_weight;

    for(int i = 1; i <= number_of_edges; i++)
    {
        fin >> start >> finish >> path_weight;
        path_weight = path_weight < weight ? 1 : 0;

        nodes[start].push_back(make_pair(finish, path_weight));
        nodes[finish].push_back(make_pair(start, path_weight));    
    }

    int start_node = 1;
    int node_to_reach = number_of_nodes;

    DijkstrasAlgorithm(start_node);
    fout << minimum_distance[node_to_reach];
}