#include "pipex.h"

// int main() {
//     // Vetor de argumentos para o novo programa
//     char *args[] = {"ls", "-l", "-a", "/home", NULL};


//     // Executa o comando 'ls -l'
//     execvp("ls", args);

//     // Se execvp falhar, o código abaixo será executado
//     perror("execvp");
//     return 1;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(int argc, char *argv[]) {
//     if (argc != 5) {
//         fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
//         return 1;
//     }

//     // Create a pipe
//     int pipefd[2];
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         return 1;
//     }

//     // Create a child process
//     pid_t child_pid = fork();

//     if (child_pid == -1) {
//         perror("fork");
//         return 1;
//     }

//     if (child_pid == 0) {
//         // Child process
//         // Redirect stdout to the write end of the pipe
//         dup2(pipefd[1], STDOU:/usr/local/binT_FILENO);
//         close(pipefd[0]);  // Close the read end of the pipe

//         // Execute cmd1
//         execvp(argv[2], &argv[2]);

//         // If execvp fails
//         perror("execvp");
//         exit(1);
//     } else {
//         // Parent process
//         // Wait for the child process to finish
//         waitpid(child_pid, NULL, 0);

//         // Close the write end of the pipe
//         close(pipefd[1]);

//         // Redirect stdin to the read end of the pipe
//         dup2(pipefd[0], STDIN_FILENO);
//         close(pipefd[0]);  // Close the read end of the pipe

//         // Open file2 for writing
//         FILE *file2 = fopen(argv[4], "w");
//         if (!file2) {
//             perror("fopen");
//             return 1;
//         }

//         // Redirect stdout to file2
//         dup2(fileno(file2), STDOUT_FILENO);

//         // Execute cmd2
//         execvp(argv[3], &argv[3]);

//         // If execvp fails
//         perror("execvp");
//         exit(1);
//     }

//     return 0;
// }


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
    if (execve(path, cmd, envp) == -1)
        perror("execve");
}

int main(int argc, char *argv[], char *envp[]) {
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
}

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
