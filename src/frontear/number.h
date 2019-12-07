#ifndef FRONTEAR_NUMBER
#define FRONTEAR_NUMBER

#include <string>
#include <ostream>

namespace frontear {
    class Number {
        std::string value;

    public:
        explicit Number(std::string number);

        Number operator+(const Number &other) const;
        Number operator-(const Number &other) const;
        Number operator*(const Number &other) const;
        Number operator/(const Number &other) const;

        friend std::ostream &operator<<(std::ostream &os, const Number &number);
    };
}

#endif //FRONTEAR_NUMBER
