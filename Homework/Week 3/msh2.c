#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
/*
 * A very simple shell that supports only commands 'exit', 'help', and 'today'.
 * In addition, displays tokens of the user input.
 */

#define MAX_BUF 160
#define MAX_TOKS 100

int main() {
	int ch;
	char* pos;
	char s[MAX_BUF + 2];   // 2 extra for the newline and ending '\0'
	static const char prompt[] = "msh> ";
	char* toks[MAX_TOKS];

	char* temp = "";
	int helpCmd = 1;
	int todayCmd = 1;
	int exitOut = 1;
	int pid = 1;

	while (1) {
		// prompt for input if input from terminal
		if (isatty(fileno(stdin))) {
			printf(prompt);
		}

		// read input
		char* status = fgets(s, MAX_BUF + 2, stdin);

		// exit if ^d entered
		if (status == NULL) {
			printf("\n");
			break;
		}

		// input is too long if last character is not newline 
		if ((pos = strchr(s, '\n')) == NULL) {
			printf("error: input too long\n");
			// clear the input buffer
			while ((ch = getchar()) != '\n' && ch != EOF);
			continue;
		}

		// remove trailing newline
		*pos = '\0';

		temp = strtok(s, ">");
		helpCmd = strcmp(temp, "help");
		todayCmd = strcmp(temp, "today");
		exitOut = strcmp(temp, "exit");
		pid = strcmp(temp, "ls");
		
		//help
		if (helpCmd == 0) {
			printf("enter 'help', 'today', or 'exit' to quit\n");
			continue;
		}

		//exit
		if (exitOut == 0) {
			break;
		}

		//today
		if (todayCmd == 0) {
			time_t now;
			time(&now);
			struct tm* local = localtime(&now);
			int month, day, year;
			month = local->tm_mon + 1;
			day = local->tm_mday;
			year = local->tm_year + 1900;
			printf("%02d/%02d/%02d\n", month, day, year);
			continue;
		}
	    else {
		
            
            char **args = (char**) calloc(5, sizeof(char*));
            temp  = strtok(s, " \n\t");
            
            int i = 0;
            while(temp != NULL)
            {
                if(temp != "\n"){
                    args[i] = strdup(temp);
                }
                if(i == 5)
                    break;
                i++;
                temp  = strtok(NULL, " \n\t");
            }
            args[i] = NULL;
            
            int rc = fork();
            if (rc < 0) { // fork failed; exit
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else if (rc == 0) {
                int check = execvp(args[0], args);
                if(check < 0)
                    printf("msh: %s: No such file or directory\n", args[0]);
                
                break;
                
            } else {
                int rc_wait = wait(NULL);
            }
		
		}
		
		//printf("msh: %s: %s\n", res[0], strerror(errno));
		
		


	}//end of function
	exit(EXIT_SUCCESS);
}
