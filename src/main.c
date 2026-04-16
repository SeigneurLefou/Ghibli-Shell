/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:56:05 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/17 00:52:36 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tree(t_btree_node *node)
{
	if (node->operator == operator_none)
	{
		for (unsigned int index = 0; node->cmds->argv[index]; index++)
			free(node->cmds->argv[index]);
		free(node->cmds->argv);
		free(node->cmds->path);
		free(node->cmds);
		vec_free(&node->io_files);
	}
	else
	{
		free_tree(node->right);
		free_tree(node->left);
	}
	free(node);
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

	int files[2] = {0, 1};
	t_btree	*tree;
	tree = malloc(sizeof(t_btree));
	tree->node = root;
	tree->expr = parsed;
	tree->env = env;
	exec_binary_tree(tree, files);

	free_tree(root);

	free(tree);

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
