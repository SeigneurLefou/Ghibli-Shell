/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:56:05 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 18:11:34 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_vec *expr)
{
	unsigned int	i;

	i = 0;
	while (i < expr->size)
	{
		vec_free(&((t_token *)vec_get(expr, i))->data);
		i++;
	}
	vec_free(expr);
}

bool	create_and_exec_tree(t_vec *parsed, t_btree_node *root,
		t_minishell *minishell, int *files)
{
	t_btree	*tree;
	char	*status;

	root->expr_start = 0;
	root->expr_end = parsed->size - 1;
	root->cmds = NULL;
	vec_null(&root->io_files);
	if (!parse_token_btree(parsed, root, 0))
	{
		display_error_message("Max recursion limit reached!");
		return (false);
	}
	tree = mem_alloc(sizeof(t_btree), default_error_exit, NULL, 0b1);
	tree->node = root;
	tree->expr = *parsed;
	tree->minishell = minishell;
	tree->node->wstatus = 0;
	exec_binary_tree(tree, files);
	tree->minishell->last_status = tree->node->wstatus;
	status = ft_itoa(tree->node->wstatus);
	env_variables_set(&tree->minishell->env_variables_manager, "?", status);
	mem_free(tree);
	return (true);
}

bool	check_syntax_and_exec(t_vec *parsed, t_minishell *minishell)
{
	t_parsing_check_result	parser_result;
	t_btree_node			*root;
	int						files[2];

	files[0] = 0;
	files[1] = 1;
	parser_result = check_syntax(parsed);
	check_result1(parser_result, parsed);
	check_result2(parser_result, parsed);
	if (parser_result.parsing_error != parse_err_success)
	{
		free_tokens(parsed);
		minishell->last_status = 2;
		return (false);
	}
	root = mem_alloc(2 * sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	if (!create_and_exec_tree(parsed, root, minishell, files))
	{
		mem_free(root);
		return (false);
	}
	mem_free(root);
	free_tokens(parsed);
	return (true);
}

bool	main_token(char *line, t_minishell *minishell)
{
	t_vec				parsed;
	t_tokeniser_error	result;

	result = tokenise(line, &parsed);
	if (result == tokeniser_error_unterminated_quoted_string)
	{
		free_tokens(&parsed);
		display_error_message("Unterminated quoted string.");
		minishell->last_status = 2;
		return (false);
	}
	if (!parsed.size)
	{
		vec_free(&parsed);
		return (true);
	}
	if (!check_syntax_and_exec(&parsed, minishell))
		return (false);
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
