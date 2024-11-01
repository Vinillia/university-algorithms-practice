#include <iostream>
#include <memory>
#include <functional>
#include <optional>

inline std::vector<int> create_user_array()
{
	int size;
	std::cin >> size;

	std::vector<int> values(size);

	for (int i = 0; i < size; i++)
	{
		std::cin >> values[i];
	}

	return values;
}

void merge_arrays(std::vector<int>& result, std::vector<int>& lhs, std::vector<int>& rhs)
{
	struct indexed_vector
	{
		struct element
		{
			indexed_vector* array;
			std::optional<int> element;
		};

		indexed_vector(std::vector<int>& vec) :  _array(vec), _index(0) {}

		element element_or()
		{
			if (_index >= _array.size())
				return { nullptr, std::nullopt };

			return { this, _array[_index] };
		}

		unsigned int _index;
		const std::vector<int>& _array;
	};

	static auto select_min = [](const indexed_vector::element& lhs, const indexed_vector::element& rhs) -> const indexed_vector::element*
		{
			if (lhs.element && rhs.element)
			{
				return lhs.element.value() < rhs.element.value() ? &lhs : &rhs;
			}
			
			return lhs.element ? &lhs : rhs.element ? &rhs : nullptr;
		};

	indexed_vector index_array[2] =
	{
		{ rhs },
		{ lhs }
	};

	std::vector<int> merge;
	merge.reserve(result.size() + rhs.size() + lhs.size());

	while (true)
	{
		indexed_vector::element rhs_element = index_array[0].element_or();
		indexed_vector::element lhs_element = index_array[1].element_or();

		if (!lhs_element.element && !rhs_element.element)
			break;

		const indexed_vector::element* min = select_min(lhs_element, rhs_element);

		if (!min)
			break;

		min->array->_index++;
		merge.push_back(min->element.value());
	}

	result.clear();
	result = std::move(merge);
}

int main()
{
	int num_arrays;
	std::cin >> num_arrays;

	if (num_arrays < 1 || num_arrays > 20)
		return 0;

	std::unique_ptr<std::vector<int>[]> arrays = std::make_unique<std::vector<int>[]>(num_arrays);

	std::vector<int> result;

	for (int i = 0; i < num_arrays; i++)
	{
		arrays[i] = create_user_array();
		result.reserve(result.capacity() + arrays[i].size());
		merge_arrays(result, result, arrays[i]);
	}

	for (int i : result)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;

	return 0;
}
