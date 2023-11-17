/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/possible-bipartition/
*/

/*
        Algoritmul verifica daca graful este bipartit
    sau nu. Acesta parcurge nodurile cu DFS si incearca 
    sa "coloreze" nodurile doar cu 2 culori, astfel incat
    sa nu existe 2 vecini cu aceeasi culoare.

*/

#include <iostream>
#include <vector>

using namespace std;

/*
    k = nodul curent
    edges = muchiile grafului
    poss_bipart = se returneaza la final
    fathers_color = culoarea nodului de unde 
                    a intrat in nodul k
    color = vectorul de culori :
            -1 = neatins
            0  = prima culoare
            1  = a doua culoare
*/

void dfs(int k, vector<vector<int>> &edges, bool &poss_bipart, int fathers_color, int *color) {

    if (poss_bipart == false)
    {
        return;
    }
    
    for(int i = 0; i < edges[k].size(); i++)
    {
        if(color[edges[k][i]] == color[k])
        {
            poss_bipart = false;
            break;
        }
        else if(color[edges[k][i]] == -1)
        {
            color[edges[k][i]] = fathers_color;
            dfs(edges[k][i], edges, poss_bipart, !fathers_color, color);
        }
    }
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

    vector<vector<int>> edges(n + 1); 
    int color[n + 1];

    for(int i = 0; i <= n; i++)
    {
        color[i] = -1;
    }

    // aici creez lista de muchii

    for (int i = 0; i < dislikes.size(); i++) 
    {
        edges[dislikes[i][0]].push_back(dislikes[i][1]);
        edges[dislikes[i][1]].push_back(dislikes[i][0]);
    }

    bool response = true;

    // folosesc for pentru a ma asigura ca merge 
    // si pe grafuri cu noduri izolate 

    for(int i = 1; i <= n; i++)
    {
        if(color[i] == -1) 
        {
            color[i] = 1;
            dfs(i,edges, response, 0, color);
        }
    }

    return response;
}

int main()
{
    // citirea

    int n_nodes;
    int n_edges;
    vector<vector<int>> edges;

    cout << "Number of nodes = ";
    cin >> n_nodes;
    cout << "Number of edges = ";
    cin >> n_edges;
    cout << "\n";

    for(int i = 0; i < n_edges; i++)
    {
        int node1, node2;
        vector<int> temp_vec;

        cout << "Edge number " << i + 1 << "\n";
        cout << "First node = " ;
        cin >> node1;
        cout << "Second node = " ;
        cin >> node2;
        cout << "\n";

        temp_vec.push_back(node1);
        temp_vec.push_back(node2);
        edges.push_back(temp_vec);

    }

    cout << possibleBipartition(n_nodes, edges);
}