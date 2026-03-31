/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:56:05 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/31 08:42:09 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree(t_vec *expr, t_btree_node *node)
{
	if (node->operator == operator_none)
	{
		for (int i = node->expr_start; i <= node->expr_stop; i++)
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
		vec_free(&node->io_files);
		free(node);
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
		vec_free(&node->io_files);
		free(node);
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

int	main_token(char *line, char *env[])
{
	t_vec parsed;
	t_tokeniser_error result = tokenise(line, &parsed);
	if (result == tokeniser_error_succes)
		printf("Tokeniser success! Nice!\n");
	if (result == tokeniser_error_unterminated_quoted_string)
	{
		free_tokens(&parsed);
		printf("Tokeniser error: Unterminated quoted string.\n");
		return (1);	
	}

	unsigned int i = 0;
	while (i < parsed.size)
	{
		t_token cmd = *(t_token *)vec_get(&parsed, i);
		if (cmd.type == token_type_plain)
			write(1, "Plain:     ", 12);
		else
			write(1, "Delimiter: ", 12);
		write(1, (char *)cmd.data.data, cmd.data.size);
		write(1, "\n", 1);
		i++;
	}

	t_parsing_checker_result parser_result = check_syntax(&parsed);
	if (parser_result.parsing_error == parsing_error_unmatching_parentheses)
		printf("Parser Error: Unmatching parenthesis at token %d!\n", parser_result.index1);
	else if (parser_result.parsing_error == parsing_error_unsuported_arithmetic)
		printf("Parser Error: Unsuported arithmetic detected between tokens %d and %d!\n", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_empty_parentheses)
		printf("Parser Error: Empty parentheses at token %d!\n", parser_result.index1);
	else if (parser_result.parsing_error == parsing_error_incorrect_right_operand)
		printf("Parser Error: Wrong right operand at token %d needed by operator at token %d!\n", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_incorrect_left_operand)
		printf("Parser Error: Wrong left operand at token %d needed by operator at token %d!\n", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_no_operator_left_parenthese)
		printf("Parser Error: No operator before parenthese at token %d!\n", parser_result.index1);
	else if (parser_result.parsing_error == parsing_error_no_operator_right_parenthese)
		printf("Parser Error: No operator after parenthese at token %d!\n", parser_result.index1);
	else if (parser_result.parsing_error == parsing_error_invalide_io_file_after_parentheses)
		printf("Parser Error: Invalid IO file at %d after parenthese at %d!\n", parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parsing_error_invalide_io_file)
		printf("Parser Error: Invalid IO file at %d!\n", parser_result.index1);
	else
		printf("Parser is happy!\n");
	if (parser_result.parsing_error != parsing_error_success)
	{
		free_tokens(&parsed);
		return (1);
	}
	
	t_btree_node *root = malloc(sizeof(t_btree_node));
	root->expr_start = 0;
	root->expr_stop = parsed.size - 1;
	vec_null(&root->io_files);
	if (!parse_token_btree(&parsed, root, 0))
		return 1;

	print_tree(&parsed, root);
	write(1, "\n", 1);

	vec_to_cmd(root, &expr, env);
	exec_binary_tree(root, env);
	
	free_tokens(&parsed);
}

int	main(int argc, char **argv, char *env[])
{
	(void)argc;
	(void)argv;
	handle_prompt(env);
}
