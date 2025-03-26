/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:01:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/24 11:25:30 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	filter(char *s, char *x)
{
	int i;
	int len_x;
	int a;
	int len_s;
	int start;

	len_s = strlen(s);
	i = 0;
	len_x = strlen(x);
	a = 0;
	while (i < len_s)
	{
		if (x[a] == s[i])
		{
			start = i;
			while (x[a] == s[i])// bonne sequence ?
			{
				i++;
				a++;
			}
			if (!x[a])// bonne sequence !
			{
				while(a > 0)
				{
					a--;
					// printf("\n s[i] : %c\t", s[i]);
					// printf("\tx[a] : %c\t", x[a]);
					// printf("a : %i\t", a);
					printf("*");
				}
			}
			else
				i = start;
			a = 0;
		}
		
		// printf("\n s[i] : %c\t", s[i]);
		// printf("x[a] : %c\t\t", x[a]);
		// printf("a : %i\t", a);
		printf("%c", s[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		printf(" input : %s\n", av[1]);
		printf("output : ");
		filter(av[1], av[2]);
		printf("\n");
	return (0);
}

// # Tests simples
// ./a.out "bonjour" "jour"
// ./a.out "abc_xyz_abc" "abc"
// ./a.out "coucou" "cou"
// ./a.out "aaaaa" "aaa"
// ./a.out "patate" "patate"

// # Tests avancés
// ./a.out "testtestabc" "abc"
// ./a.out "abcabcabc" "abc"
// ./a.out "abcabcdabc" "abcd"
// ./a.out "ababababa" "aba"

// # Cas particuliers
// ./a.out "aucunrapport" "xyz"
// ./a.out "" "abc"
// ./a.out "abc" ""
// ./a.out "abc" "abcd"

// # Caractères spéciaux
// ./a.out "123#@!abc#@!" "abc"
