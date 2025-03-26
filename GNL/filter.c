/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:01:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/26 21:01:23 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void  filter(char *s, char *x)
{
	int i = 0;
	int len_x = strlen(x);
	int a = 0;
	int len_s = strlen(s);
	int start;

	while (i < len_s)
	{
		a = 0;
		start = i;
		while (a < len_x && i < len_s && x[a] == s[i])
		{
			i++;
			a++;
		}
		if (a == len_x)
		{
			for (int j = 0; j < len_x; j++)
				printf("*");
			continue; // évite l'affichage double
		}
		else
			i = start; // réinitialise i à start en cas d'échec
		printf("%c", s[i]);
		i++;
	}
}

int   main(int ac, char **av)
{
	  if (ac == 2)
	  {
		char  *buf = malloc(sizeof(char) * 100);

		int bytes_read = read(0, buf, 99);
		buf[bytes_read] = '\0';
		filter(buf, av[1]);
		// filter(av[1], av[2]);
		free(buf);
	  }
	  return (0);
}
