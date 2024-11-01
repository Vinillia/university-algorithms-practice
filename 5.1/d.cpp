#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& a, const Matrix& b, long long mod) 
{
    Matrix result(2, vector<long long>(2));

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

long long last_digit_of_fibonacci_sum(long long n)
{
    const int pisano_period = 60;
    long long reduced_index = (n + 2) % pisano_period;

    Matrix base = { {1, 1}, {1, 0} };
    Matrix result = matrix_pow(base, reduced_index, 10);

    long long last_digit = result[0][1];

    return (last_digit - 1 + 10) % 10;
}

int main() 
{
    long long num;
    cin >> num;

    long long result = last_digit_of_fibonacci_sum(num);
    cout << result << endl;

    return 0;
}
