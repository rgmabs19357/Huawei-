/*
 ******************************************************************************
 *                     SOURCE FILE
 *
 *     Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipcom_syslog_data.c,v $ $Revision: 1.16.24.1 $
 *     $Source: /home/interpeak/CVSRoot/ipcom/src/ipcom_syslog_data.c,v $
 *     $State: Exp $ $Locker:  $
 *
 *     INTERPEAK_COPYRIGHT_STRING
 *     Design and implementation by Lennart Bang <lob@interpeak.se>
 ******************************************************************************
 */

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#define IPCOM_USE_CLIB_PROTO
#include "ipcom_clib.h"
#include "ipcom_syslog.h"


/*
 ****************************************************************************
 * 4                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         ipcom_syslogd_facility_names
 *===========================================================================
 */
IP_GLOBAL const char *ipcom_syslog_facility_names[IPCOM_LOG_FACILITY_MAX+1] =
{
    "kern",
    "user",
    "daemon",
    "auth",
    "syslog",
    "ipcom",
    "ipcom_shell",
    "ipcom_telnet",
    "ipcrypto",
    "ipipsec",
    "ipike",
    "ipl2tp",
    "ipldapc",
    "iplite",
    "ipnat",
    "ippppoe",
    "ipradius",
    "iprip",
    "ipssh",
    "ipssl",
    "ipsslproxy",
    "ipftp",
    "ipfirewall",
    "ipdhcpd",
    "ipdhcpc",
    "ipwebs",
    "ipnet",
    "iptftp",
    "ipsntp",
    "ipdhcps",
    "ipdhcps6",
    "ipsnmp",
    "ipdhcpr",
    "ipcom_drv_eth",
    "ipppp",
    "ipmip",
    "ipappl",
    "iptcp",
    "ipmlds",
    "ipemanate",
    "ipfreescale",
    "ipmcp",
    "ipprism",
    "ip8021x",
    "ipeap",
    "ipsafenet",
    "iphwcrypto",
    "ipnetsnmp",
    "ipquagga",
    "ipdhcpc6",
    "ipcci",
    "ipdiameter",
    "iprohc",
    "ipmpls",
    "ipcavium",
    "ipsctp",
    "ipifproxy",
    "ipcom_key_db",
    "ipwps",
    "wrnad",
    "*ILLEGAL*"
};


/*
 *===========================================================================
 *                         ipcom_syslogd_priority_names
 *===========================================================================
 */
IP_GLOBAL const char *ipcom_syslog_priority_names[8] =
{
    "Emerg",
    "Crit",
    "Error",
    "Warning",
    "Notice",
    "Info",
    "Debug",
    "Debug2"
};


/*
 ****************************************************************************
 * 9                    STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
