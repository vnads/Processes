#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

void assertEqualsStr(const char *expected, const char *actual);
void assertEqualsInt(const int expected, const int actual);


/* Uncomment for Process Building Tests */
//int main() 
//{
//	char psOutput[] = "root     15348  8353  0 23:27 pts/0    00:00:00 ps -aef";
//	Process* proc = CreateProcess(psOutput);
//	assertEqualsInt(proc->Pid, 15348);
//	assertEqualsInt(proc->Ppid, 8353);
//	assertEqualsStr(proc->Cmd, "ps");
//}

/* Uncomment for Tree tests */
int main()
{
	//Process_new(const int pid, const int ppid, const char cmd[]);
	Process* proc1 = Process_new(1, 0, "Process1");
	Process* proc2 = Process_new(2, 0, "Process2");
	Process* proc3 = Process_new(3, 1, "Process3");
	Process* proc4 = Process_new(4, 2, "Process4");
	Process* proc5 = Process_new(5, 1, "Process5");
	Process* proc6 = Process_new(6, 3, "Process6");
	
	Process* allProcs[6];

	allProcs[0] = proc1;
	allProcs[1] = proc2;
	allProcs[2] = proc3;
	allProcs[3] = proc4;
	allProcs[4] = proc5;
	allProcs[5] = proc6;

	Process* tree[6];

	BuildTree(allProcs, tree, 6);

	//proc1 should have 2 children	
	assertEqualsInt(tree[0]->ChildrenCount, 2);
	//proc3 should be one of them
	Process* child = tree[0]->Children[0];
	assertEqualsStr(child->Cmd, "Process3");
	//proc5 should be the other
	child = tree[0]->Children[1];
	assertEqualsStr(child->Cmd, "Process5");

	//proc2 should have 1 child
	child = tree[1]->Children[0];
	assertEqualsInt(tree[1]->ChildrenCount, 1);
	//it should be process4
	assertEqualsStr(child->Cmd, "Process4");

	//proc3 should have 1 child
	child = tree[0]->Children[0];
	assertEqualsInt(child ->ChildrenCount, 1);
	//it should be proc6

	child = child->Children[0];
	assertEqualsStr(child->Cmd, "Process6");
}


/* Uncomment for actual program */
//0int main ()
//{	
//	const int BUFFER_MAX = 5000;
//	char buffer[BUFFER_MAX];
//	char * output;
//	Process* processes[500];
//	
//	FILE *stream;
//	stream = popen("ps -aef", "r");
//	int index = 0;
//	if(stream) 
//	{
//		while (fgets(buffer, sizeof(buffer), stream) != NULL)
//		{			
//			processes[index] = CreateProcess(buffer);		
//			index ++;		
//		}
//	}
//	Process* tree[index];
//	BuildTree(processes, tree, index);	
//	PrintTree(tree, index);

//	pclose(stream);
//}

void assertEqualsStr(const char* expected, const char* actual) {
        if(strcmp(expected, actual) != 0) {
                printf("expected <%s> but was <%s>\n", expected, actual);
                exit(1);
        }
}

void assertEqualsInt(const int expected, const int actual) {
        if(expected != actual) {
                printf("expected <%d> but was <%d>\n", expected, actual);
                exit(1);
        }
}


