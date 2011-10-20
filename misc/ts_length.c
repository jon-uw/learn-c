/******************************************************************************
 * Filename:        ts_length.c  
 * Created on:      Mar 8, 2010  
 * Author:          jeremiah  
 * Description:     print out the length of each pid in the ts 
 *  
 ******************************************************************************/ 
 
#include <stdio.h>  
#include <stdint.h>  
 
#define TS_SYNC_BYTE 0x47  
#define TS_PACKET_SIZE 188  
 
typedef struct {  
    unsigned pid;  
    double clock_begin;  
    double clock_end;  
} pid_t;  

int pids[10] = {0}; 
pid_t pid_array[8191]; // max pid number in a ts file
unsigned char buf[TS_PACKET_SIZE];  
 
void get_length(unsigned char* pkt);  
void store_pid(unsigned pid, double clock);  
 
int main(int argc, char **argv) {  
    if (argc < 2) {  
        fprintf(stderr, "please use %s <file_name>\n", argv[0]);  
        return 1;  
    }  
 
    FILE *fp = fopen(argv[1], "rb");  
    if (!fp) {  
        perror("fopen");  
        return 1;  
    }  
    fseek(fp, 0, SEEK_END);  
    int size = ftell(fp);  
    rewind(fp);  
 
    while (size > 0) {  
        int read_size = fread(buf, 1, sizeof(buf), fp);  
        size -= read_size;  
        get_length(buf);  
    }  
 
    int i;  
    for (i = 0; i < 8191; i++) {  
        if (pid_array[i].pid != 0) {  
            printf("PID:0x%x length:%fs\n", pid_array[i].pid,   
                pid_array[i].clock_end - pid_array[i].clock_begin);  
        } else {  
            break;  
        }  
    }  

    //print out pid
    for (i = 0; i < 10; i++) {
        if (pids[i] != 0) {
            printf("pid is: %x\n", pids[i]);
        } else 
            break;
    }
    return 0;  
}  
 
void get_length(unsigned char* pkt) {  
    // Sanity check: Make sure we start with the sync byte:  
    if (pkt[0] != TS_SYNC_BYTE) {  
        fprintf(stderr, "Missing sync byte!\n");  
        return;  
    }  
    unsigned pid = ((pkt[1] & 0x1F) << 8) | pkt[2];  
    //printf("pid %x\n", pid);
    int i;
    for (i = 0; i < 10; i++) {
        if (pids[i] == pid)
            break;
        if (pids[i] == 0 )  {
            printf("add pid: %x\n", pid);
            pids[i] = pid;
            break;
        }
    }
 
    // If this packet doesn't contain a PCR, then we're not interested in it:  
    uint8_t const adaptation_field_control = (pkt[3] & 0x30) >> 4;  
    if (adaptation_field_control != 2 && adaptation_field_control != 3) {  
        return;  
    }  
 
    // there's no adaptation_field  
    uint8_t const adaptation_field_length = pkt[4];  
    if (adaptation_field_length == 0) {  
        return;  
    }  
 
    // no PCR  
    uint8_t const pcr_flag = pkt[5] & 0x10;  
    if (pcr_flag == 0) {  
        return;  
    }  
 
    // yes, we get a pcr  
    uint32_t pcr_base_high = (pkt[6] << 24) | (pkt[7] << 16) | (pkt[8] << 8)  
                        | pkt[9];  
    // caculate the clock  
    double clock = pcr_base_high / 45000.0;  
    if ((pkt[10] & 0x80)) {  
        clock += 1 / 90000.0; // add in low-bit (if set)  
    }  
    unsigned short pcr_extra = ((pkt[10] & 0x01) << 8) | pkt[11];  
    clock += pcr_extra / 27000000.0;  
 
    //unsigned pid = ((pkt[1] & 0x1F) << 8) | pkt[2];  
    store_pid(pid, clock);  
}  
 
void store_pid(unsigned pid, double clock) {  
    int i;  
    for (i = 0; i < 8191; i++) {  
        if (pid == pid_array[i].pid) {  
            break;  
        }  
    }  
    if (i == 8191) {  
        for (i = 0; i < 8191; i++) {  
            if (pid_array[i].pid == 0) {  
                break;  
            }  
        }  
        pid_array[i].pid = pid;  
        pid_array[i].clock_begin = clock;  
    } else {  
        pid_array[i].clock_end = clock;  
    }  
} 