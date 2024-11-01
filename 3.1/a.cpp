#include <iostream>

int get_factorial_of(int n)
{
    int result = 1;

    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }

    return result;
}

int main()
{
    int n;
    std::cin >> n;

    if (n < 1 || n > 7)
        return 0;

    int factorial = get_factorial_of(n);
    std::cout << factorial << std::endl;
    return 0;
}