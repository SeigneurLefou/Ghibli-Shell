#include "error_manager.h"

unsigned int get_char_pos(t_vec *expr, unsigned int index)
{
    unsigned int char_index = 0;

    while (index--)
    {
        t_token *token = vec_get(expr, index);
        char_index += token->data.size + 1;
    }
    return (char_index);
}

unsigned int underline_error(t_vec *expr, unsigned int token_index, unsigned int current_index, char c)
{
    unsigned int char_index = get_char_pos(expr, token_index) - current_index;
    unsigned int index = char_index;
    while (index--)
        write(1, " ", 1);
    t_token *token = vec_get(expr, token_index);
    index = token->data.size;
    write(1, "\x1b[33m", 6);
    while (index--)
        write(1, &c, 1);
    write(1, "\x1b[0m", 5);
    return (char_index + token->data.size);
}

void display_error_message(char *msg)
{
    write(1, "\x1b[31mGhibliShell error: ", 25);
    write(1, msg, ft_strlen(msg));
    write(1, "\x1b[0m\n", 6);
}

void show_error(t_vec *expr, char *msg, int index1, int index2)
{
    unsigned int index;
    unsigned int offset;

    display_error_message(msg);
    if (index1 >= (int)expr->size)
        index1 = expr->size - 1;
    if (index2 >= (int)expr->size)
        index2 = expr->size - 1;
    index = 0;
    offset = 0;
    while (index < expr->size)
    {
        t_token *token = vec_get(expr, index);
        write(1, token->data.data, token->data.size);
        index++;
        write(1, " ", 1);
    }
    write(1, "\n", 1);
    if (index1 <= index2)
    {
        if (index1 >= 0)
            offset = underline_error(expr, index1, 0, '^');
        if (index2 >= 0 && index1 != index2)
            underline_error(expr, index2, offset, '~');
    }
    else
    {
        if (index2 >= 0)
            offset = underline_error(expr, index2, 0, '~');
        if (index1 >= 0 )
            underline_error(expr, index1, offset, '^');
    }
    write(1, "\n", 1);
}
