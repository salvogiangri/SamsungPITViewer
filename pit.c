/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

// All rights reserved to Samsung Electronics Co. LTD

#include "pit.h"

static char *get_binary_type(int binary) {
    switch (binary) {
        case BINARY_TYPE_AP:
            return "BINARY_TYPE_AP";
        case BINARY_TYPE_CP:
            return "BINARY_TYPE_CP";
    }

    return "Unknown";
}

static char *get_device_type(int device) {
    switch (device) {
        case PARTITION_DEV_TYPE_ONENAND:
            return "PARTITION_DEV_TYPE_ONENAND";
        case PARTITION_DEV_TYPE_NAND:
            return "PARTITION_DEV_TYPE_NAND";
        case PARTITION_DEV_TYPE_EMMC:
            return "PARTITION_DEV_TYPE_EMMC";
        case PARTITION_DEV_TYPE_SPI:
            return "PARTITION_DEV_TYPE_SPI";
        case PARTITION_DEV_TYPE_IDE:
            return "PARTITION_DEV_TYPE_IDE";
        case PARTITION_DEV_TYPE_NAND_X16:
            return "PARTITION_DEV_TYPE_NAND_X16";
        case PARTITION_DEV_TYPE_NOR:
            return "PARTITION_DEV_TYPE_NOR";
        case PARTITION_DEV_TYPE_NAND_WB1:
            return "PARTITION_DEV_TYPE_NAND_WB1";
        case PARTITION_DEV_TYPE_UFS:
            return "PARTITION_DEV_TYPE_UFS";
    }

    return "Unknown";
}

static char *get_partition_type(int type) {
    switch (type) {
        case PARTITION_PIT_TYPE_NONE:
            return "PARTITION_PIT_TYPE_NONE";
        case PARTITION_PIT_TYPE_BCT:
            return "PARTITION_PIT_TYPE_BCT";
        case PARTITION_PIT_TYPE_BOOTLOADER:
            return "PARTITION_PIT_TYPE_BOOTLOADER";
        case PARTITION_PIT_TYPE_PARTITION_TABLE:
            return "PARTITION_PIT_TYPE_PARTITION_TABLE";
        case PARTITION_PIT_TYPE_NVDATA:
            return "PARTITION_PIT_TYPE_NVDATA";
        case PARTITION_PIT_TYPE_DATA:
            return "PARTITION_PIT_TYPE_DATA";
        case PARTITION_PIT_TYPE_MBR:
            return "PARTITION_PIT_TYPE_MBR";
        case PARTITION_PIT_TYPE_EBR:
            return "PARTITION_PIT_TYPE_EBR";
        case PARTITION_PIT_TYPE_GP1:
            return "PARTITION_PIT_TYPE_GP1";
        case PARTITION_PIT_TYPE_GPT:
            return "PARTITION_PIT_TYPE_GPT";
    }

    return "Unknown";
}

static char *get_partition_fs(int filesys) {
    switch (filesys) {
        case PARTITION_FS_TYPE_NONE:
            return "PARTITION_FS_TYPE_NONE";
        case PARTITION_FS_TYPE_BASIC:
            return "PARTITION_FS_TYPE_BASIC";
        case PARTITION_FS_TYPE_ENHANCED:
            return "PARTITION_FS_TYPE_ENHANCED";
        case PARTITION_FS_TYPE_EXT2:
            return "PARTITION_FS_TYPE_EXT2";
        case PARTITION_FS_TYPE_YAFFS2:
            return "PARTITION_FS_TYPE_YAFFS2";
        case PARTITION_FS_TYPE_EXT4:
            return "PARTITION_FS_TYPE_EXT4";
    }

    return "Unknown";
}

bool pit_check_integrity(const struct pit_header *hdr) {
	return (hdr->magic == PIT_MAGIC);
}

void pit_print_hdr(const struct pit_header *hdr) {
    printf("\n%s\n", "----- PIT Header -----");
    printf("Magic: 0x%08x\n", hdr->magic);
    printf("Partitions count: %u\n", hdr->count);
    printf("File type: %.8s\n", hdr->dummy);
    printf("SoC/bootloader tag: %s\n", hdr->dummy + 8);
    printf("LUNs count: %u\n", hdr->numlun);
}

void pit_print_partinfo(const struct pit_partinfo *p_info, int count) {
        printf("\n----- Partition: %d -----\n", count);
        printf("Partition ID: %u\n", p_info->id);
        printf("Partition name: %s\n", p_info->name);
        if (p_info->filename[0] != '\0') {
            printf("Partition file name: %s\n", p_info->filename);
        }
        if (p_info->option[0] != '\0') {
            printf("Partition options: %s\n", p_info->option);
        }
        //printf("Block location: %u\n", p_info->blkstart);
        if (p_info->blknum > 0) {
            printf("Partition size: %ld bytes\n", (long)p_info->blknum * 4096);
        }
        if (p_info->filesize > 0) {
            printf("Partition file size: %d\n", p_info->filesize);
        }
        printf("Binary type: %s\n", get_binary_type(p_info->binary));
        printf("Device type: %s\n", get_device_type(p_info->device));
        printf("Partition type: %s\n", get_partition_type(p_info->type));
        printf("Partition filesystem: %s\n", get_partition_fs(p_info->filesys));
        printf("Partition LUN: %u\n", p_info->lun);
}
