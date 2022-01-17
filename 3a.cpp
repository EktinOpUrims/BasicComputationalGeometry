/*
C. Точка в многоугольнике
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Входные данные
В первой строке содержится три числа —– N (3⩽N⩽100000) и координаты точки. Последующие N строк содержат координаты вершин многоугольника. Координаты — целые, не превосходят 10^6 по модулю.

Выходные данные
Одна строка YES, если заданная точка содержится в приведённом многоугольнике или на его границе, и NO в противном случае.

Пример
входные данные
3 2 3
1 1
10 2
2 8
выходные данные
YES
*/


#include <iostream>


struct Point
{
    int x;
    int y;
    const int INF = 1000001;


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


    int operator& (const Point& other) const
    {
        long long res = ((long long) this->x) * ((long long) other.y) - ((long long) this->y) * ((long long) other.x);
        if (res > 0)
            return 1;
        else if (res == 0)
            return 0;
        return -1;
    }


    Point& operator= (const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
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
        os << "[" << segment.start << " : " << segment.end << "]";
        return os;
    }


    bool segment_contains(const Point& point, const char* option) const
    // option is either "interior" or "closure"
    // check if the segment contains the point
    {
        if (((end - start) & (point - start)) != 0)
            return false;
        if (option == "interior")
        {   if (std::min(end.y, start.y) < point.y && std::max(end.y, start.y) > point.y)
                return true;
            if (std::min(end.x, start.x) < point.x && std::max(end.x, start.x) > point.x)
                return true;
            return false;
        }
        else if (option == "closure")
        {   if (std::min(end.y, start.y) > point.y || std::max(end.y, start.y) < point.y)
                return false;
            if (std::min(end.x, start.x) > point.x && std::max(end.x, start.x) < point.x)
                return false;
            return true;
        }
        else
        {
            std::cout << "No such option";
            return false;
        }
    }


    bool intersect_ray(const Point& point) const
    {   
        Point point_inf = Point(point.INF, point.y);
        int first_indicator = (Point(1, 0) & (start - point)) * (Point(1, 0) & (end - point));
        int second_indicator = ((end - start) & (point - start)) * ((end - start) & (point_inf - start));
        if (first_indicator == 1 || second_indicator == 1)
            return false;
        if (first_indicator * second_indicator == 1)
            return true;
        
        // now the case that the point lies in the interior of the segment
        if ((this->segment_contains)(point, "interior") == true)
            return true;
        
        // now remaines the case, that at least one of the ends of the segment lies on the ray
        if (std::max(end.y, start.y) > point.y)
            return true;
        return false;
    }
};


struct Polygon
{
    int size = 0;
    int capacity = 0;
    Point* arr;


    void set_capacity(int capacity)
    {
        if (this->capacity != 0)
        {
            std::cout << "Misusage of set_capacity" << capacity;
            return;
        }
        this->capacity = capacity;
        arr = new Point[capacity];
    }


    ~Polygon()
    {
        if (capacity > 0)
            delete[] arr;
    }

    
    void add_point(const Point& point)
    {
        if (size >= capacity)
        {
            std::cout << "\nArray out of range\n";
            return;
        }
        arr[size++] = point;
    }


    friend std::ostream& operator<< (std::ostream& os, const Polygon& polygon)
    {
        os << "[";
        for (int index = 0; index < polygon.size; ++index)
        {
            os << polygon.arr[index];
            if (index != polygon.size - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }


    bool is_point_inside(const Point& point) const
    {
        int intersections_cnt = 0;
        int next_vertex;
        for (int index = 0; index < size; ++index)
        {
            next_vertex = index + 1;
            if (index == size - 1)
            {
                next_vertex = 0;
            }
            if (Segment(arr[index], arr[next_vertex]).segment_contains(point, "closure"))
                return true;
            intersections_cnt += Segment(arr[index], arr[next_vertex]).intersect_ray(point);
        }
        return intersections_cnt % 2;
    }
};


void read_input(Point& point, Polygon& polygon)
{
    int capacity;
    std::cin >> capacity;
    polygon.set_capacity(capacity);
    std::cin >> point.x >> point.y;  
    int x;
    int y;
    for (int index = 0; index < capacity; ++index)
    {
        std::cin >> x >> y;
        polygon.add_point(Point(x, y));
    }
}


int main()
{
    Polygon polygon;
    Point point;
    read_input(point, polygon);

    if (polygon.is_point_inside(point))
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}