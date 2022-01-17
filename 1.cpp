/*
A. Point on the Line segment
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output

Input
Single line contains six integers — coordinates of the point and ends of the line segment.

Output
Output YES, if point lies on the line segment, and NO — otherwise

Examples
input
3 3 1 2 5 4
output
YES

input
4 2 4 2 4 5
output
YES
*/

#include <iostream>


struct Point
{
    int x;
    int y;


    Point()
    {}


    Point(int x, int y)
        : x(x)
        , y(y)
    {}


    friend std::ostream& operator<< (std::ostream& os, const Point& point)
    {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }


    Point operator- (const Point& second) const
    {
        return Point(this->x - second.x, this->y - second.y);
    }


    int operator& (const Point& second) const
    {
        return this->x * second.y - this->y * second.x;
    }
};


struct Segment
{
    Point start;
    Point end;


    Segment(Point& start, Point& end)
        : start(start)
        , end(end)
    {}


    friend std::ostream& operator<< (std::ostream& os, const Segment& segment)
    {
        os << "[" << segment.start << ": " << segment.end << "]";
        return os;
    }


    bool point_on(const Point& point) const
    {
        if (((end - point) & (point - start)) != 0)
        {
            return false;
        }
        if (point.y > std::max(start.y, end.y) || point.y < std::min(start.y, end.y))
        {
            return false;
        }
        if (point.x > std::max(start.x, end.x) || point.x < std::min(start.x, end.x))
        {
            return false;
        }
        return true;
    }
};


void read_input(Point& point, Point& start, Point& end)
{
    std::cin >> point.x >> point.y >> start.x >> start.y >> end.x >> end.y;
}


int main()
{
    Point point;
    Point start;
    Point end;

    read_input(point, start, end);
    Segment segment = Segment(start, end);
    if (segment.point_on(point) == 1)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    
    return 0;
}
