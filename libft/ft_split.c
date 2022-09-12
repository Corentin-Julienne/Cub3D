/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:00:33 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/20 17:25:47 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_free_memory(char **split, size_t w_c)
{
	size_t	size;

	size = 0;
	while (size < w_c)
	{
		free(split[size]);
		size++;
	}
	free(split);
}

static char	*ft_str_alloc(const char *str, size_t len, size_t w_c, char c)
{
	char	*str_w;
	size_t	limit;
	size_t	i;

	i = 0;
	limit = 0;
	if (w_c == 1)
	{
		while (str[i] != c && str[i])
		{
			limit++;
			i++;
		}
		len = limit;
	}
	str_w = malloc(sizeof(char) * (len + 1));
	if (!str_w)
		return (NULL);
	str_w = ft_memcpy(str_w, str, len);
	str_w[len] = '\0';
	return (str_w);
}

static size_t	ft_word_count(const char *str, char c)
{
	size_t		res;
	size_t		i;
	char		*w_str;

	res = 0;
	i = 0;
	w_str = (char *)str;
	if (!w_str[0])
		return (res);
	while (w_str[i])
	{
		if (w_str[i] != c && (w_str[i + 1] == c || w_str[i + 1] == '\0'))
			res++;
		i++;
	}
	return (res);
}

static char	**ft_split_fulfiller(const char *s, char c, size_t w_c, size_t i)
{
	char	**res;
	char	*str;
	size_t	j;

	j = i;
	str = (char *)s;
	res = (char **)malloc(sizeof(char *) * (w_c + 1));
	if (!(res))
		return (NULL);
	while (str[i] && w_c > 1)
	{
		if (str[i] != c)
			i++;
		else if (i > 0)
		{
			res[j++] = ft_str_alloc(str, i, w_c, c);
			str = &str[i];
			i = 0;
		}	
		else
			str++;
	}
	if (w_c > 1 && j < w_c)
		res[j] = ft_str_alloc(str, i, w_c, c);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**split_res;
	char	*str;
	size_t	word_count;
	size_t	size;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	word_count = ft_word_count(str, c);
	size = 0;
	while (str[0] == c && str && c != 0)
		str++;
	split_res = ft_split_fulfiller(str, c, word_count, 0);
	if (!split_res)
		return (NULL);
	if (word_count == 1)
		split_res[0] = ft_str_alloc(str, ft_strlen(str), word_count, c);
	while (size < word_count)
		if (split_res[size++] == NULL)
			ft_free_memory(split_res, word_count);
	if (!split_res)
		return (NULL);
	split_res[word_count] = NULL;
	return (split_res);
}
