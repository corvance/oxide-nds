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
 * @file ox_common.c
 * @author Corvance
 * @brief Common includes, pre-processor definitions, typedefs and macros.
 * @version 0.1
 * @date 2022-02-26
 */

#include <ox_common.h>

u8* oxLoadDataFS(const char* path, u32* sizePtr)
{
    u8* dest = NULL;
    FILE* file = fopen(path, "rb");

    if (file)
    {
        // Determine the file size.
        fseek(file, 0, SEEK_END);
        u32 size = ftell(file);
        rewind(file);

        // Store if desired.
        if (sizePtr)
            *sizePtr = size;

        dest = (u8*)malloc(size);

        if (dest)
            fread(dest, sizeof(u8), size, file);
        else
            debug_err("oxLoadDataFS: Insufficient memory.\n");
        fclose(file);
    }
    else
        debug_err("oxLoadDataFS:: File %s not found.\n", path);

    return dest;
}