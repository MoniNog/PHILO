#include <stddef.h>
#include <stdio.h>

int	solve(size_t n, int array[n])
{
	int	i = 0;
	int	j = 1;
	while (i < n)
	{
		j = 0;
		if (array[i] == 0)
		{
			i++;
			j++;
			continue ;
		}

			printf("i : %i , j : %i\n", array[i], array[j]);
		while (j < n)
		{
			if (array[i] + array[j] == 0)
			{
				array[i] = 0;
				array[j] = 0;
				j++;
				break ;
			}
			else
				j++;
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (array[i] != 0)
			return (array[i]);
		else
			i++;
	}
	return 0;
}



// pour chaque element du tableau (while) 
// 	comparer a chaque autre element du tableau (while)
// 		si c'est l'inverse (somme ==0)
// 			supprimer les correspondance du tableau (mettre les deux a zero)
// 			stop boucle=
// pour chaque element du tableau (while) 
// 	si c'est != 0
// 		retourne valeur

int main()
{
	size_t n = 11;
//  const int array[5] = {1, -1, 2, -2, 3};

 int array[11] = {0, 0, -110, 110, -38, -38, -62, 62, -38, -38, -38};

//  const int array[9] = { 0  , 0  , -38, -38,   0,  0, -38, -38, -38};
	printf("result : %i\n", solve(n, array));
	return (0);
}
// /*
// In this Kata, you will be given an array of integers whose elements have both a negative and a positive value, except for one integer that is either only negative or only positive. Your task will be to find that integer.
// Examples:

// [1, -1, 2, -2, 3] => 3

// 3 has no matching negative appearance

// [-3, 1, 2, 3, -1, -4, -2] => -4

// -4 has no matching positive appearance

// [1, -1, 2, -2, 3, 3] => 3

// (the only-positive or only-negative integer may appear more than once)

// Good luck!

// Test(Sample_Tests, should_pass_all_the_tests_provided)
// {
//   { const int array[5] = {1, -1, 2, -2, 3};                             tester(5, array,   3); }
//   { const int array[7] = {-3, 1, 2, 3, -1, -4, -2};                     tester(7, array,  -4); }
//   { const int array[6] = {1, -1, 2, -2, 3, 3};                          tester(6, array,   3); }
//   { const int array[9] = {-110, 110, -38, -38, -62, 62, -38, -38, -38}; tester(9, array, -38); }
//   { const int array[7] = {-9, -105, -9, -9, -9, -9, 105};               tester(7, array,  -9); }
// }
// */
// '
// 1 comprendre la consigne
// 2 penser a une methodologie
// 3 ecrire un pseudocode
// 4 verifier avec un exemple concret si ca peut jouer
// 5 essayer avec des exemples plus specifique
// 	-> identifier le corners cases
// 6 traduire en code 
// 7 tester / debeuguer