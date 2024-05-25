/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

// All rights reserved to Samsung Electronics Co. LTD

#ifndef _SIGNER_H
#define _SIGNER_H

#include <stdio.h>

struct sign_footer {
    char signer_revision[16];
    char quick_build_id[16];
    char version_name[32];
    char build_time[16];
    char model_name[32];
    char system_rp_value[16];
    char kernel_rp_value[16];
    char build_variant[4];
    char kill_switch_magic[4];
    char factory_build[4];
    char binary_name[16];
    char quick_build_id_slot1[16];
    char quick_build_id_slot2[16];
    char reserved[52];
};

void print_signer_info(struct sign_footer *s_info);

#endif // _SIGNER_H
