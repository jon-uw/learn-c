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
    va_list ap;
    va_start(ap, fmt);
    handle_error(1, errno, fmt, ap);
    va_end(ap);
}
#endif


