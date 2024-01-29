#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>  // for fork()
#include <sys/wait.h>  // for wait()

// int main(void)
// {
//     int id = fork();
//     int n;
//     if(id == 0) {
//         n = 1;
//     }else{
//         n = 6;
//     }
//     if(id != 0)
//         wait(NULL);
    
//     int i;
//     printf("Process %d: ", id);
//     for(i = n; i < n + 5; i++)
//     {
//         printf("%d ", i);
//         //fflush(stdout);
//     }
//     if(id != 0)
//         printf("\n");
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

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
//         dup2(pipefd[1], STDOUT_FILENO);
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

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
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

    // Inicializando loop para testar cada caminho
    i = 0;
    while (paths[i])
    {
        // Construindo o caminho completo para o executável
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);

        // Verificando se o executável existe no caminho atual
        if (access(path, F_OK) == 0)
            return (path);

        // Liberando a memória alocada para o caminho atual
        free(path);

        // Indo para o próximo caminho
        i++;
    }

    // Liberando memória alocada para os caminhos
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);

    // Retornando NULL, indicando que o executável não foi encontrado
    return (0);
}

void execute(char *argv, char **envp)
{
    char **cmd;
    int i;
    char *path;

    // Inicializando i com -1
    i = -1;

    // Dividindo a string do comando em partes usando ' ' como delimitador
    cmd = ft_split(argv, ' ');

    // Encontrando o caminho do executável usando a função find_path
    path = find_path(cmd[0], envp);

    // Verificando se o caminho foi encontrado
    if (!path)
    {
        // Liberando a memória alocada para as partes do comando
        while (cmd[++i])
            free(cmd[i]);
        free(cmd);

        // Chamando a função de erro (presumivelmente para lidar com o fato de que o caminho não foi encontrado)
        error();
    }

    // Executando o comando usando execve
    if (execve(path, cmd, envp) == -1)
        error();
}

