#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int convert_buffer_a_argv (char buffer[2550], char argv[10][255]) {

    char* token;
    token = strtok(buffer, " ");
    int  counter = 0;

    while( token != NULL) {
        strcpy(argv[counter],token);

        token = strtok(NULL, " ");
        counter++;
    }

return counter;

}


void main () {
    // Toma como máximo 9 argumentos de 254 char + el nulo
    // (despues del ultimo argumento el puntero debe ser NULL
    // para indicar el fin de argv)
    char argv[10][255];
    char buffer[2550];
    while (1) {
        printf("RECURSION@MACHINE-972:~$ ");
        gets(buffer);
        int cant_arg = convert_buffer_a_argv(buffer, argv);
        pid_t pid = fork();

        // hijo
        if (pid == 0){
            execv(argv[0], argv);
            printf("hijo: %d\n", getpid());
        }
        else {
            if ( *argv[cant_arg - 1] != '&')
                waitpid(pid, NULL, 0);
        }
    }
    free(argv);
}
