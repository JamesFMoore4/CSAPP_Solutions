#ifndef JOBS_LIST
#define JOBS_LIST
#include "csapp.h"

typedef int jid_t;
typedef enum {RUNNING, STOPPED} job_status;

typedef struct job
{
  pid_t pid;
  jid_t jid;
  job_status stat;
  char* cmdline;
  struct job* next;
} job;

typedef struct
{
  job* head;
  job* tail;
} job_lst;

void jlst_init();
void jlst_del();
void jlst_add(pid_t p, char* cmd, job_status status);
int jlst_rem(pid_t p);
job* jlst_get(jid_t j);
job* jlst_getp(pid_t p);
void jlst_print();
static void jlst_err(char* msg);

#endif


