/*
D. Area
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output

Input
First line contains single integer n — number of vertices of the polygon (3 ≤ n ≤ 100 000).

Next n lines contain coordinates of the vertices in a clockwise or counterclockwise direction.

All coordinates are integers with absolute values not exceeding 10^4.

Output
Output a single number — area of the polygon.

Example
input
3
1 0
0 1
1 1
output
0.5
*/

#include <iostream>


struct Point
{
    int x;
    int y;

    
    Point()
    {}


    Point(int xx, int yy)
        : x(xx)
        , y(yy)
    {}


    Point& operator=(Point& other_point)
    {
        x = other_point.x;
        y = other_point.y;

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& os, Point& point)
    {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }


    int cross_product(Point other_point)
    {
        return x * other_point.y - y * other_point.x;
    }
};


struct Polygon
{
    int size = 0;
    int index = 0;
    Point* arr_of_points;

    ~Polygon()
    {
        if (size > 0)
        {
            delete[] arr_of_points;
        }
    }


    void set_size(int size)
    {
        if (this->size == 0)
        {
            this->size = size;
            this->arr_of_points = new Point[size];
        }
    }


    void add_point(Point point)
    {
        if (index < size)
        {
            arr_of_points[index++] = point;
        }
    }


    friend std::ostream& operator<< (std::ostream& os, Polygon& polygon)
    {
        os << "\n[";
        for (int i = 0; i < polygon.size; ++i)
        {
            os << polygon.arr_of_points[i];
            if (i < polygon.size - 1)
            {
                os << ", ";
            }
        }
        os << "]\n";
        return os;
    }


    double get_area()
    {
        int next_index;
        int double_area = 0;
        for(int i = 0; i < size; ++i)
        {
            next_index = (i < size - 1) ? (i + 1) : 0;
            double_area += arr_of_points[i].cross_product(arr_of_points[next_index]);
        }
        double area = (double) double_area / 2;
        area = (area >= 0) ? area : -area;
        return area;
    }

};


void read_input(int& vert_cnt, Polygon& polygon)
{
    std::cin >> vert_cnt;
    polygon.set_size(vert_cnt);
    int x;
    int y;
    for(int i = 0; i < vert_cnt; ++i)
    {
        std::cin >> x >> y; 
        polygon.add_point(Point(x, y));
    }
}

int main()
{
    int vert_cnt;
    Polygon polygon;
    read_input(vert_cnt, polygon);
    std::cout << polygon.get_area();
    return 0;
}