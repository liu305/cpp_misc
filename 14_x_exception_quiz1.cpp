#include <iostream>
#include <cmath>
#include <exception>

class Fraction
{
private:
    int m_numerator;
    int m_denominator;
    bool m_sign;
public:
    Fraction(int numerator, int denominator) :m_numerator(numerator),m_denominator(denominator)
    {
        if (denominator==0){throw std::runtime_error("invalid denominator");}
        m_sign = (numerator/denominator >= 0);
    }
    
    friend std::ostream& operator<< (std::ostream & out, Fraction &f)
    {
        if (f.m_sign)
            out << std::abs(f.m_numerator) << "/" << std::abs(f.m_denominator);
        else
            out << "-" << std::abs(f.m_numerator) << "/" << std::abs(f.m_denominator);
        return out;
    }
    
};

int main()
{
    int numerator;
    int denominator;
    std::cout << "Enter the numerator: ";
    std::cin >> numerator;
    std::cout << "Enter the denominator: ";
    std::cin >> denominator;
    try
    {
        Fraction fraction(numerator,denominator);
        std::cout << fraction << "\n";
    }
    catch (std::exception &exception)
    {
        std::cerr << "Your fraction has an " << exception.what() << ".\n";
    }
    return 0;
}
