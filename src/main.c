/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:56:05 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/16 13:35:05 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree(t_vec *expr, t_btree_node *node)
{
	if (node->operator == operator_none)
	{
		for (unsigned int i = node->expr_start; i <= node->expr_end; i++)
		{
			t_token *token = (t_token *)vec_get(expr, i);
			write(1, token->data.data, token->data.size);
			write(1, " ", 1);
		}
		write(1, "{", 1);
		for (unsigned int index = 0; index < node->io_files.size; index++)
		{
			t_io_file *file = (t_io_file *)vec_get(&node->io_files, index);

			t_token		*name = (t_token *)vec_get(expr, file->file_name_token_index);
			write(1, name->data.data, name->data.size);
			if (file->type == io_type_infile)
				write(1, ": infile, ", 11);
			if (file->type == io_type_outfile)
				write(1, ": outfile, ", 12);
			if (file->type == io_type_append_file)
				write(1, ": append, ", 11);
			if (file->type == io_type_heredoc)
				write(1, ": heredoc, ", 12);
		}
		write(1, "} ", 2);
	}
	else
	{
		write(1, "(", 1);
		print_tree(expr, node->left);
		if (node->operator == operator_and)
			write(1, "and ", 4);
		if (node->operator == operator_or)
			write(1, "or ", 3);
		if (node->operator == operator_semicolon)
			write(1, " semicolon ", 12);
		if (node->operator == operator_pipe)
			write(1, " pipe ", 7);
		print_tree(expr, node->right);
		write(1, ")", 1);
		write(1, "{", 1);
		for (unsigned int index = 0; index < node->io_files.size; index++)
		{
			t_io_file *file = (t_io_file *)vec_get(&node->io_files, index);

			t_token		*name = (t_token *)vec_get(expr, file->file_name_token_index);
			write(1, name->data.data, name->data.size);
			if (file->type == io_type_infile)
				write(1, ": infile, ", 11);
			if (file->type == io_type_outfile)
				write(1, ": outfile, ", 12);
			if (file->type == io_type_append_file)
				write(1, ": append, ", 11);
			if (file->type == io_type_heredoc)
				write(1, ": heredoc, ", 12);
		}
		write(1, "} ", 2);
	}
}

void free_tokens(t_vec *expr)
{
	for (unsigned int i = 0; i < expr->size; i++)
	{
		vec_free(&((t_token *)vec_get(expr, i))->data);
	}
	vec_free(expr);
}

bool	main_token(char *line, char *env[])
{
	t_vec parsed;
	t_tokeniser_error result = tokenise(line, &parsed);
	if (result == tokeniser_error_unterminated_quoted_string)
	{
		free_tokens(&parsed);
		display_error_message("Unterminated quoted string.");
		return (false);	
	}

	/*unsigned int i = 0;
	while (i < parsed.size)
	{
		t_token cmd = *(t_token *)vec_get(&parsed, i);
		if (cmd.type == token_type_plain)
			write(1, "Plain:     ", 12);
		else
			write(1, "Delimiter: ", 12);
		write(1, (char *)cmd.data.data, cmd.data.size);
		write(1, "<-\n", 3);
		i++;
	}*/

	t_parsing_checker_result parser_result = check_syntax(&parsed);
	if (parser_result.parsing_error == parsing_error_unmatching_parentheses)
		show_error(&parsed, "Parser Error: Unmatching parenthesis!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_unsupported_arithmetic)
		show_error(&parsed, "Parser Error: Unsupported arithmetic detected!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_empty_parentheses)
		show_error(&parsed, "Parser Error: Empty parentheses!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_incorrect_right_operand)
		show_error(&parsed, "Parser Error: Wrong right operand needed by operator!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_incorrect_left_operand)
		show_error(&parsed, "Parser Error: Wrong left operand needed by operator!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_no_operator_left_parenthese)
		show_error(&parsed, "Parser Error: No operator before parenthese!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_no_operator_right_parenthese)
		show_error(&parsed, "Parser Error: No operator after parenthese!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_invalide_io_file_after_parentheses)
		show_error(&parsed, "Parser Error: Invalid IO file after parenthese!", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_invalide_io_file)
		show_error(&parsed, "Parser Error: Invalid IO file!", parser_result.index1, -1);
	else if (parser_result.parsing_error == parsing_error_unsupported_operator)
		show_error(&parsed, "Parser Error: Unsupported operator!", parser_result.index1, -1);
	if (parser_result.parsing_error != parsing_error_success)
	{
		free_tokens(&parsed);
		return (false);
	}
	
	t_btree_node *root = malloc(2* sizeof(t_btree_node));
	root->expr_start = 0;
	root->expr_end = parsed.size - 1;
	root->cmds = NULL;
	vec_null(&root->io_files);
	if (!parse_token_btree(&parsed, root, 0))
		return (false);

	//print_tree(&parsed, root);
	int files[2] = {0, 1};
	t_btree	*tree;
	tree = malloc(sizeof(t_btree));
	tree->node = root;
	tree->expr = parsed;
	tree->env = env;
	exec_binary_tree(tree, files);

	free_tokens(&parsed);
	return (true);
}

int	main(int argc, char **argv, char *env[])
{
	if (argc == 1)
		handle_prompt(env);
	else if (argc == 2)
		execute_file(argv[1], env);
	else {
		display_error_message("Too many arguments!");
	}
}
