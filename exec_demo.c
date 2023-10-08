#include <stdio.h>
#include <unistd.h>

extern char** environ;
int main() {
    // execl("/bin/ls", "ls", "-l", "/tmp", NULL);
    // execlp("ls", "ls", "-l", "/tmp", NULL);
    char* new_env[] = {"MY_VARIABLE=HELLO", NULL};
    // execle("/bin/env", "env", NULL, new_env);
    // for (char** env = environ; *env != NULL; env++) {
    //     printf("%s\n", *env);
    // }
    char* args[] = {
        "env",
        NULL
    };
    // execv("/bin/ls", args);
    // execvp("ls", args);
    execve("/bin/env", args, new_env);

    perror("exec");
    return 0;
}