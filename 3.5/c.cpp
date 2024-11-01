#include <iostream>
#include <memory>
#include <functional>
#include <optional>
#include <vector>

constexpr int pow(int base, int exp)
{
	return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

void merge_arrays(std::vector<int>& result, std::vector<int>& lhs, std::vector<int>& rhs)
{
	int i = 0, j = 0;
	result.clear();
	result.reserve(lhs.size() + rhs.size());

	while (i < lhs.size() && j < rhs.size()) 
	{
		if (lhs[i] <= rhs[j]) 
		{
			result.push_back(lhs[i++]);
		}
		else 
		{
			result.push_back(rhs[j++]);
		}
	}

	while (i < lhs.size()) 
	{
		result.push_back(lhs[i++]);
	}

	while (j < rhs.size()) 
	{
		result.push_back(rhs[j++]);
	}
}

void merge_sort(std::vector<int>& arr, int left, int right) 
{
	if (left >= right) 
		return;

	int mid = left + (right - left) / 2;

	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);

	std::vector<int> left_array(arr.begin() + left, arr.begin() + mid + 1);
	std::vector<int> right_array(arr.begin() + mid + 1, arr.begin() + right + 1);

	std::vector<int> merged;
	merge_arrays(merged, left_array, right_array);

	std::copy(merged.begin(), merged.end(), arr.begin() + left);
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
		int& value = values.emplace_back(0);
		std::cin >> value;

		if (value > max_value)
			return 0;
	}

	merge_sort(values, 0, values.size() - 1);

	for (int value : values)
	{
		std::cout << value << " ";
	}

	std::cout << std::endl;

	return 0;
}
