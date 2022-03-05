// ┌────────────────────────────────────────────────────────────────────────────┐
// |                                                                            |
// |   ██████╗ ██╗  ██╗██╗██████╗ ███████╗███╗   ██╗██████╗ ███████╗            |
// |  ██╔═══██╗╚██╗██╔╝██║██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝            |
// |  ██║   ██║ ╚███╔╝ ██║██║  ██║█████╗  ██╔██╗ ██║██║  ██║███████╗            |
// |  ██║   ██║ ██╔██╗ ██║██║  ██║██╔══╝  ██║╚██╗██║██║  ██║╚════██║            |
// |  ╚██████╔╝██╔╝ ██╗██║██████╔╝███████╗██║ ╚████║██████╔╝███████║            |
// |   ╚═════╝ ╚═╝  ╚═╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝            |
// |                                                                            |
// |  OxideNDS - A 2D + 3D Game/Application Engine for the Nintendo DS (NTR),   |
// |  built on devkitARM and libnds.                                            |
// |                                                                            |
// |  Copyright (C) 2022 - 2022 Conaer Macpherson a.k.a Corvance                |
// |  OxideNDS is licensed under the terms of the MIT License.                  |
// |                                                                            |
// |  If you discover any bugs, issues or room for improvement, open an issue.  |
// |                                                                            |
// |  https://www.github.com/corvance/oxide-nds                                 |
// |                                                                            |
// └────────────────────────────────────────────────────────────────────────────┘

/**
 * @file ox_common.h
 * @author Corvance
 * @brief Common includes, pre-processor definitions, typedefs and macros.
 * @version 0.1
 * @date 2022-02-26
 */

#pragma once

#ifndef _OXIDE_COMMON_HEADER
#define _OXIDE_COMMON_HEADER

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------//
// When compiling OxideNDS with this option, error checks and messages are      //
// enabled. You can specify an error handling function with setErrorCallback(), //
// which takes a pointer to a function which accepts a const char* as its       //
// only parameter.                                                              //
// You can disable this option to save some RAM and CPU in release builds.      //
//------------------------------------------------------------------------------//

//------------------------------------------------------------------------------//
// INCLUDES                                                                     //
//------------------------------------------------------------------------------//

#include <nds.h>
#include <filesystem.h>

#include <stdio.h>
#include <string.h> // memcpy

//------------------------------------------------------------------------------//
// PRE-PROCESSOR DEFINITIONS                                                    //
//------------------------------------------------------------------------------//

/**
 * @brief Enabled debug error checks and messages.
 *
 * When compiling OxideNDS with this option, error checks and messages are
 * enabled. You can specify an error handling function using setErrorCallback(),
 * which takes a pointer to a function which accepts a const char* as its
 * only parameter.
 * You can disable this option to save some RAM and CPU in release builds.
 */
#define OXIDE_DEBUG

/**
 * @brief ANSI colors for console colorisation.
 */
#define ANSI_BLACK 30
#define ANSI_RED 31
#define ANSI_GREEN 32
#define ANSI_YELLOW 33
#define ANSI_BLUE 34
#define ANSI_MAGENTA 35
#define ANSI_CYAN 36
#define ANSI_WHITE 37

/**
 * @brief NDS screen dimensions.
 */
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

/**
 * @brief Default clear colour - Cornflower Blue.
 */
#define COMMON_CLEAR_COLOR 0x68B0D8FF
#define COMMON_CLEAR_COLOR_RED (COMMON_CLEAR_COLOR & 0xFF000000) >> 0x18
#define COMMON_CLEAR_COLOR_GREEN (COMMON_CLEAR_COLOR & 0x00FF0000) >> 0x10
#define COMMON_CLEAR_COLOR_BLUE (COMMON_CLEAR_COLOR & 0x0000FF00) >> 0x08
#define COMMON_CLEAR_COLOR_ALPHA (COMMON_CLEAR_COLOR & 0x000000FF)

/**
 * @brief Dummy for GL parameters included for compatibility but ignored.
 */
#define GL_DUMMY_PARAM 0

//------------------------------------------------------------------------------//
// TYPES                                                                        //
//------------------------------------------------------------------------------//

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;

//------------------------------------------------------------------------------//
// MACROS                                                                       //
//------------------------------------------------------------------------------//

/**
 * @brief Prints a debug info message to the console if OXIDE_DEBUG is enabled.
 */
#ifdef OXIDE_DEBUG
#define debug_info(...)                                              \
    do                                                               \
    {                                                                \
        printf("\x1b[%imINF: \x1b[%im", ANSI_GREEN, ANSI_WHITE); \
        printf(__VA_ARGS__);                                     \
    } while (0)

/**
 * @brief Prints a debug warning message to the console if N3D_DEBUG is enabled.
 */
#define debug_warn(...)                                               \
    do                                                                \
    {                                                                 \
        printf("\x1b[%imWRN: \x1b[%im", ANSI_YELLOW, ANSI_WHITE); \
        printf(__VA_ARGS__);                                      \
    } while (0)
/**
 * @brief Prints a debug error message to the console if N3D_DEBUG is enabled.
 */
#define debug_err(...)                                             \
    do                                                             \
    {                                                              \
        printf("\x1b[%imERR: \x1b[%im", ANSI_RED, ANSI_WHITE); \
        printf(__VA_ARGS__);                                   \
    } while (0)

#else
// Replacing the macro calls with empty space in release builds would cause compilation errors if a call was the single statement in an unbraced if/else.
#define debug_info(...) {}
#define debug_warn(...) {}
#define debug_err(...) {}
#endif  // OXIDE_DEBUG


//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

/**
 * @brief Loads binary data from a file in the NitroFS or FAT filesystem into memory, optionally storing the file size in a u16.
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 * @param sizePtr Pointer to u32 to store the size in - not stored if NULL.
 * @return u8* Pointer to the data loaded into memory.
 */
u8* oxLoadDataFS(const char* path, u32* sizePtr);

#ifdef __cplusplus
}
#endif

#endif // _OXIDE_COMMON_HEADER