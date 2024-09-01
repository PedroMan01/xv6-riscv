#include "types.h"
#include "user.h"

int main(void) {
    int generation = 0;
    int ancestor_pid = getancestor(generation);
    if (ancestor_pid < 0) {
        printf("E: No ancestor found for generation %d\n", generation);
    } else {
        printf("Ancestor PID for generation %d: %d\n", generation, ancestor_pid);
    }

    generation = 1;
    ancestor_pid = getancestor(generation);
    if (ancestor_pid < 0) {
        printf("E: No ancestor found for generation %d\n", generation);
    } else {
        printf("Ancestor PID for generation %d: %d\n", generation, ancestor_pid);
    }

    generation = 5;
    ancestor_pid = getancestor(generation);
    if (ancestor_pid < 0) {
        printf("E: No ancestor found for generation %d\n", generation);
    } else {
        printf("Ancestor PID for generation %d: %d\n", generation, ancestor_pid);
    }

    exit(0);
}
