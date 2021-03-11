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

    //If end times are equal, give us MWF classes first
    if(a.days == b.days)
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
 * Takes vector<string>, Course::iterator and Course
 * Only called if scheduling conflict exists. Updates conflict vector
 */
void recordConflict(const deque<Course>::const_iterator& c1, const Course& c2, vector<Course>& conf)
{
    conf.push_back(*c1);
    conf.push_back(c2);  
}

/**
 * Takes 2 args: deque of Course, vector of Room
 * Adds class sessions to rooms if there are no conflicts. Returns a vector of strings.
 * If any scheduling conflicts exist, they are stored in the returned vector, else empty.
 */
vector<Course> addClasses(deque<Course>& courses, vector<Room>& rooms)
{
    //Conflict list
    vector<Course> conflicts;
    //Store name of conflicting class if one exists
    Course conflictDetails;
    //Course iterator
    deque<Course>::const_iterator course = courses.begin();

    while(course != courses.end())
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
                }
                else if(!room->sessions.empty())
                {
                    
                    Course last = room->sessions.back();

                    if(course->startTime >= last.endTime || course->days != last.days)
                    {
                        room->sessions.push_back(*course);
                        slotFilled = true;
                    }
                    else
                    {
                        //Because of scope, store last course details here in case we can't find a room that works
                        conflictDetails.name = last.name;
                        conflictDetails.startTime = last.startTime;
                        conflictDetails.endTime = last.endTime;
                        conflictDetails.days = last.days;
                        conflictDetails.size = last.size;
                    }
                }
            }
            room++;
            if(room == rooms.end() && !slotFilled)
            {
                recordConflict(course, conflictDetails, conflicts);
            }
        }
        course++;
    }

    return conflicts;
        
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


/**
 * Takes one arg. Vector of Course (Conflicts list)
 * only called if vector is not empty.
 */
void printConflicts(const vector<Course>& c)
{
    cout << "\n";
    cout << right << setfill('*') << setw(28) << "SCHEDULE" << right << setw(24) << "\n";
    cout << right << setw(28) << "CONFLICT" << right << setw(24) << "\n";
    cout << left << setfill(' ') << setw(10) << "\nCourse" << setw(8) << "Start" << setw(8) << "End" << setw(8) << "Days" << setw(5) << "Size\n";
    
    for(const auto& crs : c)
    {
        cout << left << setw(9) << crs.name << setw(8) << crs.startTime << setw(8) << crs.endTime << setw(8) << crs.days << setw(5) << crs.size << "\n";
    }
    cout << "\n";
}

/**
 * Void function takes one parameter: vector of type <Room> and prints room details 
 */

void printSchedule(const vector<Room>& rooms)
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

    vector<Course> conflicts = addClasses(courses, rooms);

    if(!conflicts.empty())
    {
        printConflicts(conflicts);
    }

    printSchedule(rooms);

    return 0;
}
