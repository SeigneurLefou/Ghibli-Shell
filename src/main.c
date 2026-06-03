/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:56:05 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/03 16:53:47 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_vec *expr)
{
	for (unsigned int i = 0; i < expr->size; i++)
	{
		vec_free(&((t_token *)vec_get(expr, i))->data);
	}
	vec_free(expr);
}

bool	main_token(char *line, t_minishell *minishell)
{
	t_vec					parsed;
	t_tokeniser_error		result;
	t_parsing_check_result	parser_result;
	t_btree_node			*root;
	int						files[2] = {0, 1};
	t_btree					*tree;
	char					*status;

	result = tokenise(line, &parsed);
	if (result == tokeniser_error_unterminated_quoted_string)
	{
		free_tokens(&parsed);
		display_error_message("Unterminated quoted string.");
		minishell->last_status = 2;
		return (false);
	}
	else if (result == tokeniser_error_memory_error)
	{
		minishell->last_status = 2;
		display_error_message("Memory allocation failed.");
		return (false);
	}
	if (!parsed.size)
	{
		vec_free(&parsed);
		return (true);
	}
	parser_result = check_syntax(&parsed);
	if (parser_result.parsing_error == parse_err_unmatching_parentheses)
		show_error(&parsed, "Parser Error: Unmatching parenthesis!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_unsupported_arithmetic)
		show_error(&parsed, "Parser Error: Unsupported arithmetic detected!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_empty_parentheses)
		show_error(&parsed, "Parser Error: Empty parentheses!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_bad_right_operand)
		show_error(&parsed,
			"Parser Error: Wrong right operand needed by operator!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_bad_left_operand)
		show_error(&parsed,
			"Parser Error: Wrong left operand needed by operator!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_no_operator_left_parenthese)
		show_error(&parsed, "Parser Error: No operator before parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_no_operator_right_parenthese)
		show_error(&parsed, "Parser Error: No operator after parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_invalide_io_file_after_parentheses)
		show_error(&parsed, "Parser Error: Invalid IO file after parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_invalide_io_file)
		show_error(&parsed, "Parser Error: Invalid IO file!",
			parser_result.index1, -1);
	else if (parser_result.parsing_error == parse_err_unsupported_operator)
		show_error(&parsed, "Parser Error: Unsupported operator!",
			parser_result.index1, -1);
	if (parser_result.parsing_error != parse_err_success)
	{
		free_tokens(&parsed);
		minishell->last_status = 2;
		return (false);
	}
	root = mem_alloc(2 * sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	if (!root)
	{
		display_error_message("Memory allocation Failed!");
		free_tokens(&parsed);
		return (false);
	}
	root->expr_start = 0;
	root->expr_end = parsed.size - 1;
	root->cmds = NULL;
	vec_null(&root->io_files);
	if (!parse_token_btree(&parsed, root, 0))
	{
		display_error_message("Memory allocation failed or max recursion limit reached!");
		return (false);
	}
	// print_tree(&parsed, root);
	tree = mem_alloc(sizeof(t_btree), default_error_exit, NULL, 0b1);
	tree->node = root;
	tree->expr = parsed;
	tree->minishell = minishell;
	tree->node->wstatus = 0;
	exec_binary_tree(tree, files);
	tree->minishell->last_status = tree->node->wstatus;
	status = ft_itoa(tree->node->wstatus);
	if (status)
		env_variables_set(&tree->minishell->env_variables_manager, "?", status);
	mem_free(tree);
	mem_free(root);
	free_tokens(&parsed);
	return (true);
}

void	increment_shell_lvl(t_minishell *minishell)
{
	char	*shell_lvl;
	int		shell_lvl_num;

	shell_lvl = env_variables_get(&minishell->env_variables_manager, "SHLVL");
	if (!shell_lvl)
	{
		minishell->shell_level = 1;
		return ;
	}
	shell_lvl_num = ft_atoi(shell_lvl);
	minishell->shell_level = shell_lvl_num + 1;
	shell_lvl = ft_itoa(minishell->shell_level);
	if (!shell_lvl)
		memory_allocation_failed_error_exit();
	if (!env_variables_set(&minishell->env_variables_manager, "SHLVL",
			shell_lvl))
		memory_allocation_failed_error_exit();
	mem_free(shell_lvl);
}

bool	setup_minishell(t_minishell *minishell, char *env[])
{
	env_variables_add_from_env(&minishell->env_variables_manager, env);
	increment_shell_lvl(minishell);
	env_variables_set(&minishell->env_variables_manager, "?", "0");
	if (minishell->shell_level > 100)
	{
		display_error_message("Maximum shell recursion excedded!");
		env_variables_free(&minishell->env_variables_manager);
		return (false);
	}
	load_config_file(minishell, ".ghiblirc");
	load_history_file(minishell, ".ghiblistory");
	return (true);
}

int	main(int argc, char **argv, char *env[])
{
	t_minishell	minishell;

	if (argc > 2)
	{
		display_error_message("Too many arguments!");
		return (1);
	}
	minishell_init(&minishell);
	if (!setup_minishell(&minishell, env))
		return (1);
	if (argc == 1)
		handle_prompt(&minishell);
	else if (argc == 2)
		execute_file(argv[1], &minishell);
	env_variables_free(&minishell.env_variables_manager);
	clear_garbage_collector();
	return (minishell.last_status);
}
