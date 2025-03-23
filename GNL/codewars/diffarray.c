// Your goal in this kata is to implement a difference function, which subtracts one list from another and returns the result.

// It should remove all values from list a, which are present in list b keeping their order.

// array_diff([1, 2], [1]) = [2]
// If a value is present in b, all of its occurrences must be removed from the other:

// array_diff({1, 2, 2, 2, 3}, 5, {2}, 1, *z) == {1, 3} (z == 2)
// NOTE: In C, assign return array length to pointer *z

// 	sinon it2++;
// #include <stdlib.h>

//  return a dynamically allocated array
//  assign the length of this array to *z
//  memory will be freed by the test suite

#include <stdlib.h>
#include <stdio.h>

int *array_diff(const int *arr1, size_t n1, const int *arr2, size_t n2, size_t* n3) 
{
	int	*arr3;
	
	size_t	it1 = 0;
	size_t	it2 = 0;
	size_t	it3 = 0;

	*n3 = n1;

	//size arr3
	while (it1 < n1)
	{
		it2 = 0;
		while (it2 < n2)
		{

			if (arr1[it1] == arr2[it2])
			{
				(*n3)--;
				break ;// si doublons... [YOUPIII]
			}
			it2++;
		}
		it1++;
	}

	arr3 = malloc(sizeof(int) * *n3);
	if (!arr3)
		NULL;

	it1 = 0;
	it3 = 0;
	while (it1 < n1)
	{
		it2 = 0;
		while (it2 < n2)
		{
			if (arr1[it1] == arr2[it2])
				break ;
			it2++;
		}
		
		if (it2 == n2)
		{
			arr3[it3] = arr1[it1];
			it3++;
		}
		it1++;
	}
	return arr3;
}


int main(void)
{
	size_t *z;
	int a[5] = {1, 7, 62, 92, 3};
	int b[4] = {1, 2, 5, 0};

	size_t n3 = 0;
	int *arr3 = array_diff(a, 5, b, 4, &n3);
	size_t it3 = 0;
	printf("n3 : %i\n\n", (int)n3);
	while (it3 < n3)
	{
		printf("%i ", arr3[it3]);
		it3++;
	}

	return 0;
}
