//------------------------------------------------------------------------------//
//                                                                              //
//  OxideNDS - A 2D + 3D Game/Application Engine for the Nintendo DS (NTR),     //
//  built on devkitARM and libnds.                                              //
//                                                                              //
//  Copyright (C) 2022 - 2022 Conaer Macpherson                                 //
//                            a.k.a Corvance                                    //
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
 * @file ox_3d.h
 * @author Corvance
 * @brief Main header for the 3D component.
 * @version 0.1
 * @date 2022-02-26
 */

#pragma once

#ifndef _OXIDE_3D_MAIN_HEADER
#define _OXIDE_3D_MAIN_HEADER

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------//
// INCLUDES                                                                     //
//------------------------------------------------------------------------------//

#include "../ox_common.h"
#include "ox_material.h"
#include "ox_model.h"

//------------------------------------------------------------------------------//
// PRE-PROCESSOR DEFINITIONS                                                    //
//------------------------------------------------------------------------------//

#define CLEAR_POLY_ID 255

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

/**
 * @brief Initialise the 3D engine on the main screen (top by default).
 */
void oxInit3D_Main();

/**
 * @brief Shutdown the 3D engine.
 */
void oxShutdown3D();

/**
 * @brief Loads the matrices to begin rendering a frame.
 */
void oxBeginFrame();

/**
 * @brief Loads the matrices and flushes to end rendering a frame.
 */
void oxEndFrame();

#ifdef __cplusplus
}
#endif

#endif // _OXIDE_3D_MAIN_HEADER