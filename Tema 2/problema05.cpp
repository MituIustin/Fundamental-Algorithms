/*
    Mitu Iustin Aurelian 251 
    https://www.infoarena.ro/problema/dragoni
*/

/*
        Cerinta a se face cu un DFS simplu
    iar cerinta b se face cu un Dijkstra modificat.
    Punctaj : 20 p.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

ifstream fin("dragoni.in");
ofstream fout("dragoni.out");

#define infinity 2147483647
#define minus_infinity -2147483648

int request;
int number_of_nodes;
int number_of_edges;
int result;

vector<vector<pair<int,int>>> nodes(803);  // matricea de adiacenta
vector<int> power(803);                    // puterea dragonilor
vector<int> root(803, 1);                  // root ul pentru union find

// aici fac citireas

void get_input()
{
    fin >> request;
    fin >> number_of_nodes;
    fin >> number_of_edges;

    for(int i = 1; i <= number_of_nodes; i++)
    {
        fin >> power[i];
    }
    
    int from, to, price;
    for(int i = 0; i < number_of_edges; i++)
    {
        fin >> from >> to >> price;
        nodes[from].push_back(make_pair(to,price));
    }
}

// parcurg insulele cu dragonul de pe insula 1
// si caut dragonul cu cea mai mare putere

void dfs(vector<bool> &visited, int node_to_check, int &maximum, int &power_of_dragon)
{
    int edges_size = nodes[node_to_check].size();
    for(int i = 0; i < edges_size; i++)
    {
        if(nodes[node_to_check][i].second <= power_of_dragon && visited[nodes[node_to_check][i].first] == false)
        {
            if(power[nodes[node_to_check][i].first] > maximum)
            {
                maximum = power[nodes[node_to_check][i].first];
            }
            visited[nodes[node_to_check][i].first] = true;
            dfs(visited, nodes[node_to_check][i].first, maximum, power_of_dragon);
        }
    }
}

void solve1()
{
    vector<bool> visited(number_of_nodes + 1, false);
    int maximum = power[1];
    visited[1] = true;
    dfs(visited, 1, maximum, power[1]);
    result = maximum;
}

int DijkstrasAlgorithm(int source, int target)
{
    int n_nodes = number_of_nodes;
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> p_queue;
    vector<int> minimum_distances(n_nodes + 1, infinity);
    int power_of_dragon = power[1];
    
    minimum_distances[source] = 0;
    p_queue.push({0, source, power[source]});

    while(!p_queue.empty())
    {
        auto top_element = p_queue.top();
        int current_distance, current_node, current_power;
        tie(current_distance, current_node, current_power) = top_element;

        cout << current_distance << " " << current_node << " " << current_power << "\n";

        p_queue.pop();

        if(current_node == target) return current_distance;

        for(auto& neighbor : nodes[current_node])
        {
            int next_node = neighbor.first;
            int next_price = neighbor.second;

            if(current_distance + next_price < minimum_distances[next_node] 
                || power[current_node] < power[next_node])
            {
                minimum_distances[next_node] = current_distance + next_price;
                power[next_node] = power[current_node];
                p_queue.push({current_distance + next_price, next_node, power[next_node]});
            }
        }
               
        
    }
    result = minimum_distances[n_nodes];
}

void solve2()
{
    DijkstrasAlgorithm(1, number_of_nodes);
}

int main()
{
    get_input();
    if(request == 1) solve1();
    if(request == 2) solve2();
    fout << result;
}
