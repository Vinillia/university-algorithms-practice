#include <iostream>
#include <vector>

int lomuto_partition(std::vector<int>& arr, int left, int right) 
{
    int pivot = arr[left];  
    int i = left + 1;       

    for (int j = left + 1; j <= right; j++) 
    {
        if (arr[j] < pivot)
        { 
            std::swap(arr[i], arr[j]);  
            i++;
        }
    }

    std::swap(arr[left], arr[i - 1]); 
    return i - 1;
}

int main() 
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) 
    {
        std::cin >> arr[i];
    }

    int pivot_index = lomuto_partition(arr, 0, n - 1);

    for (int num : arr) 
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
    return 0;
}
