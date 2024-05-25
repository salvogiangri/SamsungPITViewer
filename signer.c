/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

// All rights reserved to Samsung Electronics Co. LTD

#include "signer.h"

void print_signer_info(struct sign_footer *s_info) {
    printf("\n%s\n", "----- Signer info -----");
    printf("SignSystemRevision: %s\n", s_info->signer_revision);
    printf("QuickBuildId: %s\n", s_info->quick_build_id);
    printf("VersionName: %s\n", s_info->version_name);
    printf("BuildTime: %s\n", s_info->build_time);
    printf("ModelName: %s\n", s_info->model_name);
    printf("SystemRPValue: %s\n", s_info->system_rp_value);
    printf("KernelRPValue: %s\n", s_info->kernel_rp_value);
    printf("BuildVariant: %s\n", s_info->build_variant);
    printf("KillSwitchMagic: %s\n", s_info->kill_switch_magic);
    printf("FactoryBuild: %s\n", s_info->factory_build);
    printf("BinaryName: %s\n", s_info->binary_name);
    if (s_info->quick_build_id_slot1[0] != '\0') {
        printf("QuickBuildIdSlot1: %s\n", s_info->quick_build_id_slot1);
    }
    if (s_info->quick_build_id_slot2[0] != '\0') {
        printf("QuickBuildIdSlot2: %s\n", s_info->quick_build_id_slot2);
    }
}
