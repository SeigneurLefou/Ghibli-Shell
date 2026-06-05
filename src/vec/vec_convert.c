/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:28 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 18:30:14 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exits.h"
#include "vec.h"

char	*vec_to_cstring(t_vec *vec)
{
	char	*str;

	str = mem_alloc((vec->size + 1) * sizeof(char), default_error_exit, NULL,
			0b1);
	if (!str)
		return (NULL);
	if (vec->data)
		ft_memcpy(str, vec->data, vec->size * sizeof(char));
	str[vec->size] = 0;
	return (str);
}

void	str_to_vec_char(t_vec *vec, char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		vec_append(vec, &line[i]);
		i++;
	}
}

static size_t	word_len_space(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !ft_isspace(s[len]))
		len++;
	return (len);
}

bool	vec_split_space(t_vec *vec, char *line)
{
	int		len;
	t_vec	sub_vec;
	char	*str;

	while (line && *line)
	{
		while (*line && ft_isspace(*line))
			line++;
		len = word_len_space(line);
		if (!*line)
			return (true);
		vec_init(&sub_vec, sizeof(char), len);
		str = ft_substr(line, 0, len);
		str_to_vec_char(&sub_vec, str);
		if (sub_vec.failed)
		{
			vec_free(&sub_vec);
			return (false);
		}
		vec_append(vec, &sub_vec);
		line += len;
	}
	return (true);
}

char	**vec_vec_char_to_str_array(t_vec *vec)
{
	char	**str_array;
	size_t	i;

	str_array = mem_alloc(sizeof(char *) * (vec->size + 1), default_error_exit,
			NULL, 0b1);
	if (!str_array)
		return (NULL);
	i = 0;
	while (i < vec->size)
	{
		str_array[i] = vec_to_cstring(vec_get(vec, i));
		if (!str_array[i])
		{
			while (i)
				mem_free(str_array[--i]);
			return (NULL);
		}
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}
