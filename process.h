typedef struct {
	int Pid;
	int Ppid;
	char Cmd[250];
	struct Process** Children;
	int ChildrenCount;
} Process;

Process * Process_new(const int pid, const int ppid, const char cmd[]);

void Process_AddChild(Process* process, Process* child);

void Process_Print(Process* process, const int subIndex);

int SplitString(char* str, char* tokens[], const int maxTokens);

void BuildTree(Process* processes[], Process* tree[], const int maxsize);

void PrintTree(Process* processes[], const int maxLength);

void FindParent(Process* processToCheck, Process* child);

Process* CreateProcess(char buffer[]);
