#ifndef TOKEN_H
# define TOKEN_H

# include "btree.h"
# include "vec.h"
# include <stdio.h>
# include <unistd.h>

typedef enum e_token_type
{
	token_type_scope_delimiter,
	token_type_command_delimiter,
	token_type_plain,
	token_type_void,
}							t_token_type;

typedef struct s_token
{
	t_vec					data;
	t_token_type			type;
}							t_token;

typedef enum e_tokeniser_error
{
	tokeniser_error_succes,
	tokeniser_error_unterminated_quoted_string,
}							t_tokeniser_error;

typedef enum e_parsing_error_type
{
	parsing_error_success,
	parsing_error_unmatching_parentheses,
	parsing_error_incorrect_left_operand,
	parsing_error_incorrect_right_operand,
	parsing_error_empty_parentheses,
	parsing_error_unsuported_arithmetic,
	parsing_error_no_operator_left_parenthese,
	parsing_error_no_operator_right_parenthese,
	parsing_error_invalide_io_file_after_parentheses,
	parsing_error_invalide_io_file,
}							t_parsing_error_type;

typedef struct s_parsing_checker_result
{
	t_parsing_error_type	parsing_error;
	unsigned int			index1;
	unsigned int			index2;
}							t_parsing_checker_result;

t_tokeniser_error			tokenise(char *expr, t_vec *command);
bool						parse_token_btree(t_vec *expr, t_btree_node *node, unsigned int depth);
t_parsing_checker_result    check_syntax(t_vec *expr);

#endif
