#ifndef PARSER_H
# define PARSER_H

#include "vec.h"
#include <stdio.h>
#include <unistd.h>

typedef enum e_operator
{
	operator_and,
	operator_or,
	operator_semicolon,
}							t_operator;

typedef struct s_token_btree
{
	t_vec					tokens;
	t_operator				operator;
	struct s_token_btree	*left;
	struct s_token_btree	*right;
}							t_token_btree;

typedef enum e_token_type
{
	token_type_scope_delimiter,
	token_type_command_delimiter,
	token_type_plain,
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

t_tokeniser_error			tokenise(char *expr, t_vec *command);

#endif