#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // For fork(), execvp(), chdir()
#include <sys/types.h>  // For pid_t
#include <sys/wait.h>   // For wait()

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
* (Provided in the problem)
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
        tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
        strcpy(tokens[tokenNo++], token);
        tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;

	// The main shell loop
	while(1) {			
		/* (a) It should have the prompt % */
		printf("%% ");
		fflush(stdout); // Ensure prompt is displayed before reading input

		// Read a line of input from the user
		bzero(line, sizeof(line));
		// Using fgets is safer than scanf for reading a full line
		if (fgets(line, sizeof(line), stdin) == NULL) {
            // Handle Ctrl+D (end of file) to exit gracefully
            printf("\n");
            break;
        }

		// If the user just presses enter, fgets reads a newline.
        // We can check for this and continue.
        if (strcmp(line, "\n") == 0) {
            continue;
        }

		tokens = tokenize(line);
   
        // If tokenization results in no commands (e.g., only spaces), continue
        if (tokens[0] == NULL) {
            free(tokens);
            continue;
        }
       
        /* (b) Implement 'shexit' to exit the shell */
        if (strcmp(tokens[0], "shexit") == 0) {
            // Free memory and break the loop to exit
            for(i=0; tokens[i]!=NULL; i++){
                free(tokens[i]);
            }
            free(tokens);
            break;
        }

        /* (e) Implement the 'cd' command */
        if (strcmp(tokens[0], "cd") == 0) {
            if (tokens[1] == NULL) {
                fprintf(stderr, "shell: expected argument to \"cd\"\n");
            } else {
                // Use the chdir system call to change the directory
                if (chdir(tokens[1]) != 0) {
                    perror("shell"); // Prints an error like "shell: No such file or directory"
                }
            }
        } else {
            /* (c, d, f) For all other commands, use fork() and exec() */
            
            pid_t pid = fork(); // Create a new child process

            if (pid < 0) {
                // Fork failed
                fprintf(stderr, "shell: Fork failed.\n");
            } else if (pid == 0) {
                // This is the child process
                
                // Use execvp to run the command.
                // execvp searches the system's PATH for the executable.
                if (execvp(tokens[0], tokens) == -1) {
                    // If execvp returns, an error occurred.
                    fprintf(stderr, "shell: command not found: %s\n", tokens[0]);
                    exit(EXIT_FAILURE); // Terminate the child process
                }
            } else {
                // This is the parent process
                int status;
                // Wait for the child process to finish execution
                wait(&status);
            }
        }
       
		// Freeing the allocated memory for tokens for the next loop iteration
		for(i=0; tokens[i]!=NULL; i++){
			free(tokens[i]);
		}
		free(tokens);
	}

	return 0;
}