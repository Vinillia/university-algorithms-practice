#include <iostream>
#include <vector>

int fibonacci_last_digit(int value)
{
    static std::vector<int> values({ 0, 1 });

    if (values.size() <= static_cast<size_t>(value))
    {
        int fibonacchi = 0;

        int prior = values[values.size() - 1], prior_prior = values[values.size() - 2];

        for (int i = values.size(); i <= value; i++)
        {
            fibonacchi = (prior + prior_prior) % 10;
            prior_prior = prior;
            prior = fibonacchi;

            values.push_back(fibonacchi);
        }


        return fibonacchi;
    }
    else
    {
        return values.at(value);
    }
}

int main()
{
    int num;
    std::cin >> num;

    //if (num < 1 || num > 45)
      //  return 0;

    std::cout << fibonacci_last_digit(num) << std::endl;
    return 0;
}