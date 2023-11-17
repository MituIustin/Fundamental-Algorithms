/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/course-schedule-ii/
*/

/*
        Algoritmul face o parcurgere topologica.
    Mai exact, este Algoritmul lui Kahn.
        Practic algoritmul ia nodurile cu gradul inter 0
    si le baga intr-un vector. Gradul vecinilor nodurilor din 
    vector este decrementat si nodul este pus in vectorul
    cu rezultatul asteptat. 
*/

#include <iostream>
#include <vector>

using namespace std;

// functie care creaza graful dar calculeaza si gradul intern

void create_directed_graph(vector<vector<int>> &prerequisites, vector<vector<int>> &edges, vector<int> &indgr) 
{
    for(int i = 0; i < prerequisites.size(); i++)
    {
        edges[prerequisites[i][1]].push_back(prerequisites[i][0]);
        indgr[prerequisites[i][0]]++;
    }
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
{
    vector<vector<int>> edges(numCourses); 
    vector<int> indgr(numCourses, 0);
    create_directed_graph(prerequisites, edges, indgr);

    vector<int> result;     // vectorul cu ordinea rezultata
    vector<int> nodes0;     // vectorul ce contine noduri de gr. int. = 0

    for(int i = 0; i < numCourses; i++)
    {
        if(indgr[i] == 0)
        {
            nodes0.push_back(i);
        }
    }

    while(nodes0.size() > 0)
    {
        // aici iau nodul din dreapta si il adaug la result

        int node = nodes0[nodes0.size()-1]; 
        nodes0.pop_back();
        result.push_back(node);

        // aici decrementez gradul vecinilor nodului node 

        for(int i = 0; i < edges[node].size(); i++)
        {
            indgr[edges[node][i]]--;

            // in cazul in care am mai "deblocat" un nod, il adaug in nodes0

            if(indgr[edges[node][i]] == 0)
            {
                nodes0.push_back(edges[node][i]);
            }
        }
    }

    // daca nu a fost niciun ciclu, inseamna ca nr de elemente = nr de cursuri

    if(result.size() != numCourses)
    {
        vector<int> impossible;
        return impossible;
    }

    return result;
}   

int main()
{
    // citirea

    int n_nodes;
    int n_edges;
    vector<vector<int>> edges;

    cout << "Number of courses = ";
    cin >> n_nodes;
    cout << "Number of prerequisites = ";
    cin >> n_edges;
    cout << "\n";

    for(int i = 0; i < n_edges; i++)
    {
        int node1, node2;
        vector<int> temp_vec;

        cout << "Prerequisite number " << i + 1 << "\n";
        cout << "First course = " ;
        cin >> node1;
        cout << "Second course = " ;
        cin >> node2;
        cout << "\n";

        temp_vec.push_back(node1);
        temp_vec.push_back(node2);
        edges.push_back(temp_vec);

    }

    vector<int> order;
    order = findOrder(n_nodes, edges);

    cout << "The order is: ";
    for(int i = 0; i < order.size(); i++)
    {
        cout << order[i] << " ";
    }
}