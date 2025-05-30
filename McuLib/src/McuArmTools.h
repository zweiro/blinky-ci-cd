/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuArmTools.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : KinetisTools
**     Version     : Component 01.055, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2024-07-09, 10:10, # CodeGen: 829
**     Abstract    :
**
**     Settings    :
**          Component name                                 : McuArmTools
**          Utility                                        : McuUtility
**          SDK                                            : McuLib
**          Shell                                          : Enabled
**            Shell                                        : McuShell
**     Contents    :
**         SoftwareReset           - void McuArmTools_SoftwareReset(void);
**         UIDGet                  - uint8_t McuArmTools_UIDGet(McuArmTools_UID *uid);
**         UIDSame                 - bool McuArmTools_UIDSame(const McuArmTools_UID *src, const McuArmTools_UID...
**         UIDtoString             - uint8_t McuArmTools_UIDtoString(const McuArmTools_UID *uid, uint8_t *buf,...
**         GetKinetisFamilyString  - McuArmTools_ConstCharPtr McuArmTools_GetKinetisFamilyString(void);
**         GetPC                   - void* McuArmTools_GetPC(void);
**         GetSP                   - void* McuArmTools_GetSP(void);
**         SetPSP                  - void McuArmTools_SetPSP(void *setval);
**         SetLR                   - void McuArmTools_SetLR(uint32_t setval);
**         InitCycleCounter        - void McuArmTools_InitCycleCounter(void);
**         ResetCycleCounter       - void McuArmTools_ResetCycleCounter(void);
**         EnableCycleCounter      - void McuArmTools_EnableCycleCounter(void);
**         DisableCycleCounter     - void McuArmTools_DisableCycleCounter(void);
**         GetCycleCounter         - uint32_t McuArmTools_GetCycleCounter(void);
**         GetUsedMainStackSpace   - uint32_t McuArmTools_GetUsedMainStackSpace(void);
**         GetUnusedMainStackSpace - uint32_t McuArmTools_GetUnusedMainStackSpace(void);
**         FillMainStackSpace      - void McuArmTools_FillMainStackSpace(void);
**         GetLinkerMainStackSize  - uint32_t McuArmTools_GetLinkerMainStackSize(void);
**         GetLinkerMainStackTop   - McuArmTools_uint32_t_Ptr McuArmTools_GetLinkerMainStackTop(void);
**         GetLinkerMainStackBase  - McuArmTools_uint32_t_Ptr McuArmTools_GetLinkerMainStackBase(void);
**         ParseCommand            - uint8_t McuArmTools_ParseCommand(const unsigned char* cmd, bool *handled,...
**         Deinit                  - void McuArmTools_Deinit(void);
**         Init                    - void McuArmTools_Init(void);
**
** * Copyright (c) 2014-2024, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuArmTools.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup McuArmTools_module McuArmTools module documentation
**  @{
*/         

#ifndef __McuArmTools_H
#define __McuArmTools_H

/* MODULE McuArmTools. */
#include "McuLib.h" /* SDK and API used */
#include "McuArmToolsconfig.h" /* configuration */
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
  #include "pico/unique_id.h" /* for UID */
  #include "pico/bootrom.h"   /* for entering bootloader */
#endif
#include <stddef.h> /* for size_t */
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h" /* Command line shell */
#endif


#ifndef __BWUserType_McuArmTools_ConstCharPtr
#define __BWUserType_McuArmTools_ConstCharPtr
  typedef const uint8_t *McuArmTools_ConstCharPtr; /* Pointer to constant string */
#endif
#ifndef __BWUserType_McuArmTools_uint32_t_Ptr
#define __BWUserType_McuArmTools_uint32_t_Ptr
  typedef uint32_t *McuArmTools_uint32_t_Ptr; /* Pointer to uint32_t */
#endif


#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
  /* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
  #define McuArmTools_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
    /*!< DWT Control register */
  #define McuArmTools_DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
  #define McuArmTools_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
    /*!< DWT Cycle Counter register */
  #define McuArmTools_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define McuArmTools_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */
#endif

typedef struct {
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
  uint8_t id[sizeof(pico_unique_board_id_t)]; /* 8 bytes, 64 bits */
#else
  uint8_t id[16]; /* 128 bit ID */
#endif
} McuArmTools_UID;

typedef enum {
  McuArmTools_FAMILY_K10_K12,          /* K10 or K12 */
  McuArmTools_FAMILY_K20_K22,          /* K10 or K12 */
  McuArmTools_FAMILY_K30_K11_K61,      /* K30, K11 or K61 */
  McuArmTools_FAMILY_K40_K21,          /* K40 or K21 */
  McuArmTools_FAMILY_K70,              /* K70 */
  McuArmTools_FAMILY_UNKONWN,          /* Unknown */
  McuArmTools_FAMILY_LAST              /* Must be last one! */
} McuArmTools_FAMILY;

#define McuArmTools_PARSE_COMMAND_ENABLED  McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
  /*!< set to 1 if method ParseCommand() is present, 0 otherwise */

#ifdef __cplusplus
extern "C" {
#endif

#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuArmTools_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
/*
** ===================================================================
**     Method      :  ParseCommand (component KinetisTools)
**
**     Description :
**         Shell Command Line parser. Method is only available if Shell
**         is enabled in the component properties.
**     Parameters  :
**         NAME            - DESCRIPTION
**         cmd             - Pointer to command string
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**       * io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
#endif

void McuArmTools_SoftwareReset(void);
/*
** ===================================================================
**     Method      :  SoftwareReset (component KinetisTools)
**
**     Description :
**         Performs a reset of the device
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t McuArmTools_UIDGet(McuArmTools_UID *uid);
/*
** ===================================================================
**     Method      :  UIDGet (component KinetisTools)
**
**     Description :
**         Return the 128bit UID of the device
**     Parameters  :
**         NAME            - DESCRIPTION
**       * uid             - Pointer to 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

bool McuArmTools_UIDSame(const McuArmTools_UID *src, const McuArmTools_UID *dst);
/*
** ===================================================================
**     Method      :  UIDSame (component KinetisTools)
**
**     Description :
**         Compares two UID
**     Parameters  :
**         NAME            - DESCRIPTION
**       * src             - Pointer to 
**         Variable_1      - 
**     Returns     :
**         ---             - TRUE if the same, FALSE otherwise
** ===================================================================
*/

uint8_t McuArmTools_UIDtoString(const McuArmTools_UID *uid, uint8_t *buf, size_t bufSize);
/*
** ===================================================================
**     Method      :  UIDtoString (component KinetisTools)
**
**     Description :
**         Returns the value of the UID as string
**     Parameters  :
**         NAME            - DESCRIPTION
**         uid             - 
**       * buf             - Pointer to 
**         bufSize         - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

McuArmTools_ConstCharPtr McuArmTools_GetKinetisFamilyString(void);
/*
** ===================================================================
**     Method      :  GetKinetisFamilyString (component KinetisTools)
**
**     Description :
**         Determines the Kinetis Familiy based on SIM_SDID register
**     Parameters  : None
**     Returns     :
**         ---             - String describing the Kinetis Family
** ===================================================================
*/

void* McuArmTools_GetPC(void);
/*
** ===================================================================
**     Method      :  GetPC (component KinetisTools)
**
**     Description :
**         returns the program counter
**     Parameters  : None
**     Returns     :
**         ---             - program counter
** ===================================================================
*/

void* McuArmTools_GetSP(void);
/*
** ===================================================================
**     Method      :  GetSP (component KinetisTools)
**
**     Description :
**         returns the stack pointer
**     Parameters  : None
**     Returns     :
**         ---             - stack pointer
** ===================================================================
*/

void McuArmTools_SetPSP(void *setval);
/*
** ===================================================================
**     Method      :  SetPSP (component KinetisTools)
**
**     Description :
**         sets the process stack pointer
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new PSP value
**     Returns     : Nothing
** ===================================================================
*/

void McuArmTools_SetLR(uint32_t setval);
/*
** ===================================================================
**     Method      :  SetLR (component KinetisTools)
**
**     Description :
**         Sets the link register
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new LR value
**     Returns     : Nothing
** ===================================================================
*/

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
#define McuArmTools_InitCycleCounter() \
  McuArmTools_DEMCR |= McuArmTools_TRCENA_BIT
  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */
/*
** ===================================================================
**     Method      :  InitCycleCounter (component KinetisTools)
**
**     Description :
**         Initializes the cycle counter, available if the core has a
**         DWT (Data Watchpoint and Trace) unit, usually present on
**         M3/M4/M7
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
#define McuArmTools_ResetCycleCounter() \
  McuArmTools_DWT_CYCCNT = 0
  /*!< Reset cycle counter */
/*
** ===================================================================
**     Method      :  ResetCycleCounter (component KinetisTools)
**
**     Description :
**         Reset the cycle counter (set it to zero)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
#define McuArmTools_EnableCycleCounter() \
  McuArmTools_DWT_CONTROL |= McuArmTools_DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */
/*
** ===================================================================
**     Method      :  EnableCycleCounter (component KinetisTools)
**
**     Description :
**         Enables counting the cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
#define McuArmTools_DisableCycleCounter() \
  McuArmTools_DWT_CONTROL &= ~McuArmTools_DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */
/*
** ===================================================================
**     Method      :  DisableCycleCounter (component KinetisTools)
**
**     Description :
**         Disables the cycle counter.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3 /* only for Cortex-M3 or higher */
#define McuArmTools_GetCycleCounter() \
  McuArmTools_DWT_CYCCNT
  /*!< Read cycle counter register */
/*
** ===================================================================
**     Method      :  GetCycleCounter (component KinetisTools)
**
**     Description :
**         Return the current cycle counter value
**     Parameters  : None
**     Returns     :
**         ---             - cycle counter
** ===================================================================
*/
#endif

void McuArmTools_Deinit(void);
/*
** ===================================================================
**     Method      :  Deinit (component KinetisTools)
**
**     Description :
**         Driver de-initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void McuArmTools_Init(void);
/*
** ===================================================================
**     Method      :  Init (component KinetisTools)
**
**     Description :
**         Driver initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint32_t McuArmTools_GetUsedMainStackSpace(void);
/*
** ===================================================================
**     Method      :  GetUsedMainStackSpace (component KinetisTools)
**
**     Description :
**         Returns the used main stack space, based on the overwritten
**         checking pattern.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint32_t McuArmTools_GetUnusedMainStackSpace(void);
/*
** ===================================================================
**     Method      :  GetUnusedMainStackSpace (component KinetisTools)
**
**     Description :
**         Calculates the unused stack space, based on the checking
**         pattern.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void McuArmTools_FillMainStackSpace(void);
/*
** ===================================================================
**     Method      :  FillMainStackSpace (component KinetisTools)
**
**     Description :
**         Fill the stack space with the checking pattern, up to the
**         current MSP.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint32_t McuArmTools_GetLinkerMainStackSize(void);
/*
** ===================================================================
**     Method      :  GetLinkerMainStackSize (component KinetisTools)
**
**     Description :
**         Returns the size of the main (MSP) stack size, using linker
**         symbols for top (higher address) and base (lower address).
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

McuArmTools_uint32_t_Ptr McuArmTools_GetLinkerMainStackTop(void);
/*
** ===================================================================
**     Method      :  GetLinkerMainStackTop (component KinetisTools)
**
**     Description :
**         Return the stack top, as set in the linker file. The stack
**         grows from the top (higher address) to the base (lower
**         address).
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

McuArmTools_uint32_t_Ptr McuArmTools_GetLinkerMainStackBase(void);
/*
** ===================================================================
**     Method      :  GetLinkerMainStackBase (component KinetisTools)
**
**     Description :
**         Return the stack bottom, as configured in the linker file.
**         The stack grows from the top (higher address) to the base
**         (lower address).
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END McuArmTools. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __McuArmTools_H */
/*!
** @}
*/
