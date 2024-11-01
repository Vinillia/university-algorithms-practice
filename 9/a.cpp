#include <iostream>
#include <vector>

using int_pair = std::pair<int, int>;

template<typename T>
constexpr T pow(T base, T exp)
{
    return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

template<typename T>
void apply_for_each_num(const std::vector<int>& values, T&& functor)
{
    int i = 0, j = 0;
    for (int lhs : values)
    {
        for (int rhs : values)
        {
            functor(int_pair(i, j), int_pair(lhs, rhs));

            j++;
        }

        i++;
    }
}

int main()
{
    int n;
    std::cin >> n;

    constexpr int max_values = pow(10, 5);

    if (n < 3 || n > max_values)
        return 0;

    std::vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int value;
        std::cin >> value;
        values.push_back(value);
    }

    int_pair highest(values[0], values[1]);
    int_pair lowest(values[0], values[1]);

    apply_for_each_num(values, [&values, &highest, &lowest](const int_pair& index, const int_pair& value)
        {
            auto handle_pair = [&values]<typename T>(int_pair & current, const int_pair & value, T && comparator)
            {
                if (comparator(value.first - value.second, current.first - current.second))
                {
                    current = value;
                }
                else if (value.first - value.second == current.first - current.second)
                {
                    if (value.first < current.first)
                    {
                        current = value;
                    }
                }
            };

            handle_pair(highest, value, std::greater<>());
            handle_pair(lowest, value, std::less<>());
        });


    std::cout << highest.first << " " << highest.second << std::endl;
    std::cout << lowest.first << " " << lowest.second << std::endl;

    return 0;
}