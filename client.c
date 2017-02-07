#include <stdio.h>
#include <string.h>
#include <time.h>
#include <rpc/rpc.h>
#include "rsm.h"

#define MAX_LEN 100
#define SYS_TIME_KEY 1
#define CPU_USAGE_KEY 2
#define MEM_USAGE_KEY 3
#define LOAD_PROCS_KEY 4
#define QUIT_KEY 5

long get_user_input() {
    long choice;
    printf("=================================\n");
    printf("Menu\n");
    printf("%d. Current System Time\n", SYS_TIME_KEY);
    printf("%d. CPU Usage\n", CPU_USAGE_KEY);
    printf("%d. Memory Usage\n", MEM_USAGE_KEY);
    printf("%d. Load Procs per Minute\n", LOAD_PROCS_KEY);
    printf("%d. Quit\n", QUIT_KEY);
    printf("---------------------------------\n");
    scanf("%ld", &choice);
    printf("=================================\n");
    return choice;
}

int main(int argc, char ** argv) {
    CLIENT *client;
    char *server_name;
    char **server_result;
    long user_input;
    long * user_input_ptr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }
    server_name = argv[1];
    user_input_ptr = &user_input;
    client = clnt_create(server_name, RSM_PROG, RSM_VERS, "udp");
    if (client == NULL) {
        clnt_pcreateerror(server_name);
        exit(2);
    }
    user_input = get_user_input();
    while (user_input != QUIT_KEY) {
        server_result = rsm_1(user_input_ptr, client);
        if (server_result == NULL) {
            clnt_perror(client, server_name);
            exit(3);
        }
        printf("%s\n", *server_result);
        user_input = get_user_input();
    }
    clnt_destroy(client);
    return 0;
}
