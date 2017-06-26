#include <iostream>
#include <string>

template <class T1, class T2>
class Pair
{
protected:
    T1 m_first;
    T2 m_second;
public:
    Pair(T1 first, T2 second): m_first(first), m_second(second)
    {
    }
    T1 first() const {return m_first;}
    T2 second() const {return m_second;}
};

template <class T1>
class StringValuePair : public Pair<std::string,T1>
{
public:
    StringValuePair(std::string tmp_string, T1 tmp_type): Pair<std::string,T1>(tmp_string,tmp_type)
    {
    }
};


int main()
{
    StringValuePair<int> svp("Hello", 5);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    
    return 0;
}
