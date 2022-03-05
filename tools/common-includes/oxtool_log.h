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
 * @file oxtool_log.h
 * @author Corvance
 * @brief Logging macros for OxideNDS tools.
 * @version 0.1
 * @date 2022-02-24
 */

#pragma once

#define ANSI_BLACK 30
#define ANSI_RED 31
#define ANSI_GREEN 32
#define ANSI_YELLOW 33
#define ANSI_BLUE 34
#define ANSI_MAGENTA 35
#define ANSI_CYAN 36
#define ANSI_WHITE 37

#define log_info(...)                                              \
    do                                                               \
    {                                                                \
        printf("\x1b[%imINF: \x1b[%im", ANSI_GREEN, ANSI_WHITE); \
        printf(__VA_ARGS__);                                         \
    } while (0)

#define log_warn(...)                                               \
    do                                                                \
    {                                                                 \
        printf("\x1b[%imWRN: \x1b[%im", ANSI_YELLOW, ANSI_WHITE); \
        printf(__VA_ARGS__);                                          \
    } while (0)

#define log_err(...)                                             \
    do                                                             \
    {                                                              \
        printf("\x1b[%imERR: \x1b[%im", ANSI_RED, ANSI_WHITE); \
        printf(__VA_ARGS__);                                       \
    } while (0)
