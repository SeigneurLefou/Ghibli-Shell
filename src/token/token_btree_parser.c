#include "token.h"

bool	is_a_delimiter(t_token *token, bool match_all, bool match_pipe)
{
	return (token->type == token_type_scope_delimiter
		&& ((token->data.data[0] == '&' || (!match_pipe
					&& (token->data.data[0] == '|' && token->data.size == 2))
				|| (match_pipe && token->data.data[0] == '|')
				|| token->data.data[0] == ';') || match_all));
}

/* 0 = error */
/* From right to left */
int	get_matching_parenthese(t_vec *expr, unsigned int index)
{
	int		count;
	t_token	*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		index--;
	}
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index--);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			count--;
		if (count == 0)
			return (index + 1);
	}
	return (0);
}

/* From right to left */
int	get_next_parenthese(t_vec *expr, unsigned int index)
{
	t_token	*token;

	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		index--;
	}
	return (index);
}

/* From right to left */
int	get_next_delimiter(t_vec *expr, unsigned int index)
{
	t_token	*token;

	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (is_a_delimiter(token, true, true))
			break ;
		index--;
	}
	return (index);
}

bool	check_closing_parentheses(t_vec *expr, unsigned int end, unsigned int index)
{
	t_token	*token;

	int count = 0;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count--;
		if (count <= 0)
			return (false);
		index++;
	}
	return (true);
}

/* From right to left */
bool	is_in_parentheses(t_vec *expr, unsigned int index, unsigned int end)
{
	t_token	*token;

	token = (t_token *)vec_get(expr, index);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != '(')
		return (false);
	while (end > 0)
	{
		token = (t_token *)vec_get(expr, end);
		if (is_a_delimiter(token, false, true))
			return (false);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		end--;
	}
	token = (t_token *)vec_get(expr, end);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != ')')
		return (false);
	if (!check_closing_parentheses(expr, end, index))
		return (false);
	return (true);
}

/* From left to right */
bool	contains_scope_delimiter(t_vec *expr, t_btree_node *node,
		bool match_all)
{
	unsigned int	index;
	t_token			*token;
	int				parenthese_count;

	parenthese_count = 0;
	// TODO: Maybe remove the parenthese counter? IDK if it's usefull.
	index = node->expr_start;
	while (index <= node->expr_end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, match_all, true) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

bool	contains_non_pipe_delimiter(t_vec *expr, unsigned int start,
		unsigned int stop)
{
	unsigned int	index;
	t_token			*token;
	int				parenthese_count;

	parenthese_count = 0;
	// TODO: Maybe remove the parenthese counter? IDK if it's usefull.
	index = start;
	while (index <= stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, false, false) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

bool set_io_delimiters_type(t_token			*token, t_io_file		*file)
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

/* From left to right */
void	parse_leaf(t_vec *expr, t_btree_node *node)
{
	t_token			*token;
	t_io_file		file;
	unsigned int	index;

	index = node->expr_start;
	if (!node->io_files.data)
		vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < node->expr_end)
	{
		token = (t_token *)vec_get(expr, index);
		if (!set_io_delimiters_type(token, &file))
		{
			index++;
			continue ;
		}
		index++;
		file.filename_token_i = index;
		vec_append(&node->io_files, &file);
		index++;
	}
}

void	grab_io_files(t_vec *expr, t_btree_node *node, unsigned int stop,
		unsigned index)
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

// Parsing goal : ./minishell "((echo a && echo b) > out1>out2|| echo c; echo u) < file || (< in echo u && echo b && echo c) << vaaaa"
// (echo b && echo aaa) << in

void set_leaf(t_vec *expr, t_btree_node *node)
{
	node->expr_start = node->expr_start;
	node->expr_end = node->expr_end;
	node->operator= operator_none;
	node->left = NULL;
	node->right = NULL;
	parse_leaf(expr, node);
}

void enter_parenthese(t_vec *expr, t_btree_node *node)
{
	unsigned int	old_stop;
	
	old_stop = node->expr_end;
	node->expr_end = get_next_parenthese(expr, node->expr_end) - 1;
	node->expr_start++;
	grab_io_files(expr, node, old_stop, node->expr_end + 2);
}

unsigned int capture_scope(t_vec *expr, t_btree_node	*btree_b, t_btree_node *node, unsigned int	expr_end)
{
	t_token			*token;
	unsigned int	operator_index;
	bool			contains_non_pipe;

	token = (t_token *)vec_get(expr, get_next_delimiter(expr, expr_end));
	if (token->data.data[0] == ')')
	{
		expr_end = get_matching_parenthese(expr, node->expr_end);
		btree_b->expr_end = node->expr_end;
		operator_index = expr_end - 1;
	}
	else
	{
		token = (t_token *)vec_get(expr, expr_end);
		contains_non_pipe = contains_non_pipe_delimiter(expr, node->expr_start,
				node->expr_end);
		while (token && (!is_a_delimiter(token, false, !contains_non_pipe)))
		{
			expr_end--;
			token = (t_token *)vec_get(expr, expr_end);
		}
		operator_index = expr_end;
		btree_b->expr_end = node->expr_end;
	}
	return (operator_index);
}

bool	create_children_nodes(t_vec *expr, t_btree_node *node, unsigned int	*operator_index, unsigned int depth)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	unsigned int	expr_end;

	btree_a = mem_alloc(sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	btree_b = mem_alloc(sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	expr_end = node->expr_end;
	btree_a->expr_start = node->expr_start;
	*operator_index = capture_scope(expr, btree_b, node, expr_end);
	btree_a->expr_end = *operator_index - 1;
	btree_b->expr_start = *operator_index + 1;
	vec_null(&btree_a->io_files);
	vec_null(&btree_b->io_files);
	node->left = btree_a;
	node->right = btree_b;
	if (!parse_token_btree(expr, node->left, depth + 1))
		return (false);
	if (!parse_token_btree(expr, node->right, depth + 1))
		return (false);
	return (true);
}

void set_node_operator(t_vec *expr, t_btree_node *node, unsigned int operator_index)
{
	t_token			*token;

	token = (t_token *)vec_get(expr, operator_index);
	if (token->type == token_type_scope_delimiter && token->data.data[0] == '&')
		node->operator= operator_and;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == '|' && token->data.size == 2)
		node->operator= operator_or;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == ';')
		node->operator= operator_semicolon;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == '|')
		node->operator= operator_pipe;
}

bool	parse_token_btree(t_vec *expr, t_btree_node *node, unsigned int depth)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	t_token			*token;
	unsigned int	operator_index;

	if (depth > 1024)
		return (false);
	if (is_in_parentheses(expr, node->expr_start, node->expr_end))
	{
		enter_parenthese(expr, node);
		return (parse_token_btree(expr, node, depth + 1));
	}
	if (!contains_scope_delimiter(expr, node, false))
	{
		set_leaf(expr, node);
		return (true);
	}
	if (!create_children_nodes(expr, node, &operator_index, depth))
		return (false);
	set_node_operator(expr, node, operator_index);
	return (true);
}
