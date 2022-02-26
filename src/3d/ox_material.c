//------------------------------------------------------------------------------//
//                                                                              //
//  OxideNDS - A 2D + 3D Game/Application Engine for the Nintendo DS (NTR),     //
//  built on devkitARM and libnds.                                              //
//                                                                              //
//  Copyright (C) 2022 - 2022 Conaer Macpherson a.k.a Corvance                  //
//                                                                              //
//  https://www.github.com/corvance/oxide-nds                                   //
//                                                                              //
//------------------------------------------------------------------------------//

//------------------------------------------------------------------------------//
//                                                                              //
//  OxideNDS is licensed under the terms of the MIT License, available at       //
//  the file LICENSE in the root of this Git repository.                        //
//                                                                              //
//  If you discover any bugs, issues or room for improvement, open an           //
//  issue.                                                                      //
//                                                                              //
//------------------------------------------------------------------------------//

/**
 * @file ox_material.c
 * @author Corvance
 * @brief Material type and functionality.
 * @version 0.1
 * @date 2022-02-26
 */

#include <3d/ox_material.h>

//------------------------------------------------------------------------------//
// PRIVATE CODE                                                                 //
//------------------------------------------------------------------------------//

// Default material properties.
u32 defaultDiffuse = 0;
u32 defaultAmbient = 0;
u32 defaultSpecular = 0;
u32 defaultEmission = 0;

oxMaterial* OX_DEFAULT_MATERIAL;

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

void oxInitDefaultMaterial(u32 diffuse, u32 ambient, u32 specular, u32 emission)
{
    defaultDiffuse = diffuse;
    defaultAmbient = ambient;
    defaultSpecular = specular;
    defaultEmission = emission;

    OX_DEFAULT_MATERIAL = malloc(sizeof(oxMaterial));
    OX_DEFAULT_MATERIAL->diffuse = diffuse;         OX_DEFAULT_MATERIAL->ambient = ambient;
    OX_DEFAULT_MATERIAL->specular = specular;       OX_DEFAULT_MATERIAL->emission = emission;
}

oxMaterial* oxCreateMaterial(u32 diffuse, u32 ambient, u32 specular, u32 emission)
{
    oxMaterial* material = malloc(sizeof(oxMaterial));
    material->diffuse = diffuse;         material->ambient = ambient;
    material->specular = specular;       material->emission = emission;

    return material;

}