#include "types.h"
#include "user.h"

int main(void) {
    int ppid = getppid();
    printf("Parent PID: %d\n", ppid); 
    exit(0); 
}
