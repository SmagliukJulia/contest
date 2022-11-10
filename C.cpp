#include <iostream>
#include <cstdint>
#include <algorithm>

class Fraction final {
private:
    // Do NOT rename
    int64_t numerator;
    uint64_t denominator;

    // Do NOT delete
    template <class T>
    friend bool operator==(const Fraction& lhs, const T& rhs);

public:
    uint64_t gcd(uint64_t a, uint64_t b) const {
        return b == 0 ? a : gcd(b, a % b);
    }

    uint64_t modul(int64_t a) const {
        return a >= 0 ? a : -a;
    }

    void reduce(int64_t &a, uint64_t &b) const {
        uint64_t nod = gcd(modul(a), b);
        a /= static_cast<int64_t>(nod);
        b /= nod;
    }

    Fraction() = delete;
    Fraction(const Fraction& rhs) = default;
    Fraction& operator=(const Fraction& rhs) = default;

    Fraction(int64_t numerator, uint64_t denominator) {
        reduce(numerator, denominator);
        this->numerator = numerator;
        this->denominator = denominator;
    };

    // Your code goes below!
    // Add operators overload here

    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }

    Fraction operator*(const Fraction &rha) const {
        uint64_t lgcd = gcd(modul(numerator), rha.denominator);
        uint64_t rgcd = gcd(modul(rha.numerator), denominator);

        int64_t res_numerator = (numerator / lgcd) * (rha.numerator / rgcd);
        uint64_t res_denominator = (denominator / rgcd) * (rha.denominator / lgcd);

        return Fraction(res_numerator, res_denominator);
    }

    Fraction operator*=(const Fraction &rha) {
        *this = *this * rha;
        return *this;
    }

    Fraction operator+(const Fraction &rha) const {
        // a/b + c/d = (ad + cb) / (bd)
        
        uint64_t bd_gcd = gcd(denominator, rha.denominator);
        uint64_t bd_lcm = (denominator / bd_gcd) * rha.denominator;
        
        int64_t res_numerator = (rha.denominator / bd_gcd) * numerator + (denominator / bd_gcd) * rha.numerator;
        uint64_t res_denominator = bd_lcm;

        reduce(res_numerator, res_denominator);

        return Fraction(res_numerator, res_denominator);
    }

    Fraction operator+=(const Fraction &rha) {
        *this = *this + rha;
        return *this;
    } 

    Fraction operator-(const Fraction &rha) const {
        return *this + (-rha);
    }

    Fraction operator-=(const Fraction &rha) {
        *this = *this - rha;
        return *this;
    } 

    friend void print(Fraction shit) {
        std::cout << shit.numerator << " / " << shit.denominator << std::endl;
    }
};


int main() {
    Fraction a(15,16);
    Fraction b(-7,1337);
    Fraction c(-12, 2);

    print(a);
    std::cout << c.modul(7) << std::endl;
    print(b);
    print(c);

    print(a * b);
    print( a + b );
    a += b;
    print(a);
    print(-c);
        

    return 0;
}
