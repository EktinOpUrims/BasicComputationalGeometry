/*
E. Perimeter
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
For given points on a plane find the perimeter of the convex hull.

Input
First line contains a single integer n — number of the points (3 ≤ n ≤ 10^5).

Next n lines contain coordinates of the points — a pair (x, y) one per line ({ - 10}^9 ≤ x, y ≤ 10^9).

Note that, given points can coincide and lay on the same line.

Output
Output the perimeter of the convex hull as accurate as possible.

Example
input
5
0 0
2 0
0 2
1 1
2 2
output
8
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


struct Point
{
    long long x;
    long long y;


    Point()
    {}


    Point(long long x, long long y)
        : x(x)
        , y(y)
    {}


    Point operator-(const Point& other) const
    {
        return Point(this->x - other.x, this->y - other.y);
    }


    friend std::ostream& operator<< (std::ostream& os, const Point& point)
    {
        os << "(" << point.x << ", " << point.y <<")";
        return os;
    }


    long long operator& (const Point& other) const
    {
        return (long long) this->x * other.y - this->y * other.x;
    }


    bool operator< (const Point& other) const
    {
        if (this->x < other.x)
            return true;
        if (this->x == other.x && this->y < other.y)
            return true;
        return false;
    }


    double dist(const Point& point) const
    {
        long long dx = (long long) this->x - point.x;
        long long dy = (long long) this->y - point.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};


struct Polygon
{
    int size;
    std::vector<Point> vec;


    Polygon()
        : size(0)
    {}


    void add_point(const Point& point)
    {
        vec.push_back(point);
        ++size;
    }


    void remove_last()
    {
        vec.pop_back();
        --size;
    }


    friend std::ostream& operator<< (std::ostream& os, Polygon& polygon)
    {
        os << "[";
        for (int index = 0; index < polygon.size; ++index)
        {
            os << polygon.vec[index];
            if (index != polygon.size - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }


    void push(const Point& point)
    {
        while(((vec[size - 1] - vec[size - 2]) & (point - vec[size - 2])) <= 0)
        {
            this->remove_last();
        }
    }


    void convex_hull(Polygon& lower_hull, Polygon& upper_hull)
    {
        Point left = vec[0];
        Point right = vec[size - 1];
        lower_hull.add_point(right);
        lower_hull.add_point(left);
        upper_hull.add_point(left);
        upper_hull.add_point(right);
        
        for (int index = 1; index < size - 1; ++index)
        {
            if (((right - left) & (vec[index] - left)) < 0)
            {
                lower_hull.push(vec[index]);
                lower_hull.add_point(vec[index]);
            }
        }
        if (lower_hull.size >= 3)
        {
            lower_hull.push(right);
        }

        for (int index = size - 2; index > 0; --index)
        {
            if (((right - left) & (vec[index] - left)) > 0)
            {
                upper_hull.push(vec[index]);
                upper_hull.add_point(vec[index]);
            }
        }
        if (upper_hull.size >= 3)
        {
            upper_hull.push(left);
        }
    }


    double modified_perimeter()
    {
        double res = vec[size - 1].dist(vec[0]);
        for (int index = 1; index < size - 1; ++index)
        {
            res += vec[index].dist(vec[index + 1]);
        }
        return res;
    }
};


void read_input(Polygon& polygon)
{
    int size;   
    long long x;
    long long y;
    std::cin >> size;
    for(int index = 0; index < size; ++index)
    {
        std::cin >> x >> y;
        polygon.add_point(Point(x, y));
    }
    std::sort(polygon.vec.begin(), polygon.vec.end());
}


int main()
{
    Polygon polygon;
    read_input(polygon);
    Polygon lower_hull;
    Polygon upper_hull;
    polygon.convex_hull(lower_hull, upper_hull);
    printf("%.15f", lower_hull.modified_perimeter() + upper_hull.modified_perimeter());

    return 0;
}
