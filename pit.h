/*
 * Samsung PIT Viewer
 * @BlackMesa123, 2024
 */

// All rights reserved to Samsung Electronics Co. LTD

#ifndef _PIT_H
#define _PIT_H

#include <stdbool.h>
#include <stdio.h>

#define PIT_MAGIC (0x12349876)

enum binary_list {
    BINARY_TYPE_AP,
    BINARY_TYPE_CP
};

enum device_list {
    PARTITION_DEV_TYPE_ONENAND,
    PARTITION_DEV_TYPE_NAND,
    PARTITION_DEV_TYPE_EMMC,
    PARTITION_DEV_TYPE_SPI,
    PARTITION_DEV_TYPE_IDE,
    PARTITION_DEV_TYPE_NAND_X16,
    PARTITION_DEV_TYPE_NOR,
    PARTITION_DEV_TYPE_NAND_WB1,
    PARTITION_DEV_TYPE_UFS
};

enum part_type_list {
    PARTITION_PIT_TYPE_NONE,
    PARTITION_PIT_TYPE_BCT,
    PARTITION_PIT_TYPE_BOOTLOADER,
    PARTITION_PIT_TYPE_PARTITION_TABLE,
    PARTITION_PIT_TYPE_NVDATA,
    PARTITION_PIT_TYPE_DATA,
    PARTITION_PIT_TYPE_MBR,
    PARTITION_PIT_TYPE_EBR,
    PARTITION_PIT_TYPE_GP1,
    PARTITION_PIT_TYPE_GPT
};

enum part_filesys_list {
    PARTITION_FS_TYPE_NONE,
    PARTITION_FS_TYPE_BASIC,
    PARTITION_FS_TYPE_ENHANCED,
    PARTITION_FS_TYPE_EXT2,
    PARTITION_FS_TYPE_YAFFS2,
    PARTITION_FS_TYPE_EXT4
};

struct pit_header {
    unsigned int magic;
    unsigned int count;
    char dummy[16];
    unsigned int numlun;
};

struct pit_partinfo {
    int binary;
    int device;
    unsigned int id;
    int type;
    int filesys;
    unsigned int blkstart;
    unsigned int blknum;
    unsigned int lun;
    unsigned int filesize;
    char name[32];
    char filename[32];
    char option[32];
};

static char *get_binary_type(int bin);
static char *get_device_type(int device);
static char *get_partition_type(int type);
static char *get_partition_fs(int filesys);
bool pit_check_integrity(const struct pit_header *hdr);
void pit_print_hdr(const struct pit_header *hdr);
void pit_print_partinfo(const struct pit_partinfo *p_info, int count);

#endif // _PIT_H
