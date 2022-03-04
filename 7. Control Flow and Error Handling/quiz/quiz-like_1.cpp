#include <iostream>

int calculate(int x, int y, char o)
{
    switch (o)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '%':
            return x % y;
        default:
            std::cerr << "calculate(): unhandled case\n";
            return 0;
    }
}

int main()
{
    using std::cout, std::cin;

    int x, y;
    char o;
    cout << "Enter an algebraic expression (eg: 3 + 4): ";
    cin >> x; cin >> o; cin >> y;

    int ans { calculate(x, y, o) };
    cout << "The result is " << ans << '\n';
    return 0;
}