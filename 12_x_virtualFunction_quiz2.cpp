#include <iostream>
#include <string>
#include <vector>

class Point
{
private:
    int m_x = 0;
    int m_y = 0;
    int m_z = 0;
    
public:
    Point(int x, int y, int z)
    : m_x(x), m_y(y), m_z(z)
    {
        
    }
    friend std::ostream& operator<<(std::ostream &out, const Point &p)
    {
        out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
        return out;
    }
};

class Shape{
public:
    virtual std::ostream& print(std::ostream & out) = 0;
    friend std::ostream& operator<<(std::ostream &out, Shape &s)
    {
        return s.print(out);
    }
    virtual ~Shape()
    {
    }
};

class Circle : public Shape{
private:
    Point m_a;
    int m_radius;
public:
    Circle(Point a, int radius) :
    m_a(a), m_radius(radius)
    {
    }
    virtual std::ostream& print(std::ostream & out){
        out << "Circle(" << m_a << ", radius " << m_radius <<")";
        return out;
    }
    int getRadius() {return m_radius;}
};

class Triangle : public Shape{
private:
    Point m_a;
    Point m_b;
    Point m_c;
public:
    Triangle(Point a, Point b, Point c) :
        m_a(a), m_b(b), m_c(c)
    {
    }
    virtual std::ostream& print(std::ostream & out){
        out << "Triangle(" << m_a << ", " << m_b << ", " << m_c << ")";
        return out;
    }
};

int getLargestRadius(std::vector<Shape*> &v)
{
    Circle * tmp_ptr=nullptr;
    int max_radius = 0;
    for (int i = 0; i<v.size(); ++i)
    {
        tmp_ptr = dynamic_cast<Circle*>(v[i]);
        if (tmp_ptr && tmp_ptr->getRadius()>max_radius) {max_radius=tmp_ptr->getRadius();}
    }
    return max_radius;
}

int main()
{
    Circle c(Point(1, 2, 3), 7);
    std::cout << c << '\n';
    
    Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
    std::cout << t << '\n';
    
    std::vector<Shape*> v;
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
    v.push_back(new Circle(Point(4, 5, 6), 3));
    
    for (int i=0; i<v.size();++i)
    {
        v[i]->print(std::cout);
        std::cout << "\n";
    }
    
    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function
    
    for (int count = 0; count < v.size(); ++count)
        delete v[count];
    
    return 0;
}
