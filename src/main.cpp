#include <iostream>
#include "frontear/number.h"

using frontear::Number;
using std::cout, std::endl;

int main() {
    Number x("30");
    Number y("40");

    cout << x << " + " << y << " = " << x + y << endl;
    cout << x << " - " << y << " = " << x - y << endl;
    cout << x << " * " << y << " = " << x * y << endl;
    //cout << x << " / " << y << " = " << x / y << endl;

    cout << endl;

    return 0;
}
