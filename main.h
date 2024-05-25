/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

#ifndef _MAIN_H
#define _MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define MAX_STR_LEN 50

typedef struct {
    bool print_header;
    bool print_partition_info;
    bool print_signer_info;
    char filename[MAX_STR_LEN];
} Parameters;

static void print_usage(const char *exec_name, bool with_flags);
static Parameters *parse_args(int argc, char *argv[]);

#endif // _MAIN_H
