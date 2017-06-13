#include <iostream>
#include <string>

class Fruit{
private:
    std::string m_name;
    std::string m_color;
public:
    Fruit(std::string name, std::string color):
        m_name(name), m_color(color)
    {
    }
    std::string get_name() const {return m_name;}
    std::string get_color() const {return m_color;}
};

class Apple : public Fruit{
private:
    double m_fiber;
public:
    Apple(std::string name, std::string color, double fiber):
        m_fiber(fiber), Fruit(name,color)
    {
    }
    double get_fiber() const {return m_fiber;}
};

class Banana : public Fruit{
public:
    Banana(std::string name, std::string color):
        Fruit(name,color)
    {
    }
};

std::ostream& operator<< (std::ostream &out, const Apple &apple)
{
    out << "Apple(" << apple.get_name() << ", " << apple.get_color() << ", " << apple.get_fiber() << ")\n";
    return out;
}
    
std::ostream& operator<< (std::ostream &out, const Banana &banana)
{
    out << "Banana(" << banana.get_name() << ", " << banana.get_color() << ")\n";
    return out;
}
    
int main()
{
    const Apple a("Red delicious", "red", 4.2);
    std::cout << a;
    
    const Banana b("Cavendish", "yellow");
    std::cout << b;
    
    return 0;
}
