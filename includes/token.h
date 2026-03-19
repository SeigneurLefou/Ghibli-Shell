#ifndef TOKEN_H
# define TOKEN_H

# include "vec.h"
# include "btree.h"
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
}					t_tokeniser_error;

t_tokeniser_error	tokenise(char *expr, t_vec *command);
bool				parse_token_btree(t_vec *expr, t_btree_node *node);

# endif
