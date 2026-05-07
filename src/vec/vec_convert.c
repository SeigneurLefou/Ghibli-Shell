/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:28 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 18:33:47 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

char	*vec_to_cstring(t_vec *vec)
{
	char	*str;

	assert((int[]){vec != NULL, 42}, "Null passed to vec_to_cstring.");
	assert((int[]){vec->type_size == 1, 42}, "The data in vec is larger than a char.");
	assert((int[]){!vec->failed, 42}, "Attempted to read a failed vec.");
	str = malloc((vec->size + 1) * sizeof(char));
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

bool	vec_split(t_vec *vec, char *line, char sep)
{
	int		len;
	t_vec	sub_vec;
	char	*str;

	assert((int[]){!vec->failed, 42}, "Attempted to write to a failed vec.");
	while (line && *line)
	{
		while (*line && *line == sep)
			line++;
		len = word_len(line, sep);
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

	str_array = malloc(sizeof(char *) * (vec->size + 1));
	i = 0;
	while (i < vec->size)
	{
		str_array[i] = vec_to_cstring(vec_get(vec, i));
		if (!str_array[i])
		{
			while (i)
				free(str_array[--i]);
			return (NULL);
		}
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}
