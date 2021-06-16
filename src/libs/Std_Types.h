
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include <avr/io.h>


/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/



/*******************************************************************************
**                      Global Data Types                                    **
*******************************************************************************/

/* for OSEK compliance this typedef has been added */
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  #define E_OK      0
  typedef unsigned char StatusType;
#endif

/* STD011
  The Std_ReturnType (STD005) may be used with the following values (STD006):
  E_OK:     0
  E_NOT_OK: 1
*/
typedef uint8_t Std_ReturnType;
#define E_NOT_OK    1

typedef struct
{
  uint16_t  vendorID;
  uint16_t  moduleID;
  uint8_t  sw_major_version;
  uint8_t  sw_minor_version;
  uint8_t  sw_patch_version;
} Std_VersionInfoType; /* STD015                                */


#define STD_HIGH    1  /* Physical state 5V or 3.3V             */
#define STD_LOW     0  /* Physical state 0V                     */

#define STD_ACTIVE  1  /* Logical state active                  */
#define STD_IDLE    0  /* Logical state idle                    */

#define STD_ON      1
#define STD_OFF     0

/* NULL_PTR define with a void pointer to zero (the usage does not lead to compile warnings about implicit casts) */
# ifndef NULL_PTR
    #define NULL_PTR ((void *)0)
# endif

#define STD_OK  0U
#define STD_NOT_OK 1U
#define STD_PENDING 2U
#define STD_NO_SUPPORT 3U
#define STD_TIMEOUT 4U
#define STD_OK_ADCNOTVALID 5

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* STD_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

