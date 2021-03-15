/******************************************************************************

                              Code to visualize 
                problem 12 from 'Algorithm Design - Kleinburg'
                pg 194 a. and b. 

*******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
struct stream
{
    int bits = 0;
    int length = 0;
};

bool streamTest(const vector<stream>& v, const int& r)
{
    int cumulativeLength = 0;
    int limit = r;
    int cumulativeSize = 0;
    bool answer = true;
    vector<stream>::const_iterator itr = v.begin();
    
    while(answer && itr != v.end())
    {
        cumulativeSize += itr->bits;
        cumulativeLength += itr->length;
        limit = r * cumulativeLength;
        
        if(cumulativeSize > limit)
        {
            answer = false;
        }

        itr++;
    }
    
    return answer;
}

bool sortStreams(const stream& a, const stream& b)
{
    return a.bits < b.bits;
}


int main()
{

    const int r = 2000;
    
    stream vid1;
    stream vid2;
    stream vid3;
    vid1.bits = 1000;
    vid1.length = 1;
    vid2.bits = 500;
    vid2.length = 1;
    vid3.bits = 2000;
    vid3.length = 1;
    
    std::vector<stream> vec;
    vec.push_back(vid1);
    vec.push_back(vid2);
    vec.push_back(vid3);
    
    //Sort the vector
    sort(vec.begin(), vec.end(), sortStreams);
    
    bool answer = streamTest(vec, r);
    
    cout << answer << endl;
    
    if(!answer)
    {
        cout << "Schedule is invalid" << endl;
    }

    return 0;
}