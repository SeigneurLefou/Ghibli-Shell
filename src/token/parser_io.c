/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:51:46 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 18:52:03 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	set_io_delimiters_type(t_token *token, t_io_file *file)
{
	if (token->type == token_type_command_delimiter
		&& token->data.data[0] == '<' && token->data.size == 1)
	{
		file->type = io_type_infile;
		return (true);
	}
	else if (token->type == token_type_command_delimiter
		&& token->data.data[0] == '>' && token->data.size == 1)
	{
		file->type = io_type_outfile;
		return (true);
	}
	else if (token->type == token_type_command_delimiter
		&& token->data.data[1] == '>')
	{
		file->type = io_type_append_file;
		return (true);
	}
	else if (token->type == token_type_command_delimiter
		&& token->data.data[1] == '<')
	{
		file->type = io_type_heredoc;
		return (true);
	}
	return (false);
}

void	grab_io_files(t_vec *expr, t_btree_node *node, unsigned int stop,
		unsigned int index)
{
	t_token		*token;
	t_io_file	file;

	if (!node->io_files.data)
		vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_command_delimiter
			&& token->data.data[0] == '<' && token->data.size == 1)
			file.type = io_type_infile;
		else if (token->type == token_type_command_delimiter
			&& token->data.data[0] == '>' && token->data.size == 1)
			file.type = io_type_outfile;
		else if (token->type == token_type_command_delimiter
			&& token->data.data[1] == '>')
			file.type = io_type_append_file;
		else if (token->type == token_type_command_delimiter
			&& token->data.data[1] == '<')
			file.type = io_type_heredoc;
		index++;
		file.filename_token_i = index;
		vec_append(&node->io_files, &file);
		index++;
	}
}
