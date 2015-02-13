/**************************************************************************
 *
 * File name: simpleShell.c
 *
 * Synopsis: simpleShell
 *
 * Author:
 *      Cameron D G Drennan, Reg no: 201126086
 *      Michael A Duddy,     Reg no: 201240084
 *      Adam Lawton,         Reg no: 201209509
 *      Paul P Hay,          Reg no: 201217918
 *
 * Group 1:
 *      Tue 11-1
 *
 * Promise: I confirm that this submission is all our own work.
 *
 *          (Signed)_____________________________________(Cameron D G Drennan)
 *
 *          (Signed)_____________________________________(Michael A Duddy)
 *
 *          (Signed)_____________________________________(Adam Lawton)
 *
 *          (Signed)_____________________________________(Paul P Hay)
 *
 *
 * Version: See VERSION below
 *
 *********************************************************************/
  
/********************* R E V I S I O N   H I S T O R Y ********************
 * 
 * v1.0 Created the file ace4v1_0.c. I made a simple loop in the main() which 
 *      calls the function getUserInput() until the user enters "exit" or 
 *      "<ctrl>-D" in the shell. getUserInput() reads and parses the user's 
 *      command and I implemented tests to make sure it works. I added in 
 *      line documentation in order to make the code more readable. From now
 *      on we shall comment TESTING TESTING next to test code, so it is 
 *      easy to find & remove later.
 * v2.0 Created the file ace4v2_0.c. I made the execCommand() which
 *		makes runs an appropriate executable file based on the users input. I
 *		made slight changes to previous code and removed duplicate code. I had
 *		to include some files so I can use the likes of the wait() function etc.
 *		I also added in line documentation to the new function. There was an 
 *		issue when trying to run the system program "ls". It would properly when
 *		ls was the first input from the user, but problems occurred when the 
 *		user entered an input with 2 parameters before calling ls. I realised 
 *		this was because we weren't removing everything from the command[] array
 *		each loop. So I created the emptyCommand() function which sets the value
 *		for every position in the command[] array to NULL, hence emptying the array.
 * v3.0 Used getenv() to access the environment then used chdir() to set the
 *		environment to the home evironment on closing of the shell. Added the first
 *		internal command "pwd" to the runCommand() function.  
 * v4.0 Added the getpath and setpath commands and coded their functionality
 * v4.1 Stored path on open, reset to that path at end of main program loop
 * v5.0 Added the cd command with no arguments, setting the path to "HOME"
 * v5.1 Added in other functionality of cd command, including checking if
 *      there are too many arguments and moving to user defined 
 *      directories
 * v6.0 Had to change our tokeniser to a function in order to be able to call it
 *      on our history array
 * v6.1 Added saving of every command entered by the user into an array (history)
 * v6.2 Added "history" command and corresponding functionality
 * v6.3 "!!" command added using historyNum as array position to print
 * v6.4 Noticed warning for origpath usage, changed to pointer
 * v7.0 Added part 7 functionality, saving and loading history from file
 * v7.1 Assorted bug fixes for commands not dealing with the number of arguments
 *      correctly
 * v7.3 Bug fixes and added further documentation for multiple methods
 * v7.4 Added error messaging for the likes of when the history invocation is
 *		out of range. Fixed bug when calling a history invocation of "exit"
 *		it now exits program appropriately. 
 **************************************************************************/
#define VERSION "simpleShell V7.4  by Group 1. Last Update 14/04/2014\n"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "~> "
#define CONTINUE 0
#define EXIT 1
#define PARAMETERS 50

char *command[PARAMETERS];

char history[20][512];

int historyNum;

