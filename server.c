#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <rpc/rpc.h>
#include <time.h>
#include "rsm.h"

#define MAX_LEN 500

char ** rsm_1(long * option, CLIENT * client) {
    static char *ptr;
    struct sysinfo info;
    struct mallinfo mem_info;
    double load_avgs[3];
    static char s[MAX_LEN];
    int func_resp;
    struct tm *timeptr;
    time_t clock;

    if (*option == 1) {
        clock = time(0);
        timeptr = localtime(&clock);
        strftime(s, MAX_LEN, "%A, %B %d, %Y - %T", timeptr);
        ptr = s;
    }
    else if (*option == 2) {
        func_resp = sysinfo(&info);
        if (func_resp == -1) {
            sprintf(s, "Could not get system info\0");
        }
        else {
            sprintf(s, "Uptime: %ld\nLoads: %lu, %lu, %lu\nTotal RAM: %lu\nFree RAM: %lu\nShared RAM: %lu\nBuffer RAM: %lu\nSwap Space Size: %lu\nAvailable Swap Space: %lu\n# Processes: %hu\0", info.uptime, info.loads[0], info.loads[1], info.loads[2], info.totalram, info.freeram, info.sharedram, info.bufferram, info.totalswap, info.freeswap, info.procs);
        }
        ptr = s;
    }
    else if (*option == 3) {
        mem_info = mallinfo();
        sprintf(s, "Total non-mmapped: %d\n# Free chunks: %d\n# Free fastbin blocks: %d\n# Mmapped regions: %d\nSpace allocated in mmapped regions: %d\nMax total allocated space: %d\nSpace in freed fastbin blocks: %d\nTotal allocated space: %d\nTotal free space: %d\nTop-most, releaseable space: %d\0", mem_info.arena, mem_info.ordblks, mem_info.smblks, mem_info.hblks, mem_info.hblkhd, mem_info.usmblks, mem_info.fsmblks, mem_info.uordblks, mem_info.fordblks, mem_info.keepcost);
        ptr = s;
    }
    else if (*option == 4) {
        func_resp = getloadavg(load_avgs, 3);
        if (func_resp == -1) {
            sprintf(s, "Could not get load procs\0");
        }
        else {
            sprintf(s, "Average for last minute: %f\nAverage for last 5 minutes: %f\nAverage for last 15 minutes: %f\0", load_avgs[0], load_avgs[1], load_avgs[2]);
        }
        ptr = s;
    }
    else {
        ptr = "Received Invalid Data";
    }
    return &ptr;
}
