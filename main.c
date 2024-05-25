/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

#include "main.h"
#include "pit.h"
#include "signer.h"

static void print_usage(const char *exec_name, bool with_flags) {
    printf("Usage: %s [-his] <pit file>\n", exec_name);
    if (with_flags) {
        printf("  %s\n", "-h: Print PIT header info");
        printf("  %s\n", "-i: Print PIT partitions info");
        printf("  %s\n", "-s: Print Samsung signer info");
    }
    exit(EXIT_FAILURE);
}

static Parameters *parse_args(int argc, char *argv[]) {
    Parameters *p = NULL;

    if (argc == 1) {
        print_usage(argv[0], false);
    } else {
        p = malloc(sizeof(Parameters));
        if (!p) {
            exit(EXIT_FAILURE);
        }

        while (argc != 1) {
            if (argv[argc - 1][0] != '-') {
                if (p->filename[0] == '\0') {
                    strncpy(p->filename, argv[argc - 1], MAX_STR_LEN - 1);
                    p->filename[MAX_STR_LEN - 1] = '\0';
                }
            } else {
                if (strcmp(argv[argc - 1], "--help") == 0) {
                    print_usage(argv[0], true);
                }

                while (*++argv[argc - 1]) {
                    switch (*argv[argc - 1]) {
                        case 'h':
                            p->print_header = true;
                            break;
                        case 'i':
                            p->print_partition_info = true;
                            break;
                        case 's':
                            p->print_signer_info = true;
                            break;
                    }
                }
            }

            --argc;
        }
    }

    return p;
}

int main(int argc, char *argv[]) {
    printf("Samsung PIT Viewer v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);

    Parameters *p = parse_args(argc, argv);

    if (p->filename[0] == '\0') {
        printf("%s\n", "No file was supplied. Exiting.");
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(p->filename, "rb");
    if (!f) {
        printf("File \"%s\" couldn't be opened. Exiting.\n", p->filename);
        exit(EXIT_FAILURE);
    }

    struct pit_header *hdr = malloc(sizeof(struct pit_header));
    if (!hdr) {
        exit(EXIT_FAILURE);
    }
    fread(hdr, 1, sizeof(struct pit_header), f);
    if (!pit_check_integrity(hdr)) {
        printf("File \"%s\" is not valid. Exiting.\n", p->filename);
        exit(EXIT_FAILURE);
    }
    if (p->print_header) {
        pit_print_hdr(hdr);
    }

    for (size_t i = 0; i < hdr->count; i++) {
        struct pit_partinfo *p_info = malloc(sizeof(struct pit_partinfo));
        if (!p_info) {
            exit(EXIT_FAILURE);
        }
        fread(p_info, 1, sizeof(struct pit_partinfo), f);
        if (p->print_partition_info) {
            pit_print_partinfo(p_info, i + 1);
        }
        free(p_info);
    }

    free(hdr);

    if (p->print_signer_info) {
        struct sign_footer *s_info = malloc(sizeof(struct sign_footer));
        if (!s_info) {
            exit(EXIT_FAILURE);
        }
        fread(s_info, 1, sizeof(struct sign_footer), f);
        print_signer_info(s_info);
        free(s_info);
    }

    fclose(f);
    return 0;
}
