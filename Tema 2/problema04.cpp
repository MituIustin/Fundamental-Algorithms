/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/trilant
*/

/*
        Pentru a gasi nodul comun, se
    aplica Dijkstra pe fiecare dintre cele
    3 noduri si apoi se calculeaza distanta 
    minima de la fieacre nod de plecare
    pana la punctul i. Drumul este restituit
    cu ajutorul vectorilor de tati.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("trilant.in");
ofstream fout("trilant.out");

#define infinity 9223372036854775807

long long int number_of_nodes;          // nr de noduri
long long int number_of_edges;          // nr de muchii
long long int node1, node2, node3;      // nodurile din care se pleace
long long int index = 0;                // nr iteratiei
                
vector<vector<long long  int>> minimum_distance;                            // vectorul de distante 
vector<vector<long long  int>> root;                                        // vectorii de tati 
vector<vector<pair<long long  int,long long  int>>> nodes(100001);          // matricea de adiacenta

/*
        Aceasta structura permite
    cozii de prioritati sa stie cum
    sa sorteze nodurile.
*/

struct cmp
{
    bool operator()(long long  int x, long long  int y)
    {
        return minimum_distance[index][x] > minimum_distance[index][y];
    }
};

priority_queue<long long  int, vector<long long  int>, cmp> p_queue;


void DijkstrasAlgorithm(long long  int start_node)
{
    vector<bool> in_queue(number_of_nodes + 1, false);

    // adaug doar nodul de start in coada

    minimum_distance[index][start_node] = 0;
    p_queue.push(start_node);
    in_queue[start_node] = true;

    while(!p_queue.empty())
    {
        /*
                Avand o coada de prioritati, nodul catre 
            care se ajunge cu costul cel mai mic va fi
            in capul cozii.
        */

        long long  int current_node = p_queue.top();
        p_queue.pop();
        in_queue[current_node] = false;
        long long  int edges_size = nodes[current_node].size();

        // parcurgem muchiile care pleaca din nodul preluat

        for(long long  int i = 0; i < edges_size; i++)
        {
            long long  int node_to_update = nodes[current_node][i].first;      // vecin
            long long  int price_of_node = nodes[current_node][i].second;      // costul pana la vecin

            // aici updatez costul in cazul in care am gasit un path mai putin costisitor si setez noul tata

            if(minimum_distance[index][current_node] + price_of_node < minimum_distance[index][node_to_update])
            {
                root[index][node_to_update] = current_node;
                minimum_distance[index][node_to_update] = minimum_distance[index][current_node] + price_of_node;
                if(in_queue[node_to_update] == false)
                {
                    p_queue.push(node_to_update);
                    in_queue[node_to_update] = true;
                }
            }
        }
    }

    // se mareste iteratia

    index++;
}

int main()
{
    // citire
    
    fin >> number_of_nodes;
    fin >> number_of_edges;
    fin >> node1 >> node2 >> node3;

    // initializare vector de distante cu numere mari

    vector<long long  int> temp(number_of_nodes + 1, infinity);
    minimum_distance.push_back(temp);
    minimum_distance.push_back(temp);
    minimum_distance.push_back(temp);

    // initializare vectori de tati

    vector<long long  int> fathers;
    for(long long  int i = 0; i <= number_of_nodes; i++)
    {
        fathers.push_back(i);
    }
    root.push_back(fathers);
    root.push_back(fathers);
    root.push_back(fathers);

    long long  int start, finish, price;
    
    for(long long  int i = 1; i <= number_of_edges; i++)
    {
        fin >> start >> finish >> price;

        nodes[start].push_back(make_pair(finish, price));
        nodes[finish].push_back(make_pair(start, price));    
    }
    
    DijkstrasAlgorithm(node1);
    DijkstrasAlgorithm(node2);
    DijkstrasAlgorithm(node3);

    // cautam nodul cel mai favorabil

    long long  int node = -1;
    long long  int min_value = infinity;
    
    for(long long  int j = 1; j <= number_of_nodes; j++)
    {
        if(minimum_distance[0][j] + minimum_distance[1][j] + minimum_distance[2][j] < min_value)
        {
            min_value = minimum_distance[0][j] + minimum_distance[1][j] + minimum_distance[2][j];
            node = j;
        }
    }

    // reconstruim drumurile inapoi

    fout << min_value << "\n";
    
    for(long long  int i = 0; i < 3; i++)
    {
        long long  int cnt = 1;
        long long  int father = node;
        vector <long long  int> t;
        t.push_back(father);
        while(root[i][father] != node1 && root[i][father] != node2 && root[i][father] != node3)
        {
            father = root[i][father];
            t.push_back(father);
            cnt++;
        }
        if(root[i][father] != t[cnt - 1])
        {
            cnt++;
            t.push_back(root[i][father]);
        }
        fout << cnt << " ";
        for(long long  int j = 0; j < cnt; j++)
        {
            fout << t[j] << " ";
        }
        fout << "\n";
    }
    return 0;
}
