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
 * @file ox_material.h
 * @author Corvance
 * @brief Material type and functionality.
 * @version 0.1
 * @date 2022-02-26
 */

#pragma once

#ifndef _OXIDE_MATERIAL_HEADER
#define _OXIDE_MATERIAL_HEADER

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------//
// INCLUDES                                                                     //
//------------------------------------------------------------------------------//

#include "../ox_common.h"

//------------------------------------------------------------------------------//
// TYPES                                                                        //
//------------------------------------------------------------------------------//

/**
 * @brief Material type, containing material properties.
 */
typedef struct
{
    u32 diffuse, ambient, specular, emission;
} oxMaterial;

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

/**
 * @brief The default material to apply to created models.
 */
extern oxMaterial* OX_DEFAULT_MATERIAL;

/**
 * @brief Sets the properties of the default oxMaterial.
 *
 * @param diffuse The diffuse property.
 * @param ambient The ambient property.
 * @param specular The specular property.
 * @param emission The emission property.
 */
void oxInitDefaultMaterial(u32 diffuse, u32 ambient, u32 specular, u32 emission);

/**
 * @brief Creates an oxMaterial with the given properties, and no texture + palette.
 *
 * @param diffuse The diffuse property.
 * @param ambient The ambient property.
 * @param specular The specular property.
 * @param emission The emission property.
 * @return oxMaterial* Pointer to the created material.
 */
oxMaterial* oxCreateMaterial(u32 diffuse, u32 ambient, u32 specular, u32 emission);


#ifdef __cplusplus
}
#endif

#endif // _OXIDE_MATERIAL_HEADER