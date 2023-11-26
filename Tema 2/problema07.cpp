/*
    Mitu Iustin Aurelian 251 
    https://leetcode.com/problems/cheapest-flights-within-k-stops/
*/

/*
        Algoritmul foloseste Dijkstra modificat.
    In coada se vor adauga nodurile cu o distanta 
    mai mica sau nodurile in care poti ajunge cu 
    numar mai mic de stop-uri.  
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int infinity = 2147483647;



int DijkstrasAlgorithm(int n_nodes, vector<vector<pair<int,int>>> adj, int source, int target, int k){
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> p_queue;
    vector<int> minimum_distances(n_nodes + 1, infinity);
    vector<int> number_of_stops(n_nodes + 1, infinity);
    
    minimum_distances[source] = 0;
    number_of_stops[source] = 0;
    p_queue.push({0, source, 0});
    while(!p_queue.empty())
    {
        auto top_element = p_queue.top();
        int current_distance, current_node, current_stops;
        tie(current_distance, current_node, current_stops) = top_element;
        p_queue.pop();

        if(current_node == target) return current_distance;

        // nu are rost sa verificam daca am trecut de k

        if(current_stops != k+1)
        {
            for(auto& neighbor : adj[current_node])
            {
                int next_node = neighbor.first;
                int next_price = neighbor.second;

                // conditia modificata din Dijkstra

                if(current_distance + next_price < minimum_distances[next_node] 
                    || current_stops + 1 < number_of_stops[next_node])
                {
                    minimum_distances[next_node] = current_distance + next_price;
                    number_of_stops[next_node] = current_stops + 1;
                    p_queue.push({current_distance + next_price, next_node, current_stops + 1});
                }
            }
        }           
        
    }
    return -1;
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) 
{
    vector<vector<pair<int, int>>> adj(n + 1);

    for (auto& flight : flights) 
    {
        int u = flight[0];
        int v = flight[1];
        int w = flight[2];
        adj[u].push_back(make_pair(v, w));
    }

    return DijkstrasAlgorithm(n, adj, src, dst, k);
}

int main()
{
    vector<vector<int>> flights;
    int number_of_cities;
    int number_of_flights;
    int src, dst, k;

    cin >> number_of_cities >> number_of_flights;

    for(int i = 0; i < number_of_flights; i++)
    {
        int from, to, price;
        cin >> from >> to >> price;

        vector<int> temp_vector;
        temp_vector.push_back(from);
        temp_vector.push_back(to);
        temp_vector.push_back(price);

        flights.push_back(temp_vector);
    }

    cin >> src >> dst >> k;

    cout << findCheapestPrice(number_of_cities, flights, src, dst, k);
}

    
