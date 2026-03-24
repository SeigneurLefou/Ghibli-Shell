#ifndef VEC_TO_CMD_H
# define VEC_TO_CMD_H

# include "btree.h"
# include "files.h"

int 	vec_to_cmd(t_btree_node *node, t_vec *expr, t_file files, char **env);
void	grab_command(t_btree_node *node, t_vec *expr, t_file files, char **env);
void	ft_append(char ***dest, const char *src);
size_t	ft_array_strlen(char **array_str);

#endif
