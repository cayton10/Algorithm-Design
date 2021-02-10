
//Dependencies
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
//Req library for JSON parsing
#include <nlohmann/json.hpp> //https://github.com/nlohmann/json


using json = nlohmann::json;

using namespace std;

int main()
{

    //Store the filename as character string for reading
    string userFile;
    ifstream inData;
    cout << "Enter the name of the schedule you'd like to process. IE: sched1, sched2, etc." << endl;
    cout << "Filename: ";

    getline(cin, userFile);//Read whole line from user input above
    //Prepend string with directory
    userFile.insert(0, "schedules/");
    //Add file extension
    userFile += ".txt";

/* ---------------------------- READ IN JSON FILE --------------------------- */
    
    inData.open(userFile.c_str());

    json j;
    inData >> j;

    inData.close();

    cout << j["classes"] << endl;
    

    return 0;
}
