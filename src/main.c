#include "list.h"
#include "vec.h"
#include <stdio.h>
#include <unistd.h>

typedef struct s_btree
{
	t_list			*tokens;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef enum e_tokeniser_error
{
	tokeniser_error_succes,
	tokeniser_error_unterminated_quoted_string,
} t_tokeniser_error;

t_tokeniser_error tokenise(char *expr, t_vec *command);

int	main(int argc, char **argv, char **env)
{
	t_vec parsed;
	t_tokeniser_error result = tokenise(argv[1], &parsed);
	if (result == tokeniser_error_succes)
		printf("Parser success\n");
	if (result == tokeniser_error_unterminated_quoted_string)
		printf("Parser error: Unterminated quoted string.\n");

	unsigned int i = 0;
	while (i < parsed.size) {
		t_vec cmd = *(t_vec *)vec_get(&parsed, i);
		write(1, (char *)cmd.data, cmd.size);
		write(1, "\n", 1);
		vec_free(&cmd);
		i++;
	}
	vec_free(&parsed);
}

void append_token(t_vec *command, t_vec *token)
{
	t_vec new;

	vec_init(&new, sizeof(char), 16);
	if (token->size)
		vec_append(command, token);
	else
		vec_free(token);
	*token = new;
}

char get_escape(char escaped_char)
{
	if (escaped_char == '\\')
		return ('\\');
	if (escaped_char == '"')
		return ('"');
	if (escaped_char == '\'')
		return ('\'');
	if (escaped_char == ' ')
		return (' ');
	else
		return (0);
}

char is_escape(char escaped_char, char quote)
{
	if (quote == '"')
		return (escaped_char == '\\' || escaped_char == '"');
	else
		return (escaped_char == '\\');
}

t_tokeniser_error tokenise(char *expr, t_vec *command)
{
	vec_init(command, sizeof(t_vec), 4);
	unsigned int i = 0;
	char quote_char = 0;
	bool in_parenthese = false; 
	t_vec current_token;
	vec_init(&current_token, sizeof(char), 16);
	while (expr[i])
	{
		if (quote_char == '"')
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					vec_append(&current_token, &escaped_char);
				}
				else
				{
					vec_append(&current_token, "\\");
					vec_append(&current_token, &expr[i]);
				}
			}
			else if (expr[i] == '"')
				quote_char = 0;
			else
				vec_append(&current_token, &expr[i]);
		}
		else if (quote_char == '\'')
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					vec_append(&current_token, &escaped_char);
				}
				else
				{
					vec_append(&current_token, "\\");
					vec_append(&current_token, &expr[i]);
				}
			}
			else if (expr[i] == '\'')
				quote_char = 0;
			else
				vec_append(&current_token, &expr[i]);
		}
		else
		{
			if (expr[i] == '\\' && expr[i + 1])
				vec_append(&current_token, &expr[++i]);
			else if (expr[i] == '"')
				quote_char = '"';
			else if (expr[i] == '\'')
				quote_char = '\'';
			else if (expr[i] == '(')
			{
				append_token(command, &current_token);
				vec_append(&current_token, &expr[i]);
				append_token(command, &current_token);
			}
			else if (expr[i] == ')')
			{
				append_token(command, &current_token);
				vec_append(&current_token, &expr[i]);
				append_token(command, &current_token);
			}
			else if (expr[i] == ';')
			{
				append_token(command, &current_token);
				vec_append(&current_token, &expr[i]);
				append_token(command, &current_token);
			}
			else if (expr[i] == '|')
			{
				if (expr[i + 1] == '|')
				{
					append_token(command, &current_token);
					i ++;
					vec_append(&current_token, "|");
					vec_append(&current_token, "|");
					append_token(command, &current_token);
				}
				else
					vec_append(&current_token, "|");
			}
			else if (expr[i] == '&')
			{
				if (expr[i + 1] == '&')
				{
					append_token(command, &current_token);
					i ++;
					vec_append(&current_token, "&");
					vec_append(&current_token, "&");
					append_token(command, &current_token);
				}
				else
					vec_append(&current_token, "&");
			}
			else if (expr[i] == '<')
			{
				if (expr[i + 1] == '<')
				{
					append_token(command, &current_token);
					i ++;
					vec_append(&current_token, "<");
					vec_append(&current_token, "<");
					append_token(command, &current_token);
				}
				else
					vec_append(&current_token, "<");
			}
			else if (expr[i] == '>')
			{
				if (expr[i + 1] == '>')
				{
					append_token(command, &current_token);
					i ++;
					vec_append(&current_token, ">");
					vec_append(&current_token, ">");
					append_token(command, &current_token);
				}
				else
					vec_append(&current_token, ">");
			}
			else if (expr[i] == ' ')
			{
				append_token(command, &current_token);
			}
			else
				vec_append(&current_token, &expr[i]);
		}
		i++;
	}
	vec_append(command, &current_token);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
