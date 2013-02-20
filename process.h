typedef struct {
	int Pid;
	int Ppid;
	char Cmd[250];
	int * Children;
} Process;

Process * Process_new(const int pid, const int ppid, const char cmd[]);

int SplitString(char* str, char* tokens[], const int maxTokens);
