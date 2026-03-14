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

typedef enum e_token_type
{
	token_type_scope_delimiter,
	token_type_plain,
} t_token_type;

typedef struct s_token
{
	t_vec data;
	t_token_type type;
} t_token;

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
		t_token cmd = *(t_token *)vec_get(&parsed, i);
		if (cmd.type == token_type_plain)
			write(1, "Plain:     ", 12);
		else
			write(1, "Delimiter: ", 12);
		write(1, (char *)cmd.data.data, cmd.data.size);
		write(1, "\n", 1);
		vec_free(&cmd.data);
		i++;
	}
	vec_free(&parsed);
}

void append_token(t_vec *command, t_token *token, t_token_type type)
{
	t_token new;

	vec_init(&new.data, sizeof(char), 16);
	token->type = type;
	if (token->data.size)
		vec_append(command, token);
	else
		vec_free(&token->data);
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
	vec_init(command, sizeof(t_token), 4);
	unsigned int i = 0;
	char quote_char = 0;
	bool in_parenthese = false; 
	t_token current_token;
	vec_init(&current_token.data, sizeof(char), 16);
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
					vec_append(&current_token.data, &escaped_char);
				}
				else
				{
					vec_append(&current_token.data, "\\");
					vec_append(&current_token.data, &expr[i]);
				}
			}
			else if (expr[i] == '"')
				quote_char = 0;
			else
				vec_append(&current_token.data, &expr[i]);
		}
		else if (quote_char == '\'')
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					vec_append(&current_token.data, &escaped_char);
				}
				else
				{
					vec_append(&current_token.data, "\\");
					vec_append(&current_token.data, &expr[i]);
				}
			}
			else if (expr[i] == '\'')
				quote_char = 0;
			else
				vec_append(&current_token.data, &expr[i]);
		}
		else
		{
			if (expr[i] == '\\' && expr[i + 1])
				vec_append(&current_token.data, &expr[++i]);
			else if (expr[i] == '"')
				quote_char = '"';
			else if (expr[i] == '\'')
				quote_char = '\'';
			else if (expr[i] == '(')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ')')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ';')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == '|')
			{
				if (expr[i + 1] == '|')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "|");
					vec_append(&current_token.data, "|");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
					vec_append(&current_token.data, "|");
			}
			else if (expr[i] == '&')
			{
				if (expr[i + 1] == '&')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "&");
					vec_append(&current_token.data, "&");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
					vec_append(&current_token.data, "&");
			}
			else if (expr[i] == '<')
			{
				if (expr[i + 1] == '<')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "<");
					vec_append(&current_token.data, "<");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
					vec_append(&current_token.data, "<");
			}
			else if (expr[i] == '>')
			{
				if (expr[i + 1] == '>')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, ">");
					vec_append(&current_token.data, ">");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
					vec_append(&current_token.data, ">");
			}
			else if (expr[i] == ' ')
			{
				append_token(command, &current_token, token_type_plain);
			}
			else
				vec_append(&current_token.data, &expr[i]);
		}
		i++;
	}
	current_token.type = token_type_plain;
	vec_append(command, &current_token);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
