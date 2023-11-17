/*
    Mitu Iustin Aurelian 251
    https://leetcode.com/problems/shortest-bridge/
*/

/*
        Algortmul foloseste in sine un soi de BKT 
    combinat cu BFS.
        Intai bordez matricea cu -1, apoi caut primul 1
    din matrice si apelez functia de BKT pentru acel nod.
    In first_island o sa mi pastreze toate nodurile primei
    insule.
        Apoi incepe algoritmul de BFS care ia toate nodurile
    din prima insula, si verifica toate nodurile nodurilor
    sus / jos / stana / dreapta si adauga aceste noduri intr-un
    vector nou care il va transmite ca parametru in urmatorul 
    apel BFS. Algoritmul se opreste atunci cand gaseste primul 1 
    in matrice. Avand in vedere ca am pus in locul nodurilor 
    vizitate lungimea drumului, s-ar fi putut determina usor si 
    path-ul parcurs.
*/

#include <iostream>
#include <vector>

using namespace std;

/*
        Functia de bordare, ia ca parametru matricea data
    si returneaza o matrice bordata cu -1.
*/ 

vector<vector<int>> create_new_grid(vector<vector<int>>& grid) 
{
    vector<int> temp_vector;
    for(int i = 0; i < grid.size() + 2; i++)
    {
        temp_vector.push_back(-1);
    }

    vector<vector<int>> new_grid(grid.size() + 2, temp_vector);

    for (int i = 0; i < grid.size(); i++) 
    {
        for (int j = 0; j < grid.size(); j++) 
        {
            new_grid[i + 1][j + 1] = grid[i][j];
        }
    }

    return new_grid;
}

/*
        Functia de bkt, gaseste nodurile primei insule.
            row = linia nodului verificat
            col = coloana nodului verificat
            new_grid = matricea bordata
            first_island = vectorul in care sunt adaugate nodurile
                           primei insule
            x = vector de pozitie pentru linie
            x = vector de pozitie pentru coloana
*/

void bkt(int row, int col, vector<vector<int>>& new_grid, vector<vector<int>>& first_island, vector<int>& x, vector<int>& y)
{
    new_grid[row][col] = 2;

    // aici parcurg practic elementele din x si y

    for(int i = 0; i < 4; i++)
    {
        // daca am gasit noduri de 1 inseamna ca sunt in prima insula, asa ca le adaug

        if(new_grid[row + x[i]][col + y[i]] == 1)
        {
            vector<int> temp_vector;
            temp_vector.push_back(row + x[i]);
            temp_vector.push_back(col + y[i]);
            first_island.push_back(temp_vector);
            bkt(row + x[i], col + y[i], new_grid, first_island, x, y);
        }
    }
}

/*
        Functia de BFS.
    Parametrii:
        nodes_to_check = vectorul cu noduri care trebuiesc verificate
        new_grid = matricea bordata
        path_length = un fel de contor care ne spune ca suntem la pasul k 
                      (Acest parametru este cu 2 mai mare deoarece pe pozitiile
                      unde se afla prima insula am pus valoarea 2.)
        x = vector de pozitie pentru linie
        x = vector de pozitie pentru coloana

*/

void bfs(vector<vector<int>> &nodes_to_check, vector<vector<int>>& new_grid, int path_length, vector<int>& x, vector<int>& y, bool& found, int& length)
{
    if(found) return;

    /* 
            In acest vector voi pune nodurile care
        trebuie verificate la urmatorul apel de BFS.
    */

    vector<vector<int>> new_nodes;

    for(int i = 0; i < nodes_to_check.size() && !found; i++)
    {
        // marchez nodul verificat

        new_grid[nodes_to_check[i][0]][nodes_to_check[i][1]] = path_length;

        for(int j = 0; j < 4; j++)
        {
           if(new_grid[nodes_to_check[i][0]+ x[j]][nodes_to_check[i][1] + y[j]] == 1)
           {    
                found = true;
                length = path_length - 3;
                break;
           }
           else if(new_grid[nodes_to_check[i][0]+ x[j]][nodes_to_check[i][1] + y[j]] == 0)
           {
                new_grid[nodes_to_check[i][0]+ x[j]][nodes_to_check[i][1] + y[j]] = path_length;
                vector<int> temp_vector;
                temp_vector.push_back(nodes_to_check[i][0]+ x[j]);
                temp_vector.push_back(nodes_to_check[i][1] + y[j]);
                new_nodes.push_back(temp_vector);
           }
        }
    }
    path_length++;
    if(!found)
    {
        bfs(new_nodes, new_grid, path_length, x, y, found, length);
    }
}

int shortestBridge(vector<vector<int>>& grid) 
{   
    vector<vector<int>> new_grid = create_new_grid(grid);
    vector<vector<int>> first_island;
    bool found = false;

    // aici caut primul 1 din matrice

    for(int i = 1; i < new_grid.size() - 1 && !found; i++)
    {
        for(int j = 1; j < new_grid.size() - 1; j++)
        {
            if(new_grid[i][j] == 1)
            {
                vector<int> temp_vector;
                temp_vector.push_back(i);
                temp_vector.push_back(j);
                first_island.push_back(temp_vector);
                found = true;
                break;
            }
        }
    }

    // aici creez vectorii de pozitie

    vector<int> x;
    vector<int> y;

    // dreapta           sus             stanga          jos

    x.push_back(1); x.push_back(0); x.push_back(-1); x.push_back( 0);
    y.push_back(0); y.push_back(1); y.push_back( 0); y.push_back(-1);

    bkt(first_island[0][0], first_island[0][1], new_grid, first_island, x, y);

    int path_length = 3;
    found = false;
    int result;

    bfs(first_island, new_grid, path_length, x, y, found, result);
    
    return result;
}

int main()
{
    // citirea
    int n;
    vector<vector<int>> matrix;
    cout << "Number of rows/cols = ";
    cin >> n;

    cout << "Enter the matrix:\n";
    for(int i = 0; i < n; i++)
    {
        vector<int> temp_vector;
        for(int j = 0; j < n; j++)
        {
            int value;
            cin >> value;
            temp_vector.push_back(value);
        }
        matrix.push_back(temp_vector);
    }

    int shortest_bridge = shortestBridge(matrix);

    cout << "The shortest bridge has the a length of " << shortest_bridge << "\n";
}

