/*
B. Пересечение двух отрезков
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Необходимо проверить, пересекаются ли два отрезка.

Входные данные
В двух строках входного файла заданы по четыре целых числа, не превосходящих по модулю 10000, — координаты концов первого отрезка, затем второго.

Выходные данные
В первой строке выходного файла выведите «YES», если отрезки имеют общие точки, и «NO» в противном случае.

Пример
входные данные
5 1 2 6
1 1 7 8
выходные данные
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
        int res = this->x * second.y - this->y * second.x;
        if (res > 0)
            return 1;
        else if (res == 0)
            return 0;
        return -1;
    }
};


struct Segment
{
    Point start;
    Point end;


    Segment()
    {}


    Segment(Point start, Point end)
        : start(start)
        , end(end)
    {}


    bool intersect(const Segment& segment) const
    {
        int first_indicator = ((end - start) & (segment.end - start)) * ((end - start) & (segment.start - start));
        int second_indicator = ((segment.end - segment.start) & (end - segment.start)) * 
                                ((segment.end - segment.start) & (start - segment.start));
        if (first_indicator == 1 || second_indicator == 1)
            return false;
        if (first_indicator * second_indicator == 1)
            return true;
        if (first_indicator == -1 && second_indicator == 0)
            return true;
        if (first_indicator == 0 && second_indicator == -1)
            return true;
        if (std::max(start.x, end.x) < std::min(segment.start.x, segment.end.x))
            return false;
        if (std::min(start.x, end.x) > std::max(segment.start.x, segment.end.x))
            return false;
        if (std::max(start.y, end.y) < std::min(segment.start.y, segment.end.y))
            return false;
        if (std::min(start.y, end.y) > std::max(segment.start.y, segment.end.y))
            return false;
        return true;
    }


    friend std::ostream& operator<< (std::ostream& os, const Segment& segment)
    {
        os << "[" << segment.start << ": " << segment.end << "]";
        return os;
    }
};


void read_input(Segment& first_segment, Segment& second_segment)
{
    std::cin >> first_segment.start.x >> first_segment.start.y >> first_segment.end.x >> first_segment.end.y;
    std::cin >> second_segment.start.x >> second_segment.start.y >> second_segment.end.x >> second_segment.end.y;
}


int main()
{
    Segment first;
    Segment second;
    read_input(first, second);
    if (first.intersect(second) == true)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
