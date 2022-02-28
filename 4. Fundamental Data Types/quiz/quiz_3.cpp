#include <iostream>

double getDouble()
{
    std::cout << "Enter a double value: ";
    double inp{};
    std::cin >> inp;
    return inp;
}

char getOperator()
{
    std::cout << "Enter one of the following =, -, *, or / : ";
    char op{};
    std::cin >> op;
    return op;
}

void getResult(double x, char op,double y)
{
    double result{};
    switch (op)
    {
        case '+': result = x + y; break;
        case '-': result = x - y; break;
        case '*': result = x * y; break;
        case '/': result = x / y; break;
        default: result = 0;
    }
    std::cout << x << " " << op << " " << y << " is " << result << '\n';
}

int main()
{
    double x{ getDouble() };
    double y{ getDouble() };
    char op{ getOperator() };
    getResult(x, op, y);
}