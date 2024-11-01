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

int get_combinations_no_repeat(int k, int n)
{
    int nk = get_factorial_of(n + k - 1);
    int n_fact = get_factorial_of(n - 1);
    int k_fact = get_factorial_of(k);

    return nk / (k_fact * n_fact);
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    if ((n < 1 || n > 4) ||
        (k < 1 || k > 4))
        return 0;

    int combinations = get_combinations_no_repeat(k, n);
    std::cout << combinations << std::endl;
    return 0;
}