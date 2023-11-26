/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/apm2
*/

/*
        Algoritmul creaza un MST 
    folosind Kruskal si adauga muchiile
    folosite in MST in mst_edges.
        Pentru fiecare muchie noua
    fortez adaugarea ei in MST si calculez
    distanta MST ului fara muchia fortata.
    Costul maxim o sa fie costul MST ului
    initial - rezultatul MST ul cu muchia 
    fortata - 1 (pentru a ne a asifura ca 
    muchia sigur intra in MST).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

vector<int> parent(100005);         // vector de tati
vector<int> std_rank(100005);       // nivelul nodurilor

int number_of_nodes;
int number_of_edges;
int new_edges;

struct edge
{
    int start, finish, cost;
} edges[100005], new_edg[1005], mst_edges[100005];

/*
    edges = toate muchiile initiale
    new_edg = muchiile adaugate ulterior
    mst_edges = muchiile MST-ului 
*/

// functia de comparare 

bool cmp(edge& first_edge, edge& second_edge)
{
    return first_edge.cost < second_edge.cost;
}

// folosita inainte de fiecare Union Find 

void init()
{
    for (int i = 1; i <= number_of_nodes; ++i) 
    {
        parent[i] = i;
        std_rank[i] = 0;
    }
}

// find function

int find(int x) 
{
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// union function

bool unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (std_rank[rootX] < std_rank[rootY]) {
            parent[rootX] = rootY;
        } else if (std_rank[rootX] > std_rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            std_rank[rootY]++;
        }
        return true;
    }
    return false;
}

void solve()
{
    int i;
    int total_length = 0;

    // Kruskal

    sort(edges + 1, edges + number_of_edges + 1, cmp);
    init();

    int count = 0;
    
    for(i = 1; i <= number_of_edges; i++)
    {
        if(unionSets(edges[i].start, edges[i].finish))
        {   
            // aici copiez muchiile

            count++;
            mst_edges[count].start = edges[i].start;
            mst_edges[count].finish = edges[i].finish;
            mst_edges[count].cost = edges[i].cost;

            total_length += edges[i].cost;
          
        }  
    }

    int length, j;

    

    for(i = 1; i <= new_edges; i++)
    {
        // fortez fiecare muchie din new_edges intr un ulterior MST
        length = 0;
        init();
        unionSets(new_edg[i].start, new_edg[i].finish);

        // Kruskal

        for(j = 1; j <= count; j++)
        {
            if(unionSets(mst_edges[j].start, mst_edges[j].finish))
            {
                length += mst_edges[j].cost;
            }
        }

        fout << total_length - length - 1 << "\n";
    }
}

int main()
{
    // citire 

    fin >> number_of_nodes >> number_of_edges >> new_edges;

    for(int i = 1; i <= number_of_edges; i++)
    {
        fin >> edges[i].start >> edges[i].finish >> edges[i].cost;
    }

    for(int i = 1; i <= new_edges; i++)
    {
        fin >> new_edg[i].start >> new_edg[i].finish;
    }

    solve();
}