int tokeniser(char *userInput) {
  char *tokenizer = " <>|\n\t\0";
  char *token;
  int i = 1;
  
  /*Tokenize first userInput and put it in command array at position 0*/
  command[0] = malloc(sizeof(command[0])); /*malloc is needed to make array both read and write*/
  command[0] = strtok(userInput, tokenizer);
  
  /*If user hit Enter/If nothing was tokenized, loop round again*/
  if(command[0] == NULL) {
    return CONTINUE;
  }
  
  /*If the first command was exit then terminate program*/
  if(strcmp(command[0], "exit") == 0) {
    return EXIT;
  }
 
  /*Loop while there is a command to be tokenized*/
  while ((token = strtok(NULL, tokenizer)) != NULL) {
    command[i] = malloc(sizeof(command[i])); /*malloc is needed to make array both read and write*/
    strcpy(command[i], token); /*Copy token string into command array at position i*/
	if (i > PARAMETERS) { /*If there are more than 50 tokens, stop and continue with program*/
	  printf("*Problem; Too many tokens*\n");
      return CONTINUE;
	}
    i++; /*Increment i*/
  }
  return CONTINUE;
}

void prevHistory(int index) {
  char temp[512];
  if(index >= 0 && index <= 19){ 
	/*Deals with empty position being selected*/
	if(strcmp(history[index], "") == 0){ 
	  printf("*History position is empty*");
	}
	/*Re-create and run the command at the given position*/
	else {
      strcpy(temp, history[index]); 
   	  index = 1;
	  while(command[index] != NULL) {
		sprintf(temp, "%s", temp); 
		strcat(temp, command[index]); 
		index++;
	  }
 	  if(tokeniser(temp) == CONTINUE) {
		runCommand();
	  }
	  else if (tokeniser(temp) == EXIT){
	    exit(EXIT_SUCCESS);
	  }
	  else {
	    printf("*ERROR*\n");
	  }
	}
  }
  else {
    printf("*History invocation out of range*\n");
  }
}

void invokeHistory() {
  if(strcmp(command[0], "!!") == 0){
	prevHistory(historyNum-1);	/*Invoke most recent command in history*/
  }
  else {
	/*Invoke command at specified position in history*/
	char *position = strtok(command[0], "!"); 
	char temp[sizeof(position)/sizeof(position[0])]; 
	int index = atoi(position); 
	sprintf(temp, "%i", index); 
	if(strcmp(temp, position) == 0) {
	  prevHistory(index-1);
	}
  }
}

/*Adds user input to the History array*/
void addToHistory(char userInput[512]) {
  int i=0;
  if(historyNum < sizeof(history)/sizeof(history[0])) {
    strcpy(history[historyNum], userInput);
	historyNum++;
  }
  else {
    while(i < sizeof(history)/sizeof(history[0])) {
	  strcpy(history[i], history[i+1]);
	  i++;
	}
	strcpy(history[sizeof(history)/sizeof(history[0])-1], userInput);
  }
}

/*Prints the History array*/
void printHistory() {
  int i;
  for(i = 0; i < historyNum; i++) {
    printf("%i. %s\n", i+1, history[i]);
  }
}

/*Set directory to the Home directory*/
void setEnvironment() { 
  chdir(getenv("HOME"));
}

void emptyCommand() {
  int i;
  for(i=0; command[i] != NULL; i++) { /*Iterates through command[] array*/
      command[i] = NULL; /*If the contents of the array are not empty...make them empty*/
  }
}

void execCommand() {
  /*this is the process ID. It is of type pid_t so the program is portable across platforms*/
  pid_t processID;
  /*fork() function is used to create a child process*/   
  processID = fork();
  /*if processID is the parent process, we need to wait for child process to terminate*/
  if(processID > 0) { 
    wait(NULL); 
  } 
  /*processID must be the child process*/
  /*if command is not recognised, print error*/
  /*message and kill child process*/
  else if(execvp(command[0], command) == -1) { 
    printf("*Problem: No such file or program*\n");
	kill(getpid(), SIGKILL);
  }
}

