#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char pwd[255];
	getcwd(pwd, 255);
	printf("%s", pwd);
	char *line = (char *)1;
	while (line > 0)
	{
		line = readline(" > ");
		printf("%s", pwd);
		execve("/bin/bash", (char *[]){"bash", "-c", line, 0}, env);
	}
}
