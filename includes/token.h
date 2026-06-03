/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:21:22 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/03 14:17:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "btree.h"
# include "vec.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_btree_node	t_btree_node;

typedef enum e_token_type
{
	token_type_scope_delimiter,
	token_type_command_delimiter,
	token_type_plain,
	token_type_void,
}							t_token_type;

typedef struct s_expand_data
{
	unsigned int			index;
	bool					allow_split;
}							t_expand_data;

typedef struct s_token
{
	t_vec					data;
	t_token_type			type;
	// t_vec<t_expand_data>
	t_vec					expandable_scopes;
	// Basically useless
	bool					is_expand;
	bool					no_skip;
}							t_token;

typedef enum e_tokeniser_error
{
	tokeniser_error_succes,
	tokeniser_error_unterminated_quoted_string,
	tokeniser_error_memory_error,
}							t_tokeniser_error;

typedef enum e_parsing_error_type
{
	parsing_error_success,
	parsing_error_unmatching_parentheses,
	parsing_error_incorrect_left_operand,
	parsing_error_incorrect_right_operand,
	parsing_error_empty_parentheses,
	parsing_error_unsupported_arithmetic,
	parsing_error_no_operator_left_parenthese,
	parsing_error_no_operator_right_parenthese,
	parsing_error_invalide_io_file_after_parentheses,
	parsing_error_invalide_io_file,
	parsing_error_unsupported_operator,
}							t_parsing_error_type;

typedef struct s_parsing_checker_result
{
	t_parsing_error_type	parsing_error;
	int						index1;
	int						index2;
}							t_parsing_checker_result;

t_tokeniser_error			tokenise(char *expr, t_vec *command);
bool						parse_token_btree(t_vec *expr, t_btree_node *node,
								unsigned int depth);
t_parsing_checker_result	check_syntax(t_vec *expr);

char						get_escape(char escaped_char);
char						is_escape(char escaped_char, char quote);
bool						is_valid_expand_char(char c);
bool						is_tilde_escape_compatible(char c);
void						finish_tokeniser(t_token *current_token,
								t_vec *command);
void						setup_token(unsigned int *i, char *quote_char,
								t_token *current_token, t_vec *command);
bool						tokenise_check_quotes(char *expr, unsigned int *i,
								t_token *current_token, char *quote_char);
bool						tokenise_check_expands(char *expr, unsigned int *i,
								t_token *current_token);
bool						tokenise_check_delimiters(char *expr,
								unsigned int *i, t_token *current_token,
								t_vec *command);
void						set_expand(t_token *current_token, bool state,
								bool allow_split);
void						append_token(t_vec *command, t_token *token,
								t_token_type type);
void						push_char(t_token *token, char c);
void						push_simple_char(char *expr, unsigned int *i,
								t_token *current_token);
void						parse_token_double_quote_no_escape(char *expr,
								unsigned int *i, t_token *current_token,
								char *quote_char);
void						parse_token_double_quote(char *expr,
								unsigned int *i, t_token *current_token,
								char *quote_char);
void						parse_token_simple_quote(char *expr,
								unsigned int *i, t_token *current_token,
								char *quote_char);
void						add_simple_token(char *expr, unsigned int i,
								t_vec *command, t_token *current_token);

void						add_double_token(char *expr, unsigned int *i,
								t_vec *command, t_token *current_token);

#endif