int getUserInput() {
  /*Variables*/
  char userInput[512];
  char *newline;
  
  
  /*Print PROMPT "~> "*/
  printf(PROMPT);
  
  /*Get the command from user, and end of file check ie ,<Ctrl>-D*/
  if((fgets(userInput, 512, stdin)) == NULL) {
	return EXIT;
  }

  if (userInput[0] == '\n') {
    return CONTINUE;
  }
  
  /*This is so when we hit enter its not treated as a token*/ 
  /*Replaces new line character with terminating character*/
  if ((newline = strchr(userInput, '\n')) != NULL) {
    *newline = '\0';
  }
  
  if(userInput[0] != '!') {
 	addToHistory(userInput);
  }
		
  if((tokeniser(userInput)) == EXIT) {
    return EXIT;
  }	
  runCommand();

  return CONTINUE;
}

void loadHistory(){
  FILE *file;
  char character[512];
  char *string;
  int i = 0;
  /*Create file if it does not already exist*/
  if((file = fopen(".hist_list", "r")) == NULL){ 
    printf("Created history file in home\n");
  } 
  /*Loads command history from file*/
  else {
    while(1) {
      if((fgets(character, 512, file)) == NULL){
        break;
      }
      if ((string = strchr(character, '\n')) != NULL) {
        *string = '\0';
       addToHistory(character);
        i++;
      }
	}
  }
  fclose(file);
} 
  
/*Saves the current History array to file*/
void saveHistory(){
  int i = 0;
  FILE *file;
  file = fopen(".hist_list", "w+");
  while(strcmp(history[i], "") != 0){
    fprintf(file, "%s\n", history[i]);
    i++;
  } 
  fclose(file);
}

int runCommand() {
  /*pwd command*/
  if(strcmp(command[0], "pwd") == 0) {
    if ((command[1]) != NULL) {
      printf("*Problem; Too many tokens*\n");
    }
    else {
	  char cdir[100];
      printf("%s\n", getcwd(cdir, 100));
    }
  }
  /*getpath command*/
  else if(strcmp(command[0], "getpath") == 0) {
    if ((command[1]) != NULL) {
      printf("*Problem; Too many tokens*\n");
    }
    else {
      printf("%s\n",getenv("PATH"));
      return 1;
    }
  }
  /*setpath command*/
  else if(strcmp(command[0], "setpath") == 0) {
	if (command[1] == NULL) {
		printf("*Problem; Too few tokens*\n");
	}
	else if (command[2] != NULL) {
		printf("*Problem; Too many tokens*\n");
	}
    setenv("PATH", command[1], 1);
    return 1;
  }
  /*cd command*/
  else if(strcmp(command[0], "cd") == 0) {
    if(command[1] == NULL) {
       setEnvironment();
       return 1;
    }
    else if (command[2] != NULL) {
       printf("*Problem; Too many tokens*\n");
       return 1;
    }
    else {
       if (chdir(command[1]) != 0) {
          perror("*Problem; Invalid directory");   
       }
       return 1;
    }
  }
  /*history command*/
  else if(strcmp(command[0], "history") == 0) {
	if (command[1] != NULL) {
		printf("*Problem; Too many tokens*\n");
	}
	else {
		printHistory();
	}
  }
  /* !! command*/
  else if(command[0][0] == '!') { 
	if (command[2] != NULL) {
		printf("*Problem; Too many tokens*\n");
	}
	else {	
		invokeHistory();
	}
  }
  
  else {
    execCommand(); /*Run external command using user's input*/
  }
  
  return CONTINUE;
}

int main() {
  char origPath;
  char *getcwd(char *origPath, size_t size);  /*get the path on opening of shell*/
  int exitLoop = 0;
  int loopCondition;
  setEnvironment();
  historyNum = 0;
  loadHistory();
  while(exitLoop == 0) { /*Main loop*/
    emptyCommand(); /*Need to empty command array each loop*/
    loopCondition = getUserInput();
	if(loopCondition == EXIT) { /*Exit condition*/
	  exitLoop = 1;
	}
  }
  saveHistory();
  setenv("PATH", &origPath, 1);  /*set PATH back to what it was on open*/
  return(0);
}
