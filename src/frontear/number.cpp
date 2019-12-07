#include "number.h"
#include <utility>

frontear::Number::Number(std::string number) : value(std::move(number)) {}

frontear::Number add(const std::string &x, const std::string &y, const long len) {
    std::string result(len + 1, '0'); // sum will never be greater than max length + 1

    auto res = result.rbegin();
    auto carry = 0u;
    for (auto i = len - 1; i >= 0; --i, ++res) {
        auto eval = (x[i] - '0') + (y[i] - '0') + carry;

        carry = 0u;
        while (eval >= 10) {
            eval -= 10;
            ++carry;
        }

        *res = eval + '0';
    }

    result = result.erase(0, std::min(result.find_first_not_of('0'), result.length() - 1)); // remove trailing 0s
    return frontear::Number(result);
}

frontear::Number frontear::Number::operator+(const frontear::Number &other) const {
    auto x = this->value, y = other.value;
    const auto len = std::max(x.length(), y.length());

#define ZERO_PAD(str, len) if (str.length() < len) str = std::string(len - str.length(), '0') + str
    ZERO_PAD(x, len);
    ZERO_PAD(y, len);
#undef ZERO_PAD

    return add(x, y, len);
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
