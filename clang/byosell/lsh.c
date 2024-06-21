#include <complex.h>
#include <stdio.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

void lsh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf('> ');
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

char *lsh_read_line(void) {
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS); // We recieved an EOF
    } else {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}
