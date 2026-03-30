#include "vec.h"
#include "token.h"
#include "libft.h"

unsigned int get_char_pos(t_vec *expr, unsigned int index)
{
    unsigned int char_index = 0;

    while (index - 1)
    {
         t_token *token = vec_get(expr, index);
        char_index += token->data.size + 1;
        index--;
    }
    return (char_index);
}

void show_error(t_vec *expr, char *msg, int index1, int index2)
{
    write(1, "\x1b[31mGhibliShell error: ", 25);
    write(1, msg, ft_strlen(msg));
    write(1, "\x1b[0m\n", 6);
    unsigned int index = 0;
    while (index)
    {
        t_token *token = vec_get(expr, index);
        write(1, token->data.data, token->data.size);
        index++;
        write(1, " ", 1);
    }
}
