//
//  main.cpp
//  graph_problem_1: Detect whether or not a cycle exists within the sample graph
//  I referenced the GG tutorial on processing cycles with bfs from this website:
//  https://www.geeksforgeeks.org/detect-cycle-in-an-undirected-graph-using-bfs/
//
//  Created by Benjamin Paul Cayton on 2/1/21.
//

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <vector>


using namespace std;


bool isConnected(vector<int> adjacency[], int vert, int V, vector<bool> & visited)
{
    //Set parent vectors
    vector<int> parent(V, -99);

    //Create queue for BFS
    queue<int> queue;

    //Mark current node as visited and place into queue
    visited[vert] = true;
    queue.push(vert);

    while(!queue.empty())
    {
        //Set value for tail
        int u = queue.front();
        queue.pop();

        //Read all nodes adjacent to u
        for(auto v : adjacency[u])
        {
            //Use parent nodes as trackers to visit children
            if(!visited[v])
            {
                visited[v] = true;
                queue.push(v);
                //Set the parent nodes
                parent[v] = u;
            }
            else if(parent[u] != v)
            {
                return true;
            }
        }
    }
    return false;

}

bool checkVisited(vector<int> adjacency[], int Nodes)
{
    //Create a vector for nodes visited and set all to false
    vector<bool> visited(Nodes, false);

    //For loop to traverse graph
    for (int i = 0; i < Nodes; i++)
        if (!visited[i] && isConnected(adjacency, i, Nodes, visited))
        {
            return true;
        }

    return false;
}


int main() {
    
    string fileName = "graph.txt";
    ifstream inData; //Declare input file stream holding graph information
    
    int V; //Total node count var
    int E; //Total edge count var

    int v; //Head int
    int u; //Tail int

    //Have to read value from file as string - following vars store those strings
    string head;
    string tail;
    
    inData.open(fileName.c_str()); 
    
    if(!inData)
    {
        cout << "Unable to open file. Please add graph.txt" << endl;
    }
    //Get values for nodes and edges
    if(inData.is_open())
    {
        string nodes;
        string edges;

        getline(inData, nodes);
        V = stoi(nodes);

        getline(inData, edges);
        E = stoi(edges);
    }

    cout << "Nodes: " << V << endl;
    cout << "Edges: " << E << endl;

    //Create our adjacency list (vector)
    vector<int> adjacency[V];
    
    //If the file's opened, read all lines of the file and store as string
    if(inData.is_open())
    {
        string Edge; //Variable to store whole line

        for(int j = 0; j < E; j++)
        {
            getline(inData, Edge);
            head = Edge[0]; //Get head of edge
            v = stoi(head); //Convert that value to an int
            tail = Edge[2]; //Get tail of edge
            u = stoi(tail); //Convert tail string to int

            //Add the node pairs to the adjacency list
            adjacency[v].push_back(u);
            adjacency[u].push_back(v);
        }
        
    }

    inData.close();//Close file after reading

    //Process the adjacency list
    
    //Wrote the loop below to make sure the adjacency list was being properly populated
/*
    for(int i = 0; i < V; ++i)
    {
        cout << "Elements at index " << i << ": ";

        for(auto it = adjacency[i].begin(); it != adjacency[i].end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
*/

    //Call checkVisited method which returns boolean
    if(checkVisited(adjacency, V))
    {
        //If the method returns true, there was a cycle
        cout << "Cycle detected" << endl;
    }
    else //If false, then no cycle
        cout << "No cycle detected" << endl;

    
    return 0;
}
