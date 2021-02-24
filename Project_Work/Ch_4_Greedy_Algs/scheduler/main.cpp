/**
 * Name: Ben Cayton
 * Goal: Make a course schedule for campus rooms with no conflicts
 * Reference: Interval scheduling problems (Algorithms)
 * Date: 2.11.2021
 */

//Dependencies
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
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
    vector<Course> sessions;//Each room will store class sessions for our schedule
};

/**
 * Returns courses in descending order of lecture end times
 */
bool sortClasses(const Course& a, const Course& b)
{
    //If endtimes are not the same, return less end time
    if(a.endTime != b.endTime)
        return a.endTime < b.endTime;

        // ! Fix the strcmp and c_str

    //If end times are equal, give us MWF classes first
    if(strcmp(a.days.c_str(), b.days.c_str()) < 0)
    {
        return a.days < b.days;
    }
    else
        return a.endTime < b.endTime;
}

/**
 * Returns rooms in descending order of room capacity
 */
bool sortRooms(const Room& a, const Room& b)
{
    return a.capacity < b.capacity;
}

/**
 * Takes a Course deque and vector of Rooms as parameters
 * Adds class sessions to rooms if there are no conflicts
 */
string addClasses(deque<Course>& courses, vector<Room>& rooms, bool conflict)
{
    //Returned message to user
    string message = "";
    string conflictName = "";
    int courseCount = 0;
    //Course iterator
    deque<Course>::const_iterator course = courses.begin();

    while(!conflict && course++ != courses.end())
    {
        //Room iterator
        vector<Room>::iterator room = rooms.begin();
        bool slotFilled = false;

        while(!slotFilled && room != rooms.end())
        {
            if(course->size <= room->capacity)
            {
                if(room->sessions.empty())
                {
                    room->sessions.push_back(*course);
                    slotFilled = true;
                    courseCount++;
                }
                else if(!room->sessions.empty())
                {
                    Course last = room->sessions.back();
                    conflictName = last.name;
                    if(course->startTime >= last.endTime || course->days != last.days)
                    {
                        room->sessions.push_back(*course);
                        slotFilled = true;
                        courseCount++;
                    }
                }
            }
            room++;
            if(room == rooms.end() && !slotFilled)
            {
                message = course->name + " could not be scheduled. Conflict with: " + conflictName;
                conflict = true;
            }
        }
    }

    return message;
        
}

    

/**
 * Loads Course struct member variables from user defined JSON file
 */
void createClassesDeque(const json& j, deque<Course>& c)
{
    //Iterate over classes and create structs for container
    for(const auto& item : j["classes"].items())
    {
        Course newCourse;
        newCourse.name = item.key();
        newCourse.days = item.value().at("days");
        newCourse.startTime = item.value().at("start");
        newCourse.endTime = item.value().at("end");
        newCourse.size = item.value().at("size");
        
        c.push_back(newCourse);
    }
}

/**
 * Loads Room struct member variables from user defined JSON file
 */
void createRoomsVector(const json& j, vector<Room>& r)
{
    for(const auto& item : j["rooms"].items())
    {
        Room newRoom;
        newRoom.name = item.key();
        newRoom.capacity = item.value();

        r.push_back(newRoom);
    }

}




/* -------------------------------------------------------------------------- */
/*                                 ENTRY POINT                                */
/* -------------------------------------------------------------------------- */
int main()
{

    //Store the filename as character string for reading
    string userFile;
    
    cout << "Enter the name of the schedule you'd like to process. IE: sched1, sched2, etc." << endl;
    cout << "Filename: ";

    ifstream inData;

    getline(cin, userFile);//Read whole line from user input above
    //Prepend string with directory
    userFile.insert(0, "schedules/");
    //Add file extension
    userFile += ".txt";
    
    inData.open(userFile.c_str());
    json schedule;
    inData >> schedule;
    inData.close();

    //Declare our data structures
    deque<Course> courses; 
    vector<Room> rooms;
    bool conflict = false;
    
    createClassesDeque(schedule, courses);
    createRoomsVector(schedule, rooms);

    //Sort courses / rooms for processing
    sort(courses.begin(), courses.end(), sortClasses);
    sort(rooms.begin(), rooms.end(), sortRooms);

    string message = addClasses(courses, rooms, conflict);

    if(!conflict)
    {
        for(Room room : rooms)
        {
            cout << "Room name: " << room.name << "\n";
            cout << "Room cap: " << room.capacity << "\n";
            cout << "Class list: " << "\n";
            for(Course session : room.sessions)
            {
                cout << session.name << ": Start: " << session.startTime 
                << " End: " << session.endTime 
                << " Days: " << session.days
                << " Size: " << session.size << "\n";
            }
            cout << "\n\n";
        }
    }
    else
    {
        cout << message << endl;
    }
      

    return 0;
}
