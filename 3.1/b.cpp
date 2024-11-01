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

int get_combinations_of(int k, int n)
{
    return get_factorial_of(n) / (get_factorial_of(k) * get_factorial_of(n - k));
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    if ((n < 1 || n > 7) ||
        (k < 1 || k > 7))
        return 0;

    int combinations = get_combinations_of(k, n);
    std::cout << combinations << std::endl;
    return 0;
}