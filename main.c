#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"


int main ()
{	
	const int BUFFER_MAX = 5000;
	char buffer[BUFFER_MAX];
	char * output;
	Process* processes[500];
	
	FILE *stream;
	stream = popen("ps -aef", "r");
	int index = 0;
	if(stream) 
	{
		while (fgets(buffer, sizeof(buffer), stream) != NULL)
		{			
			int maxTokens = 20;
			char* tokens[maxTokens];
			int tokencount = SplitString(buffer, tokens, maxTokens);
			char * pid = tokens[1];
			char * ppid = tokens[2];
			char * cmd = tokens[7];
			processes[index] = Process_new(atoi(pid), atoi(ppid), cmd);			
			index ++;		
		}
	}
	Process* tree[index];
	BuildTree(processes, tree, index);
	int rootCount = 0;	
	for(int i = 0; i < index; i++)
	{
		if(tree[i] != NULL)
		{
			rootCount++;
		}
	}
	printf("%d\n", rootCount);	
	PrintTree(tree, rootCount);

	pclose(stream);
}

