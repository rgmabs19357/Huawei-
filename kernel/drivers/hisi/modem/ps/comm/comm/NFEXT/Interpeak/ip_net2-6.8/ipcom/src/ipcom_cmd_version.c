/*
 ******************************************************************************
 *                     INTERPEAK SOURCE FILE
 *
 *   Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipcom_cmd_version.c,v $ $Revision: 1.1 $
 *   $Source: /home/interpeak/CVSRoot/ipcom/src/ipcom_cmd_version.c,v $
 *   $State: Exp $ $Locker:  $
 *
 *   INTERPEAK_COPYRIGHT_STRING
 *   Design and implementation by Lennart Bang <email@interpeak.se>
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
#include "ipcom_type.h"
#include "ipcom_cstyle.h"
#include "ipcom_clib.h"
#include "ipcom_ipd.h"


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC int ipcom_cmd_version(int argc, char **argv);


/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_cmd_version
 *===========================================================================
 * Description:     Shell command: Print Interpeak product versions.
 * Parameters:      argc - number of arguments
 *                  argv - pointer to pointer to the arguments
 * Returns:         0
 *
 */
IP_PUBLIC int
ipcom_cmd_version(int argc, char **argv)
{
    int i;

    (void)argc;
    (void)argv;

    /* Print IPCOM version */
    ipcom_printf(ipcom_version);
    ipcom_printf(IP_LF);

    /* Printf the other product versions. */
    for(i = 0; ipcom_ipd_products[i].name != IP_NULL; i++)
        if (ipcom_ipd_products[i].version != IP_NULL)
            ipcom_printf("%s"IP_LF, ipcom_ipd_products[i].version());

    return 0;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

