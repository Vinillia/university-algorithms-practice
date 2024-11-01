#include <iostream>
#include <vector>
#include <algorithm>

constexpr int pow(int base, int exp)
{
    return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

int median_of_three(std::vector<int>& arr, int low, int high)
{
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    std::swap(arr[mid], arr[high]);

    return arr[high];
}

int lomuto_partition(std::vector<int>& arr, int low, int high)
{
    int pivot = median_of_three(arr, low, high);

    int i = low;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }

    std::swap(arr[i], arr[high]);
    return i;
}

void quick_sort(std::vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pivot_index = lomuto_partition(arr, low, high);

        quick_sort(arr, low, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, high);
    }
}

int main()
{
    int nums;
    std::cin >> nums;

    if (nums < 1 || nums > 100000)
        return 0;

    constexpr int max_value = pow(10, 9);
    std::vector<int> values;
    values.reserve(nums);

    for (int i = 0; i < nums; i++)
    {
        int value;
        std::cin >> value;

        if (value < 1 || value > max_value)
            return 0;

        values.push_back(value);
    }

    quick_sort(values, 0, values.size() - 1);

    for (int value : values)
    {
        std::cout << value << " ";
    }

    std::cout << std::endl;
    return 0;
}
