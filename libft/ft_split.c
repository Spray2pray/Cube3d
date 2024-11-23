/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:27:25 by mbamatra          #+#    #+#             */
/*   Updated: 2024/01/21 13:01:43 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	free_split_memory(char **split, size_t i)
{
	while (i > 0)
		free(split[--i]);
	free(split);
}

static size_t	ft_len(char const *s, char c)
{
	size_t	word_len;

	if (!ft_strchr(s, c))
		word_len = ft_strlen(s);
	else
		word_len = ft_strchr(s, c) - s;
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_len;
	size_t	i;

	if (!s)
		return (NULL);
	split = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			word_len = ft_len(s, c);
			split[i++] = ft_substr(s, 0, word_len);
			if (!(split[i - 1]))
				return (free_split_memory(split, i), NULL);
			s = s + word_len;
		}
	}
	split[i] = NULL;
	return (split);
}
