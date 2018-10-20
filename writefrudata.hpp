#ifndef __IPMI_WRITE_FRU_DATA_H__
#define __IPMI_WRITE_FRU_DATA_H__

#include <systemd/sd-bus.h>

// IPMI commands for Storage net functions.
enum ipmi_netfn_storage_cmds
{
    IPMI_CMD_WRITE_FRU_DATA = 0x12
};

// Format of write fru data command
struct write_fru_data_t
{
    uint8_t frunum;
    uint8_t offsetls;
    uint8_t offsetms;
    uint8_t data;
} __attribute__((packed));

// Per IPMI v2.0 FRU specification
struct common_header
{
    uint8_t fixed;
    uint8_t internal_offset;
    uint8_t chassis_offset;
    uint8_t board_offset;
    uint8_t product_offset;
    uint8_t multi_offset;
    uint8_t pad;
    uint8_t crc;
} __attribute__((packed));

// first byte in header is 1h per IPMI V2 spec.
#define IPMI_FRU_HDR_BYTE_ZERO 1
#define IPMI_FRU_INTERNAL_OFFSET offsetof(struct common_header, internal_offset)
#define IPMI_FRU_CHASSIS_OFFSET offsetof(struct common_header, chassis_offset)
#define IPMI_FRU_BOARD_OFFSET offsetof(struct common_header, board_offset)
#define IPMI_FRU_PRODUCT_OFFSET offsetof(struct common_header, product_offset)
#define IPMI_FRU_MULTI_OFFSET offsetof(struct common_header, multi_offset)
#define IPMI_FRU_HDR_CRC_OFFSET offsetof(struct common_header, crc)
#define IPMI_EIGHT_BYTES 8

/**
 * Validate a FRU.
 *
 * @param[in] fruid - The ID to use for this FRU.
 * @param[in] fru_file_name - the filename of the FRU.
 * @param[in] bus_type - a systemd bus for publishing the information.
 * @param[in] bmc_fru - If a particular area accessible only by BMC.
 */
int ipmi_validate_fru_area(const uint8_t fruid, const char* fru_file_name,
                           sd_bus* bus_type, const bool bmc_fru);

#endif
