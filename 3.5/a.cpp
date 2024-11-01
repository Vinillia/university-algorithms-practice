#include <iostream>
#include <memory>
#include <functional>

constexpr int pow(int base, int exp) 
{
	return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

void selection_sort(int* numbers, int size)
{
	int index = 0;
	
	std::function<bool()> exchange_lowest_number;

	exchange_lowest_number = [numbers, size, &index, &exchange_lowest_number]() -> bool
		{
			if (index == size - 1)
				return false;

			int* min = &numbers[index];
			
			for (int i = index + 1; i < size; i++)
			{
				if (numbers[i] < *min)
				{
					min = &numbers[i];
				}
			}

			std::swap(numbers[index++], *min);
			return exchange_lowest_number();
		};

	exchange_lowest_number();
}

int main()
{
	int n;
	std::cin >> n;

	if (n < 1 || n > 1000)
		return 0;

	std::unique_ptr<int[]> numbers = std::make_unique<int[]>(n);
	constexpr int max_num = pow(10, 9);

	for (int i = 0; i < n; i++)
	{
		std::cin >> numbers[i];

		if (numbers[i] < 1 || numbers[i] > max_num)
			return 0;
	}

	selection_sort(numbers.get(), n);

	for (int i = 0; i < n; i++)
	{
		std::cout << numbers[i] << " ";
	}

	std::cout << std::endl;
	return 0;
}
