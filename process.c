#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

Process* Process_new(const int pid, const int ppid, const char cmd[])
{	
	Process* newProc = (Process*) calloc(1, sizeof(Process));
	memcpy(newProc->Cmd, cmd, strlen(cmd)+ 1);
	newProc->Pid = pid;
	newProc->Ppid = ppid;
	newProc->ChildrenCount = 0;
	newProc->Children = NULL;
	return newProc;
}

void Process_AddChild(Process* process, Process* child)
{	
	process->ChildrenCount += 1;
	process->Children = (Process**)realloc(
		process->Children,
		sizeof(Process*) * process->ChildrenCount);
	process->Children[process->ChildrenCount - 1] = child;
}



void Process_Print(Process* process, const int subIndex)
{
	if(!(process))
	{
		return;
	}

	for(int i = 0; i < subIndex; i++)
	{
		printf("\t");
	}

	printf("%d\t", process->Pid);
	//printf("%d\t", process->Ppid);
	printf("%s\n", process->Cmd);

	for(int j = 0; j < process->ChildrenCount; j++)
	{
		Process_Print(process->Children[j], subIndex + 1);
	}
}


Process* CreateProcess(char buffer[])
{
	int maxTokens = 20;
	char* tokens[maxTokens];
	int tokencount = SplitString(buffer, tokens, maxTokens);
	char * pid;
	char * ppid;
	char * cmd;
	char colon[] = ":";
	
	for(int i = 0; i < maxTokens; i++) {		
		if(tokens[i] == NULL) {
			cmd = tokens[i - 1];
			break;
		}		

		if(i == 1) {
			pid = tokens[i];
		}
		else if(i == 2) {
			ppid = tokens[i];		
		}
	}
	return Process_new(atoi(pid), atoi(ppid), cmd);	
}
void BuildTree(Process* processes[], Process* tree[], const int maxsize)
{
	int treeIndex = 0;
	for(int i = 0; i < maxsize; i++)
	{
		tree[i] = NULL;
		Process* proc = processes[i];
		
		int ppid = proc->Ppid;

		if(ppid == 0)
		{
			tree[treeIndex] = proc;
			treeIndex++;	
		}
		else
		{
			for(int j = 0; j < treeIndex; j++)
			{
				FindParent(tree[j], proc);
			}
		}
	}	
}

void FindParent(Process* processToCheck, Process* child)
{
	if(child->Ppid == processToCheck->Pid)
	{
		Process_AddChild(processToCheck, child);
		return;
	}
	
	if(processToCheck->ChildrenCount > 0)
	{
		for(int i = 0; i < processToCheck->ChildrenCount; i++)
		{
			FindParent(processToCheck->Children[i], child);
		}
	}
}




void PrintTree(Process* tree[], const int maxLength)
{
	for(int i = 0; i < maxLength; i++)
	{
		if(tree[i]) 
		{
			Process_Print(tree[i], 0);
		}	
	}
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
