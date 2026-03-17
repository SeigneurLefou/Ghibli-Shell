#ifndef PARSER_H
# define PARSER_H

# include "btree.h"
# include "vec.h"
# include <stdio.h>
# include <unistd.h>

typedef enum e_tokeniser_error
{
	tokeniser_error_succes,
	tokeniser_error_unterminated_quoted_string,
}					t_tokeniser_error;

t_tokeniser_error	tokenise(char *expr, t_vec *command);
void				parse_token_btree(t_vec *expr, t_token_btree_node *node);

#endif