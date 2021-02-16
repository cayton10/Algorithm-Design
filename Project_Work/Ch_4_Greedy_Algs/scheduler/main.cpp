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
    vector<Course> sessions;//Each room will store clas sessions for our schedule
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

void addClasses(deque<Course>& courses, vector<Room>& rooms, bool conflict)
{
    //Iterate through course list and check room info
    for(Course& c : courses)
    {
        for(Room& room : rooms)
        {
            //If class will fit, check availabililty
            if(c.size <= room.capacity)
            {
                //If no classes have been scheduled, add this one
                if(room.sessions.empty())
                {
                    room.sessions.push_back(c);
                    courses.pop_front();
                    break;
                }
                else //Now we have to iterate through this room's session schedule to find a fit
                {
                    //TODO: It's just checking the first class time, dipshit. Make it check most recent.
                    Course last = room.sessions.back();
                    if(c.startTime >= last.endTime || c.days != last.days)
                    {
                        room.sessions.push_back(c);
                        courses.pop_front();
                        break;
                    }
                    /*
                    for(Course& session : room.sessions)
                    {
                        if(c.startTime >= session.endTime && c.days != session.days)
                        {
                            room.sessions.push_back(c);
                            courses.pop_front();
                            break;
                        }
                        else
                            break;
                    }
                    */
                }
            }
        }
    }
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

    for(const Room& item : rooms)
    {
        cout << item.name << ": capacity - " << item.capacity << " seats. \n";
    }

/* ---------------------- OUTPUT CLASS LIST INFORMATION --------------------- */
/*
    for(const Course& item : courses)
    {
        cout << item.name << ": " << "\n";
        cout << "  start: " << item.startTime << "\n";
        cout << "  end: " << item.endTime << "\n";
        cout << "  days: " << item.days << "\n";
        cout << "  class size: " << item.size << "\n\n";
    }
*/

    cout << courses.size() << endl;
    //Send courses to the meat grinder
    addClasses(courses, rooms, conflict);

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
    cout << courses.size() << endl;  

    return 0;
}
