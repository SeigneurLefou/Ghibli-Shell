/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:59:39 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 17:31:09 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "vec.h"

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
}			t_tokeniser_error;

#endif
