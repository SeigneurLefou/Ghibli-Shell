#include "list.h"
#include "vec.h"

typedef struct s_btree
{
	t_list			*tokens;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

int	main(int argc, char **argv, char **env)
{
	t_vec	vec;

	vec_init(&vec, sizeof(int), 100000);
	int a = 1;
	for (unsigned int i = 0; i < 1000000; i++)
	{
		vec_append(&vec, &a);
	}

	vec_truncate(&vec);

	/*for (unsigned int i = 0; i < 100000000; i++)
	{
		vec_get(&vec, &a);
	}*/

	vec_free(&vec);
}
