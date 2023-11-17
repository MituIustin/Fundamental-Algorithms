/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/find-eventual-safe-states/
*/

/*
       Practic algoritmul cauta cicluri, si marcheaza
    elementele din ciclu ca "not safe".
        Acesta parcurge o singura data toate nodurile
    prin DFS. Initial presupunem ca niciu nod nu e safe,
    daca toate nodurile in care pleaca k sunt safe, inseamna
    ca si k este safe. In cazul in care k pleca intr-un nod
    care nu este safe, inseamna ca nici el nu este safe.
        Pentru nodurile din care nu pleaca alte noduri,
    va trece de for-ul de la DFS, si va intoarce 1.
*/

#include <iostream>
#include <vector>

using namespace std;

/*
        Functia DFS care intoarce 1 daca 
    nodul k este safe sau 0 in caz contrar.

    1 inseamna safe
    0 inseamna not safe
    -1 inseamna nevizitat
*/

int dfs(int k, vector<vector<int>> &edges, vector<int> &safe_nodes)
{
    if(safe_nodes[k] != -1) 
    {
        return safe_nodes[k];
    }

    safe_nodes[k] = 0;

    for(int i = 0; i < edges[k].size(); i++)
    {
        // in cazul in care am gasit un vecin not safe, inseamna ca nici k nu este safe

        if(dfs(edges[k][i], edges, safe_nodes) == 0)
        {
            return safe_nodes[k];
        }
    }

    // daca toti vecinii sunt safe, inseamna ca si k este

    safe_nodes[k] = 1;
    return safe_nodes[k];
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) 
{
    vector<int> safe_nodes(graph.size(), -1);
    vector<int> results;

    // apelam DFS pentru toate nodurile nevizitate

    for(int i = 0; i < graph.size(); i++)
    {
        if(dfs(i, graph, safe_nodes) == 1)
        {
            results.push_back(i);
        }
    }
    return results;
}

int main()
{
    // citirea

    int n_nodes;
    vector<vector<int>> edges;
    cout << "Number of nodes = ";
    cin >> n_nodes;
    cout << "\n";

    for(int i = 0; i < n_nodes; i++)
    {
        int number_of_edges;
        vector<int> edges_if_ith_node;
        cout << "Number of edges of node " << i << " = ";
        cin >> number_of_edges;
        for(int j = 0; j < number_of_edges; j++)
        {
            int node;
            cout << "Node " << i << " is connected to node " ;
            cin >> node;
            edges_if_ith_node.push_back(node);
        }
        edges.push_back(edges_if_ith_node);
        cout << "\n";
    }

    vector<int> safe_nodes;
    safe_nodes = eventualSafeNodes(edges);

    cout << "The safe nodes are: \n";
    for(int i = 0; i < safe_nodes.size(); i++)
    {
        cout << safe_nodes[i] << " ";
    }
}
