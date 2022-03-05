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
 * @file ox_model.h
 * @author Corvance
 * @brief 3D model type and functionality.
 * @version 0.1
 * @date 2022-02-26
 */

#pragma once

#ifndef _OXIDE_MODEL_HEADER
#define _OXIDE_MODEL_HEADER

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------//
// INCLUDES                                                                     //
//------------------------------------------------------------------------------//

#include "../ox_common.h"
#include "ox_material.h"

//------------------------------------------------------------------------------//
// TYPES                                                                        //
//------------------------------------------------------------------------------//

/**
 * @brief 3D vertex array as a union to allow both [] and .xyz access. Uses fixed point v16s (u16/uint16_ts). Intended for Mesh and Normal vertices.
 */
typedef union
{
    v16 elems[3];

    struct
    {
        v16 x, y, z;
    };
} oxVertex3D;

/**
 * @brief 2D vertex array as a union to allow to allow both [] and .xy access. Uses fixed point v16s (u16/uint16_ts). Intended for Texture vertices.
 */
typedef union
{
    v16 elems[2];

    struct
    {
        v16 x, y;
    };
} oxVertex2D;

/**
 * @brief OxideNDS oxModel index, specifying the mesh vertex, texture vertex and normal vertex.
 */
typedef struct
{
    u32 mesh;
    u32 tex;
    u32 norm;
} oxIndex;

/**
 * @brief OxideNDS model, with mesh, texture and normal vertices, and indices, as well as a material.
 */
typedef struct
{
    oxVertex3D* meshVertices;
    oxVertex2D* texVertices;
    oxVertex3D* normVertices;
    oxIndex* indices;
    u32 numMeshVertices;
    u32 numTexVertices;
    u32 numNormVertices;
    u32 numIndices;

    oxMaterial* material;
} oxModel;

/**
 * @brief oxTexture Loader function pointer type e.g., to load your own non-GRIT image formats. Custom loaders will still need to glBind and glGenTextures as normal.
 *
 * @param tex The oxTexture* to load into.
 * @param path Path to the texture file.
 */
typedef void(*oxStaticModelLoader)(oxModel* model, const char* path);

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

/**
 * @brief Creates and returns a static oxModel loaded from the filesystem, with the default oxMaterial.
 *
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 * @return oxModel* pointer to the created oxModel.
 */
oxModel* oxCreateStaticModel(const char* path);

/**
 * @brief Creates and returns a static oxModel loaded from the filesystem, with the default oxMaterial, via a user-defined oxStaticModelLoader function.
 *
 * @param loader - Pointer to a function with signature void loader(oxModel*, const char*).
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 * @return oxModel* pointer to the created oxModel.
 */
oxModel* oxCreateStaticModel_Custom(oxStaticModelLoader loader, const char* path);

/**
 * @brief Loads into an existing oxModel from the filesystem, with the default oxMaterial.
 *
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 */
void oxLoadStaticModel(oxModel* model, const char* path);

/**
 * @brief Loads into an existing oxModel from the filesystem, with the default oxMaterial, via a user-defined oxStaticModelLoader function.
 *
 * @param loader - Pointer to a function with signature void loader(oxModel*, const char*).
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 */
void oxLoadStaticModel_Custom(oxModel* model, oxStaticModelLoader loader, const char* path);


/**
 * @brief Convenience version of oxCreateStaticModel. Creates and returns a static oxModel loaded from the filesystem, with the given oxMaterial.
 *
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 * @param material The oxMaterial.
 * @return oxModel* pointer to the created oxModel.
 */
oxModel* oxCreateStaticModelWithMaterial(const char* path, oxMaterial* material);

/**
 * @brief Convenience version of oxCreateStaticModel_Custom. Creates and returns a static oxModel loaded from the filesystem, with the given material.
 *
 * @param loader - Pointer to a function with signature void loader(oxModel*, const char*).
 * @param path NitroFS or FAT path to the static model file (.oxsm).
 * @param material The oxMaterial.
 * @return oxModel* pointer to the created oxModel.
 */
oxModel* oxCreateStaticModelWithMaterial_Custom(oxStaticModelLoader loader, const char* path, oxMaterial* material);


/**
 * @brief Sets up rendering to use the properties of the provided oxModel.
 *
 * @param model The model to use the properties of.
 */
void oxUseModelRenderProps(oxModel* model);

/**
 * @brief Draws a single index of an oxModel.
 *
 * @param model oxModel to draw an index of.
 * @param index Position index of the index to draw.
 */
void oxDrawIndex(oxModel* model, u32 index);

/**
 * @brief Draws an oxModel as GL_TRIANGLES.
 *
 * @param model The oxModel to draw.
 */
void oxDrawModelTris(oxModel* model);

#ifdef __cplusplus
}
#endif

#endif // _OXIDE_MODEL_HEADER