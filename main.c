#include "pipex.h"

void child_process(char **argv, char **envp, int *fd) {
    int filein = open(argv[1], O_RDONLY, 0777);
    if (filein == -1)
        error();
    dup2(fd[1], STDOUT_FILENO);
    dup2(filein, STDIN_FILENO);
    close(fd[0]);
    execute(argv[2], envp);
}

void parent_process(char **argv, char **envp, int *fd) {
    int fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fileout == -1) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    dup2(fd[0], STDIN_FILENO);
    dup2(fileout, STDOUT_FILENO);
    close(fd[1]);
    execute(argv[3], envp);
}


int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
        ft_printf("\033[31mError: Bad arguments\n\e[0m");
	}
	return (0);
}