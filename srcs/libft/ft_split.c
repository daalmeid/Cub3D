/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:45:17 by daalmeid          #+#    #+#             */
/*   Updated: 2021/11/02 18:44:27 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
			i++;
		nb_words++;
	}
	return (nb_words);
}

static int	get_next_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			return (0);
		while (s[i] != c && s[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}

static char	**fill_splits(char **ptr_split, int k, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	while (i < k)
	{
		j = 0;
		ptr_split[i] = malloc(sizeof(char) * (get_next_word(s, c) + 1));
		if (!ptr_split[i])
			return (NULL);
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
			ptr_split[i][j++] = *s++;
		ptr_split[i++][j] = '\0';
	}
	ptr_split[k] = NULL;
	return (ptr_split);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr_split;
	int		k;

	if (s == 0)
		return (NULL);
	k = (word_count(s, c));
	ptr_split = malloc(sizeof(char *) * (k + 1));
	if (!ptr_split)
		return (NULL);
	ptr_split = fill_splits(ptr_split, k, s, c);
	if (!ptr_split)
		return (NULL);
	return (ptr_split);
}
/*
int	main(void)
{
	char	**ptr;
	char	*splitme = ft_strdup("Tripouille");

	ptr = ft_split(splitme, ' ');
	printf("%s\n", ptr[0]);
	printf("%s\n", ptr[1]);
	return (0);
}*/