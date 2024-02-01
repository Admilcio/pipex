#include "pipex.h"

char *find_path(char *cmd, char **envp)
{
    // Declarando variáveis locais
    char **paths;
    char *path;
    int i;
    char *part_path;

    // Encontrando a linha do PATH no ambiente
    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;

    // Dividindo a linha PATH em partes usando ':' como delimitador
    paths = ft_split(envp[i] + 5, ':');

    i = 0;
    while (paths[i])
    {
        // Construindo o caminho completo para o executável
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);

        if (access(path, F_OK) == 0)
            return (path);

        free(path);
        i++;
    }
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);

    return (0);
}

void execute(char *argv, char **envp)
{
    char **cmd;
    int i;
    char *path;

    i = -1;

    cmd = ft_split(argv, ' ');
    path = find_path(cmd[0], envp);

    if (!path)
    {
        while (cmd[++i])
            free(cmd[i]);
        free(cmd);

        perror("path");
    }
	printf("path: %s\n", path);
    if (execve(path, &cmd, envp) == -1)
        perror("execve");
}

void error() {
    perror("Error");
    exit(EXIT_FAILURE);
}

void child_process(char **argv, char **envp, int *fd) {
    int filein = open(argv[1], O_RDONLY, 0777);
    if (filein == -1)
        error();

    // Redirect stdout to the write end of the pipe
    dup2(fd[1], STDOUT_FILENO);

    // Redirect stdin to the specified input file
    dup2(filein, STDIN_FILENO);

    // Close the read end of the pipe
    close(fd[0]);

    // Execute the specified command with input from the file and output to the pipe
    execute(argv[2], envp);
}


int main(int argc, char *argv[], char *envp[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <command> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create a pipe
    int pipefd[2];
    if (pipe(pipefd) == -1)
        error();

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1)
        error();

    if (child_pid == 0) {
        // In the child process
        // Close the write end of the pipe
        close(pipefd[1]);

        // Execute the child process logic
        child_process(argv, envp, pipefd);

        // If the child process logic fails
        error();
    } else {
        // In the parent process
        // Wait for the child process to finish
        waitpid(child_pid, NULL, 0);

        // Close the read end of the pipe
        close(pipefd[0]);

        // Open the output file for writing
        int fileout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fileout == -1)
            error();

        // Redirect stdout to the output file
        dup2(fileout, STDOUT_FILENO);

        // Close the output file descriptor
        close(fileout);

        // Execute the specified command with input from the pipe and output to the file
        execute(argv[2], envp);

        return EXIT_SUCCESS;
    }
}


/* int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        return 1;
    }

    // Use the first argument as the command and the rest as arguments

    printf("Executing command: %s\n", argv[1]);

    // Call the execute function with command and arguments
    execute(argv[1], envp);

    // If execute function is successful, this line won't be reached
    printf("After execute function (should not reach here)\n");

    return 0;
} */

// int main() {int main() {
//     pid_t child_pid = fork();

//     if (child_pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (child_pid == 0) {
//         // Código executado pelo processo filho

//         printf("Filho: Processo filho executando...\n");
//         sleep(5); // Simula alguma operação demorada
//         printf("Filho: Processo filho concluído.\n");

//         // Não é necessário chamar exit no processo filho, pois execve substitui a imagem do processo
//     } else {
//         // Código executado pelo processo pai

//         printf("Pai: Processo pai esperando pelo filho...\n");
//         waitpid(child_pid, NULL, 0);
//         printf("Pai: Processo pai continuando após o término do filho.\n");
//     }

// 	printf("Processo %d terminando...\n", getpid());

//     return 0;
// }


// int main(int argc, char *argv[], char *envp[]) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     char *cmd = argv[1];
//     char *full_path = find_path(cmd, envp);

//     if (full_path) {
//         printf("Full path for '%s': %s\n", cmd, full_path);
//     } else {
//         printf("'%s' not found in PATH\n", cmd);
//     }
//     free(full_path);
//     return 0;
// }
