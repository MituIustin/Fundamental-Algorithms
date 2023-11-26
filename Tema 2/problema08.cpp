/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
*/

/*
        Algoritmul foloseste Kruskal pentru a crea un MST.
    Apoi, pt fiecare muchie scoasa mai creaza cate un MST, 
    Daca aceste MST-uri nu pot fi create, sau au o lungime
    mai mare decat cea a MST-ului original, inseamna ca
    sunt "critical edges". Altfel, se verifica daca sunt
    "pseudo critical edges". Practic fiecare muchie se 
    forteaza in ulterioarele MST-uri, iar daca se pot
    obtine MST-uri de aceleasi lungimi, inseamna ca sunt
    "pseudo critical edges".
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

vector<int> parent(102);
int number_of_nodes;
int number_of_edges;

struct edge
{
    int start, finish, cost;
    int original_index;
} edges[5000];

bool cmp(edge first_edge, edge second_edge)
{
    return first_edge.cost < second_edge.cost;
}

// union find

int init()
{
    for (int i = 0; i < number_of_nodes; ++i) {
        parent[i] = i;
    }
}

int find(int x) 
{
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

bool unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        parent[rootX] = rootY;
        return true;
    }
    return false;
}

int KruskalsAlgorithm()
{
    init();
    sort(edges , edges + number_of_edges, cmp);

    int total_cost = 0;

    for (int i = 0; i < number_of_edges; ++i) 
    {
        int start = edges[i].start;
        int finish = edges[i].finish;
        int cost = edges[i].cost;

        if (find(start) != find(finish)) 
        {
            total_cost += cost;
            unionSets(start, finish);
        }
    }

    return total_cost;
}

vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n) 
{
    // aici atribui si cate un index pentru 
    // a stii pe ce pozitie se afla muchia initial

    for(int i = 0; i < number_of_edges; i++)
    {
        edges[i].original_index = i;
    }

    int total_length = KruskalsAlgorithm();

    vector<int> critical_edges;
    vector<int> pseudo_edges;

    // verificam fiecare muchie daca este "critical"

    for(int i = 0; i < number_of_edges; i++)
    {
        // practic tot Kruskal

        int length = 0;
        init();
        for(int j = 0; j < number_of_edges; j++)
        {
            if(i != j && unionSets(edges[j].start, edges[j].finish))
            {
                length += edges[j].cost;
            }
        }

        int count = 0;
        for(int j = 0; j < number_of_nodes; j++)
        {
            if(find(j) == j)
            {
                count++;
            }
        }

        if(length > total_length && count == 1)
        {
            critical_edges.push_back(edges[i].original_index);
        }
        else
        {
            // verificam daca este "pseudo critical"
            // folosesc tot Kruskal doar ca fortez muchia in MST

            init();
            unionSets(edges[i].start, edges[i].finish);
            length = edges[i].cost;
            for(int j = 0; j < number_of_edges; j++)
            {
                if(unionSets(edges[j].start, edges[j].finish))
                {
                    length += edges[j].cost;
                }
            }
            
            if(length == total_length)
            {
                pseudo_edges.push_back(edges[i].original_index);
            }
        }
    }

    vector<vector<int>> temp;
    temp.push_back(critical_edges);
    temp.push_back(pseudo_edges);
    return temp;
    
}

int main()
{
    fin >> number_of_nodes;
    fin >> number_of_edges;

    for(int i = 0; i < number_of_edges; i++)
    {
        fin >> edges[i].start >> edges[i].finish >> edges[i].cost;
    }
    
    vector<vector<int>> temp;
    temp = findCriticalAndPseudoCriticalEdges(number_of_nodes);
    for(int i = 0; i < temp.size(); i++)
    {
        for(int j = 0; j < temp[i].size(); j++)
        {
            cout << temp[i][j] << " ";
        }
        cout << "\n";
    }
}
