#include "token.h"

bool	is_a_delimiter(t_token *token, bool match_all)
{
	return (token->type == token_type_scope_delimiter
		&& ((token->data.data[0] == '&' || token->data.data[0] == '|'
			|| token->data.data[0] == ';') || match_all));
}

/* 0 = error */
/* From right to left */
int	get_matching_parethese(t_vec *expr, unsigned int index)
{
	int	count;
	t_token			*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			break ;
		index --;
	}
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count--;
		if (count == 0)
			return (index);
		index--;
	}
	return (0);
}

/* From right to left */
int	get_next_parethese(t_vec *expr, unsigned int index)
{
	int	count;
	t_token			*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			break ;
		index --;
	}
	return (index);
}

/* From right to left */
int	get_next_delimiter(t_vec *expr, unsigned int index)
{
	int	count;
	t_token			*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (is_a_delimiter(token, true))
			break ;
		index --;
	}
	return (index);
}


/* From right to left */
bool	is_in_parentheses(t_vec *expr, unsigned int index, unsigned int end)
{
	int	count;
	t_token			*token;

	token = (t_token *)vec_get(expr, index);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != '(')
		return (false);
	while (end > 0)
	{
		token = (t_token *)vec_get(expr, end);
		if (is_a_delimiter(token, false))
			return (false);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			break ;
		end --;
	}
	token = (t_token *)vec_get(expr, end);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != ')')
		return (false);
	count = 0;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count--;
		if (count <= 0)
			return (false);
		index++;
	}
	return (true);
}

/* From left to right */
bool	contains_scope_delimiter(t_vec *expr, t_btree_node *node, bool match_all)
{
	unsigned int	index;
	t_token			*token;
	int parenthese_count = 0;

	// TODO: Maybe remove the parenthese counter? IDK if it's usefull.
	index = node->expr_start;
	while (index <= node->expr_stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, match_all) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

/* From left to right */
void parse_leaf(t_vec *expr, t_btree_node *node)
{
	t_token			*token;
	t_io_file		file;
	unsigned int index;

	index = node->expr_start;
	if (!node->io_files.size)
		vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < node->expr_stop)
	{
		// This assumes that the syntax is valid and that the types are checked before by the syntax checker
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_command_delimiter && token->data.data[0] == '<')
			file.type = io_type_infile;
		else if (token->type == token_type_command_delimiter && token->data.data[0] == '>')
			file.type = io_type_outfile;
		else if (token->type == token_type_command_delimiter && token->data.data[1] == '>')
			file.type = io_type_append_file;
		else if (token->type == token_type_command_delimiter && token->data.data[1] == '<')
			file.type = io_type_heredoc;
		else
		{
			index++;
			continue;
		}
		index++;
		file.file_name_token_index = index;
		vec_append(&node->io_files, &file);
		index++;
	}
}

void grab_io_files(t_vec *expr, t_btree_node *node, unsigned int stop, unsigned index)
{
	t_token			*token;
	t_io_file		file;

	vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < stop)
	{
		// This assumes that the syntax is valid and that the types are checked before by the syntax checker
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_command_delimiter && token->data.data[0] == '<' && token->data.size == 1)
			file.type = io_type_infile;
		else if (token->type == token_type_command_delimiter && token->data.data[0] == '>' && token->data.size == 1)
			file.type = io_type_outfile;
		else if (token->type == token_type_command_delimiter && token->data.data[1] == '>')
			file.type = io_type_append_file;
		else if (token->type == token_type_command_delimiter && token->data.data[1] == '<')
			file.type = io_type_heredoc;
		index++;
		file.file_name_token_index = index;
		vec_append(&node->io_files, &file);
		index++;
	}
}

// Parsing goal : ./minishell "((echo a && echo b) > out1>out2|| echo c; echo u) < file || (< in echo u && echo b && echo c) << vaaaa"
// (echo b && echo aaa) << in

bool	parse_token_btree(t_vec *expr, t_btree_node *node, unsigned int depth)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	unsigned int	expr_stop;
	t_token			*token;

	vec_null(&node->io_files);
	unsigned int old_stop = node->expr_stop;
	if (is_in_parentheses(expr, node->expr_start, node->expr_stop))
	{
		old_stop = node->expr_stop;
		node->expr_stop = get_next_parethese(expr, node->expr_stop) - 1;
		node->expr_start++;
		grab_io_files(expr, node, old_stop, node->expr_stop + 2);
	}

	if (!contains_scope_delimiter(expr, node, false))
	{
		node->expr_start = node->expr_start;
		node->expr_stop = node->expr_stop;
		node->operator = operator_none;
		node->left = NULL;
		node->right = NULL;
		parse_leaf(expr, node);
		return (true);
	}

	btree_a = malloc(sizeof(t_btree_node));
	btree_b = malloc(sizeof(t_btree_node));
	// TODO: Handle malloc fail
	expr_stop = node->expr_stop;
	btree_a->expr_start = node->expr_start;
	unsigned int next_delimiter = get_next_delimiter(expr, expr_stop);
	token = (t_token *)vec_get(expr, next_delimiter);

	unsigned int operator_index;
	if (token->data.data[0] == ')')
	{
		expr_stop = get_matching_parethese(expr, node->expr_stop);
		if (!expr_stop)
		{
			printf("Something has gone very very wrong.\n");
			// TODO: It leaks here bro
			return (false);
		}
		btree_b->expr_stop = node->expr_stop;
		operator_index = expr_stop - 1;
	}
	else
	{
		token = (t_token *)vec_get(expr, expr_stop);
		while (token && !is_a_delimiter(token, false))
		{
			expr_stop--;
			token = (t_token *)vec_get(expr, expr_stop);
		}
		operator_index = expr_stop;
		btree_b->expr_stop = node->expr_stop;
	}
	btree_a->expr_stop = operator_index - 1;
	btree_b->expr_start = operator_index + 1;
	node->left = btree_a;
	node->right = btree_b;
	if (!parse_token_btree(expr, node->left, depth + 1))
		return (false);
	if (!parse_token_btree(expr, node->right, depth + 1))
		return (false);
	token = (t_token *)vec_get(expr, operator_index);
	if (token->type == token_type_scope_delimiter && token->data.data[0] == '&')
		node->operator = operator_and;
	else if (token->type == token_type_scope_delimiter && token->data.data[0] == '|')
		node->operator = operator_or;
	else if (token->type == token_type_scope_delimiter && token->data.data[0] == ';')
		node->operator = operator_semicolon;
	else if (token->type == token_type_command_delimiter && token->data.data[0] == '|')
		node->operator = operator_pipe;
	return (true);
}
