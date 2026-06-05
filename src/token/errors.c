/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:54:25 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 18:01:44 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "token.h"

void	check_result1(t_parsing_check_result parser_result, t_vec *parsed)
{
	if (parser_result.parsing_error == parse_err_unmatching_parentheses)
		show_error(parsed, "Parser Error: Unmatching parenthesis!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_unsupported_arithmetic)
		show_error(parsed, "Parser Error: Unsupported arithmetic detected!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_empty_parentheses)
		show_error(parsed, "Parser Error: Empty parentheses!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_bad_right_operand)
		show_error(parsed,
			"Parser Error: Wrong right operand needed by operator!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_bad_left_operand)
		show_error(parsed,
			"Parser Error: Wrong left operand needed by operator!",
			parser_result.index1, parser_result.index2);
}

void	check_result2(t_parsing_check_result parser_result, t_vec *parsed)
{
	if (parser_result.parsing_error == parse_err_no_operator_left_parenthese)
		show_error(parsed, "Parser Error: No operator before parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error
		== parse_err_no_operator_right_parenthese)
		show_error(parsed, "Parser Error: No operator after parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error
		== parse_err_invalide_io_file_after_parentheses)
		show_error(parsed, "Parser Error: Invalid IO file after parenthese!",
			parser_result.index1, parser_result.index2);
	else if (parser_result.parsing_error == parse_err_invalide_io_file)
		show_error(parsed, "Parser Error: Invalid IO file!",
			parser_result.index1, -1);
	else if (parser_result.parsing_error == parse_err_unsupported_operator)
		show_error(parsed, "Parser Error: Unsupported operator!",
			parser_result.index1, -1);
}
