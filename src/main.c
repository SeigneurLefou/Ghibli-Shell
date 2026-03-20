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
			write(1, "# ", 2);
		print_tree(expr, node->right);
		write(1, ")", 1);
		free(node);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_vec parsed;
	t_tokeniser_error result = tokenise(argv[1], &parsed);
	if (result == tokeniser_error_succes)
		printf("Parser success\n");
	if (result == tokeniser_error_unterminated_quoted_string)
		printf("Parser error: Unterminated quoted string.\n");

	t_parsing_checker_result parentheses_checker_result = check_matching_parentheses(&parsed);
	if (parentheses_checker_result.parsing_error != parsing_error_success)
		printf("Unmatching parenthesis at token %d!\n", parentheses_checker_result.index1);
	else
		printf("Fine !\n");

	t_parsing_checker_result arithmetic_checker_result = check_unsuported_arithmetic(&parsed);
	if (arithmetic_checker_result.parsing_error != parsing_error_success)
		printf("Unsuported arithmetic detected between tokens %d and %d!\n", arithmetic_checker_result.index1, arithmetic_checker_result.index2);
	else
		printf("Fine !\n");
		
	t_parsing_checker_result empty_par_checker_result = check_empty_parentheses(&parsed);
	if (empty_par_checker_result.parsing_error != parsing_error_success)
		printf("Empty parentheses at token %d!\n", empty_par_checker_result.index1);
	else
		printf("Fine !\n");

	t_parsing_checker_result missing_operand_checker_result = check_missing_operand(&parsed);
	if (missing_operand_checker_result.parsing_error == parsing_error_incorrect_right_operand)
		printf("Wrong right operand at token %d needed by operator at token %d!\n", missing_operand_checker_result.index1, missing_operand_checker_result.index2);
	else if (missing_operand_checker_result.parsing_error == parsing_error_incorrect_left_operand)
		printf("Wrong left operand at token %d needed by operator at token %d!\n", missing_operand_checker_result.index1, missing_operand_checker_result.index2);
	else 
		printf("Fine !\n");

	for (unsigned int i = 0; i < parsed.size; i++)
	{
		vec_free(&((t_token *)vec_get(&parsed, i))->data);
	}
	vec_free(&parsed);
	
	return 0;

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
	t_btree_node *root = malloc(sizeof(t_btree_node));
	root->expr_start = 0;
	root->expr_stop = parsed.size - 1;
	if (!parse_token_btree(&parsed, root))
		return 1;

	print_tree(&parsed, root);
	write(1, "\n", 1);
	
	for (unsigned int i = 0; i < parsed.size; i++)
	{
		vec_free(&((t_token *)vec_get(&parsed, i))->data);
	}
	vec_free(&parsed);

}

// 'echo a && (echo b && echo c)'
// '((echo a && echo b) || echo c; echo u) || (echo u && echo b && echo c)'
