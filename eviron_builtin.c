#include "shell.h"

extern char **environ;
void shell_env() {
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}
