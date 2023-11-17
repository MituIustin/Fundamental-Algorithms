/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/critical-connections-in-a-network/
*/

/*
        Acesta este o implementare a
    algoritmului lui Tarjan.
        Graful este parcurs o singura data in DFS,
    si calculeaza pentru fiecare nod "tatal", si 
    stramosul cel mai mic din care poate ajunge la el.
    Daca stramosul nodului este mai mare decat stramosul 
    tatalui inseamna ca intre ele este o legatura critica, 
    adica daca se sterge muchia respectiva, se vor crea mai 
    multe componente conexe.
*/

#include <iostream>
#include <vector>

using namespace std;

// functia care calculeaza lista de adiacenta

void create_undirected_graph(vector<vector<int>> &connections, vector<vector<int>> &edges) 
{
    for(int i = 0; i < connections.size(); i++)
    {
        edges[connections[i][1]].push_back(connections[i][0]);
        edges[connections[i][0]].push_back(connections[i][1]);
    }
}

/*
        Aceasta functie calculeaza cel mai mic
    stramos a nodului k de unde poate proveni.
*/

int calculate_the_lowest(int k, vector<vector<int>> & edges, vector<int> & lowest_time, int parent)
{
    int lowest = lowest_time[k];
    for(int i = 0; i < edges[k].size(); i++)
    {
        if(lowest_time[edges[k][i]] < lowest && edges[k][i] != parent)
        {
            lowest = lowest_time[edges[k][i]];
        }
    }
    return lowest;
}

/*
    k = nodul curent
    lowest_time = vectorul cu cei mai mici stramosi
    parent = vectorul de tati
    visited = vectorul care retine daca nodurile au fost vizitate
    critical_connections = rezultatul final returnat
*/

void dfs(int k, 
        vector<vector<int>> &edges,
        vector<int> & lowest_time,
        vector<int> & parent,
        vector<bool> & visited,
        vector<vector<int>> & critical_connections)
{
    for(int i = 0; i < edges[k].size(); i++)
    {
        if(visited[edges[k][i]] == false)
        {
            visited[edges[k][i]] = true;
            parent[edges[k][i]] = k;
            lowest_time[edges[k][i]] = lowest_time[parent[edges[k][i]]] + 1;
            dfs(edges[k][i], edges, lowest_time, parent, visited, critical_connections);
        }
    }

    lowest_time[k] = calculate_the_lowest(k, edges, lowest_time, parent[k]);

    // daca e adevarat, inseamna ca am gasit o legatura critica

    if(lowest_time[k] > lowest_time[parent[k]])
    {
        vector<int> temp_vect;
        temp_vect.push_back(parent[k]);
        temp_vect.push_back(k);
        critical_connections.push_back(temp_vect);
    }
}

vector<vector<int>> criticalConnections(int number_of_servers, vector<vector<int>>& connections) 
{
    vector<vector<int>> edges(number_of_servers);
    create_undirected_graph(connections, edges);

    vector<int> lowest_time(number_of_servers);
    vector<int> parent(number_of_servers);
    vector<bool> visited(number_of_servers);
    vector<vector<int>> critical_connections;

    parent[0] = 0;
    lowest_time[0] = 0;
    visited[0] = true;

    dfs(0, edges, lowest_time, parent, visited, critical_connections);

    return critical_connections;
}

int main()
{
    // citirea

    int n_nodes;
    int n_edges;
    vector<vector<int>> edges;

    cout << "Number of servers = ";
    cin >> n_nodes;
    cout << "Number of connections = ";
    cin >> n_edges;
    cout << "\n";

    for(int i = 0; i < n_edges; i++)
    {
        int node1, node2;
        vector<int> temp_vec;

        cout << "Connection number " << i + 1 << "\n";
        cout << "First server = " ;
        cin >> node1;
        cout << "Second server = " ;
        cin >> node2;
        cout << "\n";

        temp_vec.push_back(node1);
        temp_vec.push_back(node2);
        edges.push_back(temp_vec);

    }

    vector<vector<int>> critical_connections;
    critical_connections = criticalConnections(n_nodes, edges);

    cout << "The critical connections are:\n";
    for(int i = 0; i < critical_connections.size(); i++)
    {
        cout << critical_connections[i][0] << " " << critical_connections[i][1] << "\n";
    }
}
