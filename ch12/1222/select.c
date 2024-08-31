#include "../../include/csapp.h"

void echo(int connfd, fd_set* read_set);
void command(void);

int main(int argc, char** argv)
{
  int listenfd, connfd, cnt, i;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  fd_set read_set, ready_set;

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  listenfd = Open_listenfd(argv[1]);
  cnt = listenfd + 1;

  FD_ZERO(&read_set);
  FD_SET(STDIN_FILENO, &read_set);
  FD_SET(listenfd, &read_set);

  while (1)
  {
    ready_set = read_set;
    Select(cnt, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &ready_set))
      command();
    if (FD_ISSET(listenfd, &ready_set))
    {
      clientlen = sizeof(struct sockaddr_storage);
      connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
      if (connfd + 1 > cnt)
	cnt = connfd + 1;
      FD_SET(connfd, &read_set);
    }

    for (i = listenfd + 1; i < cnt; i++)
      if (FD_ISSET(i, &ready_set))
	echo(i, &read_set);
  }
}

void command(void)
{
  char buf[MAXLINE];
  if (!Fgets(buf, MAXLINE, stdin))
    exit(0);
  printf("%s", buf);
}

void echo(int connfd, fd_set* read_set)
{
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);
  if (!(n = Rio_readlineb(&rio, buf, MAXLINE)))
  {
    Close(connfd);
    FD_CLR(connfd, read_set);
    return;
  }
  Rio_writen(connfd, buf, n);
}
