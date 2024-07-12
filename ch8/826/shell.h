#include "csapp.h"
#include "jobs.h"

void eval();
int parseline(char* buf, char** argv);
int builtin_command(char** argv);
void proc_cont(char** argv, int bg);
sigset_t block_signals();
void unblock_signals(sigset_t prev_mask);
void print_if_signaled(int status, pid_t pid);
void stop(int sig);
void intr(int sig);
void reap(int sig);
