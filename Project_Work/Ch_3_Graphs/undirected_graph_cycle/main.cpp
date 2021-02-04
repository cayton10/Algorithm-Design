//
//  main.cpp
//  graph_problem_1
//
//  Created by Benjamin Paul Cayton on 2/3/21.
//

#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <fstream>


using namespace std;

int main() {
    
    //Declare string to store graph info
    string graphInfo;
    string fileName = "graph.txt";
    ifstream inData; //Declare input file stream holding graph information
    
    inData.open(fileName.c_str()); //Hard coded, but can change if necessary
    
    if(!inData)
    {
        cout << "Unable to open file. Please add graph.txt" << endl;
    }
    
    //If the file's opened, read all lines of the file and store as string
    if(inData.is_open())
    {
        while(getline(inData, graphInfo))
        {
            cout << graphInfo << "\n";
        }
    }

    inData.close();//Close file after rading
    
    //Test by reading in the graph
    
    return 0;
}
