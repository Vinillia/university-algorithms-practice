#include <iostream>
#include <vector>

template<typename T>
constexpr T pow(T base, T exp)
{
    return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

long long pisano_period(long long m)
{
    long long previous = 0;
    long long current = 1;
    long long period = 0;

    for (long long i = 0; i < m * m; i++) 
    {
        long long temp = (previous + current) % m;
        previous = current;
        current = temp;

        if (previous == 0 && current == 1)
            return i + 1;
    }
    return period;
}

long long fibonacci_mod(long long n, long long m)
{
    long long period = pisano_period(m);
    n = n % period;

    if (n <= 1)
        return n;

    long long previous = 0;
    long long current = 1;

    for (long long i = 2; i <= n; i++)
    {
        long long temp = (previous + current) % m;
        previous = current;
        current = temp;
    }

    return current;
}

int main()
{
    long long num, divisor;
    std::cin >> num >> divisor;

    constexpr long long max_num = pow(10ll, 14ll);
    constexpr long long max_divisor = pow(10ll, 5ll);

    if (num < 1 || num > max_num)
        return 0;

    if (divisor < 2 || divisor > max_divisor)
        return 0;

    std::cout << fibonacci_mod(num, divisor) << std::endl;
    return 0;
}
