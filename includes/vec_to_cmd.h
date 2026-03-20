#ifndef VEC_TO_CMD_H
# define VEC_TO_CMD_H

# include "btree.h"

int 	vec_to_cmd(t_btree_node *node, t_vec *expr, char **env);
void	ft_append(char ***dest, const char *src);
void	grab_command(int *i, t_btree_node *node, t_vec *expr, char **env);
size_t	ft_array_strlen(char **array_str);

#endif
