#include "jobs.h"

job_lst* jlst;
static int jlst_cntr = 1;

void jlst_init()
{
  jlst = (job_lst*)malloc(sizeof(job_lst));
  if (!jlst)
    jlst_err("Could not allocate job list.\n");
  jlst->head = jlst->tail = NULL;
}

void jlst_del()
{
  job* ptr = jlst->head;
  while (ptr)
  {
    job* temp = ptr;
    ptr = ptr->next;
    free(temp->cmdline);
    free(temp);
  }
  free(jlst);
}

void jlst_add(pid_t p, char* cmd, job_status status)
{
  job* jb = (job*)malloc(sizeof(job));
  if (!jb)
    jlst_err("Could not add job.\n");
  jb->pid = p;
  jb->jid = jlst_cntr;
  jb->stat = status;
  jb->cmdline = (char*)malloc(strlen(cmd) + 1);
  if (!jb->cmdline)
    jlst_err("String allocation error.\n");
  strcpy(jb->cmdline, cmd);
  jb->next = NULL;

  if (!jlst->head)
    jlst->head = jlst->tail = jb;
  else
    jlst->tail = jlst->tail->next = jb;
  
  jlst_cntr++;
}

int jlst_rem(pid_t p)
{
  if (!jlst->head)
    return 0;

  if (jlst->head == jlst->tail)
  {
    if (jlst->head->pid == p)
    {
      job* temp = jlst->head;
      jlst->head = jlst->tail = NULL;
      free(temp->cmdline);
      free(temp);
      return 1;
    }
    return 0;
  }

  if (jlst->head->pid == p)
  {
    job* temp = jlst->head;
    jlst->head = temp->next;
    free(temp->cmdline);
    free(temp);
    return 1;
  }

  job* ptr;
  for (ptr = jlst->head; ptr->next; ptr = ptr->next)
  {
    if (ptr->next->pid == p)
    {
      job* temp = ptr->next;
      ptr->next = temp->next;
      free(temp->cmdline);
      free(temp);
      return 1;
    }
  }

  return 0;
}

job* jlst_get(jid_t j)
{
  job* jb;
  for (jb = jlst->head; jb; jb = jb->next)
    if (jb->jid == j)
      return jb;
  return NULL;
}

job* jlst_getp(pid_t p)
{
 job* jb;
  for (jb = jlst->head; jb; jb = jb->next)
    if (jb->pid == p)
      return jb;
  return NULL;
} 

void jlst_print()
{
  job* jb;
  for (jb = jlst->head; jb; jb = jb->next)
  {
    char* str_stat = jb->stat == RUNNING ? "Running" : "Stopped";
    printf("[%d] %d %s   %s\n", jb->jid, jb->pid, str_stat, jb->cmdline);
  }
}

static void jlst_err(char* msg)
{
  fprintf(stderr, "%s", msg);
  exit(0);
}
