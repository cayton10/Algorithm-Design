/**
 * Name: Ben Cayton
 * Goal: Make a course schedule for campus rooms with no conflicts
 * Reference: Interval scheduling problems (Algorithms)
 * Date: 2.11.2021
 */

//Dependencies
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
//Req library for JSON parsing
#include <nlohmann/json.hpp> //https://github.com/nlohmann/json


using json = nlohmann::json;

using namespace std;

/* ----------------------------- DECLARE STRUCTS ---------------------------- */
struct Course 
{
    std::string name;
    std::string days;
    int endTime;
    int size;
    int startTime;
};

struct Room
{
    std::string name;
    int capacity;
    vector<Course> session;//Each room will store clas sessions for our schedule
};

/**
 * Returns courses in descending order of lecture end times
 */
bool sortClasses(const Course& a, const Course& b)
{
    //If endtimes are not the same, return less end time
    if(a.endTime != b.endTime)
        return a.endTime < b.endTime;
    //If end times are equal, give us MWF classes first
    if(strcmp(a.days.c_str(), b.days.c_str()) < 0)
    {
        return a.days < b.days;
    }
    else
        return a.endTime < b.endTime;
}


int main()
{

    //Store the filename as character string for reading
    /*string userFile;
    
    cout << "Enter the name of the schedule you'd like to process. IE: sched1, sched2, etc." << endl;
    cout << "Filename: ";*/

    ifstream inData;
    std::string userFile = "schedules/sched2.txt";

/*
    getline(cin, userFile);//Read whole line from user input above
    //Prepend string with directory
    userFile.insert(0, "schedules/");
    //Add file extension
    userFile += ".txt";
    */

/* ---------------------------- READ IN JSON FILE --------------------------- */
    
    inData.open(userFile.c_str());

    json schedule;
    inData >> schedule;

    inData.close();

    //Declare our data structures
    vector<Course> courses;
    vector<Room> rooms;

/* ----------------- ITERATE OVER JSON - LOAD COURSE VECTOR ----------------- */

    //Iterate over classes and create structs for container
    for(const auto& item : schedule["classes"].items())
    {
        Course newCourse;
        newCourse.name = item.key();
        newCourse.days = item.value().at("days");
        newCourse.startTime = item.value().at("start");
        newCourse.endTime = item.value().at("end");
        newCourse.size = item.value().at("size");
        
        courses.push_back(newCourse);
    }

    //Sort courses by end time
    sort(courses.begin(), courses.end(), sortClasses);

    for(const auto& item : schedule["rooms"].items())
    {
        Room newRoom;
        newRoom.name = item.key();
        newRoom.capacity = item.value();

        rooms.push_back(newRoom);
    }

    for(const Room& item : rooms)
    {
        cout << item.name << ": capacity - " << item.capacity << " seats. \n";
    }


    for(const Course& item : courses)
    {
        cout << item.name << ": " << "\n";
        cout << "  start: " << item.startTime << "\n";
        cout << "  end: " << item.endTime << "\n";
        cout << "  days: " << item.days << "\n";
        cout << "  class size: " << item.size << "\n\n";
    }
  

    return 0;
}
