/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/03 14:21:15 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	add_double_token(char *expr, unsigned int *i, t_vec *command,
		t_token *current_token)
{
	t_token_type	token_type;

	if (expr[*i] == '>' || expr[*i] == '<')
		token_type = token_type_command_delimiter;
	else
		token_type = token_type_scope_delimiter;
	set_expand(current_token, false, false);
	if (expr[(*i) + 1] == expr[*i])
	{
		append_token(command, current_token, token_type_plain);
		(*i)++;
		push_char(current_token, expr[*i]);
		push_char(current_token, expr[*i]);
		append_token(command, current_token, token_type);
	}
	else
	{
		append_token(command, current_token, token_type_plain);
		push_char(current_token, expr[*i]);
		append_token(command, current_token, token_type);
	}
}

void	add_simple_token(char *expr, unsigned int i, t_vec *command,
		t_token *current_token)
{
	set_expand(current_token, false, false);
	append_token(command, current_token, token_type_plain);
	push_char(current_token, expr[i]);
	append_token(command, current_token, token_type_scope_delimiter);
}

t_tokeniser_error	tokenise(char *expr, t_vec *command)
{
	unsigned int	i;
	char			quote_char;
	t_token			current_token;

	setup_token(&i, &quote_char, &current_token, command);
	while (expr[i])
	{
		if (quote_char == '"')
			parse_token_double_quote(expr, &i, &current_token, &quote_char);
		else if (quote_char == '\'')
			parse_token_simple_quote(expr, &i, &current_token, &quote_char);
		else
		{
			if (!(tokenise_check_quotes(expr, &i, &current_token, &quote_char)
					|| tokenise_check_expands(expr, &i, &current_token)
					|| tokenise_check_delimiters(expr, &i, &current_token,
						command)))
				push_simple_char(expr, &i, &current_token);
		}
		i++;
	}
	finish_tokeniser(&current_token, command);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
