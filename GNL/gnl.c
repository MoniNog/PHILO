#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// define	BUFFER_SIZE = 12;

/// @brief malloc a new char* with begin + end ; free begin (still need "end" because is buffer)
/// @param begin first part of the final part, [mod] free
/// @param end last part of the final part
/// @return final = concatenation start + end
char	*append(char *begin, char *end)
{
	int i = strlen(begin);
	int j = strlen(end);
	char *total;

	if (!begin || !end)
		return NULL;
	total = malloc(sizeof(char) * (i + j + 1));
	if (!total)
		return NULL;
	j = 0;
	i = 0;
	while(begin[i])
	{
		total[i] = begin[i];
		i++;
	}
	while(end[j])
	{
		total[i] = end[j];
		j++;
		i++;
	}
	total[i] = '\0';

	if(begin[0])
		free(begin);
	return (total);
}

/// @brief check if there is a \n in a string 
/// @param s string to check
/// @return 1 = there is a \n | 0 = there is NOT a \n
int has_newline(char *s)
{
	int i = 0;

	while(s[i])
	{
		if (s[i] == '\n')
			return 1;
		i++;
	}
	return 0;
}

/// @brief return a line that has been read from the file descriptor passed as parameter
/// @param fd file descriptor passed as param
/// @return line read
char	  *get_next_line(int fd)
{
	char	*buffer;
	char	*begin;
	int		size_buf;
	char	*total;

	size_buf = 4;

	buffer = malloc(sizeof(char) * size_buf);
	begin = malloc(sizeof(char) * size_buf);
	if (!buffer || !begin)
		return NULL;
		
	read(fd, begin, size_buf);
	while((has_newline(begin)) != 1) 
	{
		read(fd, buffer, size_buf);
		begin = append(begin, buffer); // 123 456 123456
		
		sleep(1);
	}
	if (buffer)
		free(buffer);
	return (begin);
}

int main(int ac, char **av)
{
	int		fd;
	
	fd = open(av[1], O_RDONLY);
	printf("%s\n\n", get_next_line(fd));
	printf("%s\n\n", get_next_line(fd));
	return(0);
}

		// je me rappelle plus l'explication de pourquoi il est illogique de mettre un free 
		// dans la boucle while.
		// je sais que je dois free le buffer au fur et a mesure que je l'utilise
		// mais comment ?
		// malloc et free doivent etre fait de la meme facon, hors boucle par exemple
		// 		malloc total
		// begin = append(begin, buffer, total); // 123 456 123456
		// free