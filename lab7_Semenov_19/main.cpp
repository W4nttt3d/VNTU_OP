#include <iostream>
#include <limits>
#include <cmath>

struct COMPLEX {
    double re;
    double im;

    COMPLEX operator+(const COMPLEX& other) const 
    {
        return { re + other.re, im + other.im };
    }

    COMPLEX operator-(const COMPLEX& other) const 
    {
        return { re - other.re, im - other.im };
    }

    COMPLEX operator*(const COMPLEX& other) const 
    {
        return { re * other.re - im * other.im,
                 re * other.im + im * other.re };
    }

    COMPLEX operator/(const COMPLEX& other) const 
    {
        double denom = other.re * other.re + other.im * other.im;
        if (denom == 0.0) 
        {
            std::cerr << "Error: division by zero\n";
            return { 0.0, 0.0 };
        }
        return { (re * other.re + im * other.im) / denom,
                 (im * other.re - re * other.im) / denom };
    }

    COMPLEX operator^(int n) const 
    {
        COMPLEX result{ 1.0, 0.0 };
        COMPLEX base = *this;
        if (n == 0) return result;
        bool negative = false;
        if (n < 0) 
        { 
            negative = true; 
            n = -n; 
        }
        for (int i = 0; i < n; i++)
        {
            result = result * base;
        }
        if (negative)
        {
            result = COMPLEX{ 1.0,0.0 } / result;            
        }
        return result;
    }
};

double inputDouble(const std::string& prompt) 
{
    double val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

void printComplex(const COMPLEX& z) 
{
    std::cout << z.re;
    if (z.im >= 0)
    {
        std::cout << " + " << z.im << "i";
    }
    else
    {
        std::cout << " - " << -z.im << "i";
    }
    std::cout << '\n';
}

int main() 
{
    std::cout << "Enter first complex number:\n";
    COMPLEX a;
    a.re = inputDouble("  Real part: ");
    a.im = inputDouble("  Imaginary part: ");

    std::cout << "Enter second complex number:\n";
    COMPLEX b;
    b.re = inputDouble("  Real part: ");
    b.im = inputDouble("  Imaginary part: ");

    int n;
    std::cout << "Enter integer exponent for first number (a ^ n): ";
    std::cin >> n;

    std::cout << "\nResults:\n";
    std::cout << "a + b = "; printComplex(a + b);
    std::cout << "a - b = "; printComplex(a - b);
    std::cout << "a * b = "; printComplex(a * b);
    std::cout << "a / b = "; printComplex(a / b);
    std::cout << "a ^ " << n << " = "; printComplex(a ^ n);

    return 0;
}
