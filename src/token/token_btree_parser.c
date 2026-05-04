#include "token.h"

bool	is_a_delimiter(t_token *token, bool match_all, bool match_pipe)
{
	return (token->type == token_type_scope_delimiter
		&& ((token->data.data[0] == '&' || (!match_pipe && (token->data.data[0] == '|' && token->data.size == 2)) || (match_pipe && token->data.data[0] == '|')
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
	t_token			*token;

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
	t_token			*token;

	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (is_a_delimiter(token, true, false))
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
		if (is_a_delimiter(token, false, false))
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
	while (index <= node->expr_end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, match_all, true) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

bool	contains_non_pipe_delimiter(t_vec *expr, unsigned int start, unsigned int stop)
{
	unsigned int	index;
	t_token			*token;
	int parenthese_count = 0;

	// TODO: Maybe remove the parenthese counter? IDK if it's usefull.
	index = start;
	while (index <= stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, false, false) && !parenthese_count)
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
	if (!node->io_files.data)
		vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < node->expr_end)
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

	if (!node->io_files.data)
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
	unsigned int	expr_end;
	t_token			*token;

	unsigned int old_stop = node->expr_end;
	if (is_in_parentheses(expr, node->expr_start, node->expr_end))
	{
		old_stop = node->expr_end;
		node->expr_end = get_next_parethese(expr, node->expr_end) - 1;
		node->expr_start++;
		grab_io_files(expr, node, old_stop, node->expr_end + 2);
		return (parse_token_btree(expr, node, depth + 1));
	}

	if (!contains_scope_delimiter(expr, node, false))
	{
		node->expr_start = node->expr_start;
		node->expr_end = node->expr_end;
		node->operator = operator_none;
		node->left = NULL;
		node->right = NULL;
		parse_leaf(expr, node);
		return (true);
	}

	btree_a = malloc(sizeof(t_btree_node));
	btree_b = malloc(sizeof(t_btree_node));
	// TODO: Handle malloc fail
	expr_end = node->expr_end;
	btree_a->expr_start = node->expr_start;
	unsigned int next_delimiter = get_next_delimiter(expr, expr_end);
	token = (t_token *)vec_get(expr, next_delimiter);

	unsigned int operator_index;
	if (token->data.data[0] == ')')
	{
		expr_end = get_matching_parethese(expr, node->expr_end);
		if (!expr_end)
		{
			printf("Something has gone very very wrong.\n");
			// TODO: It leaks here bro
			return (false);
		}
		btree_b->expr_end = node->expr_end;
		operator_index = expr_end - 1;
	}
	else
	{
		token = (t_token *)vec_get(expr, expr_end);
		bool contains_non_pipe = contains_non_pipe_delimiter(expr, node->expr_start, node->expr_end);
		while (token && (!is_a_delimiter(token, false, !contains_non_pipe)))
		{
			expr_end--;
			token = (t_token *)vec_get(expr, expr_end);
		}
		operator_index = expr_end;
		btree_b->expr_end = node->expr_end;
	}
	btree_a->expr_end = operator_index - 1;
	btree_b->expr_start = operator_index + 1;
	vec_null(&btree_a->io_files);
	vec_null(&btree_b->io_files);
	node->left = btree_a;
	node->right = btree_b;
	if (!parse_token_btree(expr, node->left, depth + 1))
		return (false);
	if (!parse_token_btree(expr, node->right, depth + 1))
		return (false);
	token = (t_token *)vec_get(expr, operator_index);
	if (token->type == token_type_scope_delimiter && token->data.data[0] == '&')
		node->operator = operator_and;
	else if (token->type == token_type_scope_delimiter && token->data.data[0] == '|' && token->data.size == 2)
		node->operator = operator_or;
	else if (token->type == token_type_scope_delimiter && token->data.data[0] == ';')
		node->operator = operator_semicolon;
	else if (token->type == token_type_scope_delimiter && token->data.data[0] == '|')
		node->operator = operator_pipe;
	return (true);
}
