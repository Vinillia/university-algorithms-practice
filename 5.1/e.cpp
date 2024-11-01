#include <iostream>
#include <vector>

typedef std::vector<std::vector<long long>> Matrix;

Matrix multiply(const Matrix& a, const Matrix& b, long long mod)
{
    Matrix result(2, std::vector<long long>(2));

    result[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % mod;
    result[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % mod;
    result[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % mod;
    result[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % mod;

    return result;
}

Matrix matrix_pow(Matrix base, long long exp, long long mod)
{
    Matrix result = { {1, 0}, {0, 1} };

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = multiply(result, base, mod);
        }

        base = multiply(base, base, mod);
        exp /= 2;
    }

    return result;
}

int fibonacci_mod_10(long long n)
{
    if (n <= 1) return n;

    Matrix base = { {1, 1}, {1, 0} };
    Matrix result = matrix_pow(base, n, 10);

    return result[0][1];
}

int last_digit_of_fibonacci_partial_sum(long long m, long long n)
{
    int pisano_period = 60;

    int reduced_n = (n + 2) % pisano_period;
    int reduced_m = (m + 1) % pisano_period;

    int last_digit_n_plus_2 = fibonacci_mod_10(reduced_n);
    int last_digit_m_plus_1 = fibonacci_mod_10(reduced_m);

    int result = (last_digit_n_plus_2 - last_digit_m_plus_1 + 10) % 10;
    return result;
}

int main()
{
    long long m, n;
    std::cin >> m >> n;

    int result = last_digit_of_fibonacci_partial_sum(m, n);
    std::cout << result << std::endl;

    return 0;
}
