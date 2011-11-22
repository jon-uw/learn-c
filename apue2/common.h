/* 
 * contains common headers and some error handling methods
*/

#ifndef _COMMON_H
#define _COMMON_H


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <fcntl.h>
#include <syslog.h>
#include <signal.h>

#define MAXLINE 4096
static void handle_error(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE, fmt, ap);
    if (errnoflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s"
	    , strerror(error));
    strcat(buf, "\n");
    fputs(buf, stderr);
}

void err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    handle_error(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_exit(int error, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    handle_error(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}


void err_sys(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    handle_error(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}


void err_ret(const char *fmt, ...)
{
    printf("in err_ret\n");
    va_list ap;
    va_start(ap, fmt);
    handle_error(1, errno, fmt, ap);
    va_end(ap);
}

void
set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
    int        val;

    if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
        {
            printf("fcntl F_GETFL error");
            exit(1);
        }

    val |= flags;        /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0)
        {
            printf("fcntl F_SETFL error");
            exit(1);
        }
}

void
clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) == -1)
    {
        syslog(LOG_ERR, __FILE__, __LINE__,"fcntl() error : %s", strerror(errno));
        exit(1);
    }
    val &= ~flags; /* turn flags off */

    if (fcntl(fd, F_SETFL, val) == -1)
    {
        syslog(LOG_ERR, __FILE__, __LINE__,"fcntl() error : %s", strerror(errno));
        exit(1);
    }
    return;
}
#endif


