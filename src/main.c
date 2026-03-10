#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char pwd[255];
	getcwd(pwd, 255);
	printf("%s", pwd);
	char *line = (char *)1;
	while (line > 0)
	{
		line = readline(" > ");
		if (!line)
			break;
		if (!strcmp(line, "exit"))
		{
			free(line);
			break;
		}
		printf("%s", pwd);
		int pid = fork();
		if (pid == 0)
			execve("/bin/bash", (char *[]){"bash", "-c", line, 0}, env);
		else
			wait(NULL);
		free(line);
	}
}
