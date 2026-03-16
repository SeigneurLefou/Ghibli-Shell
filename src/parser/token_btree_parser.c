#include "parser.h"

/* 0 = error */
unsigned int get_matching_parethese(t_vec *expr, unsigned int index,
		unsigned int end)
{
    unsigned int count = 1;

    while (index < end)
    {
        t_token *token = (t_token *)vec_get(expr, index);
        if (token->data.data[0] == '(')
            count++;
        if (token->data.data[0] == '(')
            count--;
        if (count == 0)
            return (index);
    }
    return (0);
}

t_token_btree	*parse_token_btree(t_vec *expr, unsigned int start,
		unsigned int end)
{
    unsigned int index = 0;
    int current_command = 0;

    t_token_btree command_a;
    vec_init(&command_a.tokens, sizeof(t_token), 5);
    t_token_btree command_b;
    vec_init(&command_b.tokens, sizeof(t_token), 5);
    while (index < end)
    {
        t_token *token = (t_token *)vec_get(expr, start + index);
        if (token->type == token_type_scope_delimiter && token->data.data[0])
        {
            unsigned int scope_end = get_matching_parethese(expr, start + index, end);
            if (!scope_end)
                printf("Parsing error!");
            parse_token_btree(expr, start + index + 1, scope_end);
        }
        else
        {
            vec_append(&command_a, token);
        }
        index++;
    }
}
