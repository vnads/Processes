#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

Process * Process_new(const int pid, const int ppid, const char cmd[])
{	
	Process* newProc = (Process*) calloc(1, sizeof(Process));
	memcpy(newProc->Cmd, cmd, strlen(cmd)+ 1);
	newProc->Pid = pid;
	newProc->Ppid = ppid;
	newProc->Children = NULL;

	return newProc;
}

int SplitString(char* str, char* tokens[], const int maxTokens) {
        int i = 0;
        for(i = 0; i < maxTokens; i++) {
                char* token = strtok(str, " \t\n");
                str = NULL;
                tokens[i] = token;
                if(token == NULL) {
                        break;
                }
        }
        return i;
}