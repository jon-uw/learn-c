#include <unistd.h>
#include <stdio.h>
#include <sys/times.h>

static void pr_times(clock_t time, struct tms * start, struct tms * end);
static void do_cmd(char *cmdstr);

int main(int argc, char *argv[])
{
    int i = 0;
    setbuf(stdout, NULL);
    for (i = 1; i < argc; i++)
        do_cmd(argv[i]); // once for each command-line arg
    return 0;    
}

static void do_cmd(char *cmdstr)
{
    struct tms tmsstart, tmsend;
    clock_t start, end;

    int status;
    printf("\ncommand: %s\n", cmdstr);
    start  = times(&tmsstart);
    status = system(cmdstr);
    end = times(&tmsend);

    pr_times(end -start, &tmsstart, &tmsend);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;
    if (clktck == 0)
        clktck = sysconf(_SC_CLK_TCK);
    printf("\treal: %7.2f\n", real / (double)clktck);
    printf("\tuser: %7.2f\n",
        (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf("\tsys : %7.2f\n",
        (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf("\tchild user: %7.2f\n",
        (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf("\tchild sys : %7.2f\n",
        (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}


