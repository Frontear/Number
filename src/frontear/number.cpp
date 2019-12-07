#include "number.h"

#include <utility>

frontear::Number::Number(std::string number) : value(std::move(number)) {}

frontear::Number frontear::Number::operator+(const frontear::Number &other) const {
    return Number("0");
}

frontear::Number frontear::Number::operator-(const frontear::Number &other) const {
    return Number("0");
}

frontear::Number frontear::Number::operator*(const frontear::Number &other) const {
    return Number("0");
}

frontear::Number frontear::Number::operator/(const frontear::Number &other) const {
    return Number("0");
}

std::ostream &frontear::operator<<(std::ostream &os, const frontear::Number &number) {
    os << number.value;
    return os;
}
