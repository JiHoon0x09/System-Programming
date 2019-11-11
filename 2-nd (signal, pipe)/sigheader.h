#ifndef __SIGHEADER_H__
#define __SIGHEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define DIE(x) perror(x), exit(1)
#endif /* __SIGHEADER_H__ */
