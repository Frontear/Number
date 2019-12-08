#include "number.h"
#include <utility>
#include <iostream>

#define ZERO_PAD(str, len) if (str.length() < len) str = std::string(len - str.length(), '0') + str
#define OPERATION(name) frontear::Number name(const std::string &x, const std::string &y, const long len)
#define OPERATOR(sign, func) frontear::Number frontear::Number::operator sign(const frontear::Number &other) const {\
    auto x = this->value, y = other.value;\
    const auto len = std::max(x.length(), y.length());\
    \
    ZERO_PAD(x, len);\
    ZERO_PAD(y, len);\
    \
    return func(x, y, len);\
}

/*
 * Main issues: todo
 *  - Does not check for string validity
 *  - Performs dangerous std::move operation
 */
frontear::Number::Number(std::string number) : value(std::move(number)) {}

/*
 * Main issues: todo
 *  - Cannot add negative numbers
 *  - Cannot handle decimal values
 */
OPERATION(add) {
    std::string result(len + 1, '0'); // result will never be greater than max length + 1

    auto res = result.rbegin();
    auto carry = 0u;
    for (auto i = len - 1; i >= 0; --i, ++res) {
        auto eval = (x[i] - '0') + (y[i] - '0') + carry;

        carry = 0u;
        if (eval >= 10) {
            eval -= 10;
            carry = 1u;
        }

        *res = eval + '0';
    }

    *res = carry + '0';

    return frontear::Number(result.erase(0,
                                         std::min(result.find_first_not_of('0'),
                                                  result.length() - 1))); // remove trailing 0s
}

OPERATOR(+, add)

/*
 * Main issues: todo
 *  - Cannot subtract negative values
 *  - Cannot handle decimal values
 *  - Cannot handle y being greater than x (only has max - min subtraction)
 *  - Narrow conversions between unsigned and signed ints
 */
OPERATION(sub) {
    std::string result(len, '0'); // result will never be greater than the max length

    auto res = result.rbegin();
    auto borrow = 0u;
    for (auto i = len - 1; i >= 0; --i, ++res) {
        int first = x[i] - '0', second = y[i] - '0';

        if (borrow > 0) {
            first -= borrow;
            borrow = 0u;
        }
        if (second > first) {
            first += 10 * (borrow = 1);
        }

        *res = (first - second) + '0';
    }

    return frontear::Number(result.erase(0,
                                         std::min(result.find_first_not_of('0'),
                                                  result.length() - 1))); // remove trailing 0s
}

OPERATOR(-, sub)

/*
 * Main issues: todo
 *  - Very very inefficient
 *  - Can't handle decimals
 *  - Can't handle negative values
 *  - Can't handle digit differences
 */
OPERATION(mul) {
    std::string result(len * 2, '0');

    auto res = result.rbegin();
    auto carry = 0u;
    for (auto i = len - 1; i >= 0; --i, ++res) {
        for (auto j = len - 1; j >= 0; --j) {
            auto eval = (x[i] - '0') * (y[j] - '0') + carry;

            carry = 0u;
            while (eval >= 10) {
                eval -= 10;
                ++carry;
            }

            *res = eval + '0';
        }
    }

    *res = carry + '0';

    return frontear::Number(result.erase(0, result.find_first_not_of('0')) + std::string(len - 1, '0'));
}

OPERATOR(*, mul)

frontear::Number frontear::Number::operator/(const frontear::Number &other) const {
    return frontear::Number("0");
}

#undef OPERATOR
#undef OPERATION
#undef ZERO_PAD

std::ostream &frontear::operator<<(std::ostream &os, const frontear::Number &number) {
    os << number.value;
    return os;
}
