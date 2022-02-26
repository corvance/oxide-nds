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
 * @file ox_model.c
 * @author Corvance
 * @brief 3D model type and functionality.
 * @version 0.1
 * @date 2022-02-26
 */

#include <3d/ox_model.h>

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

oxModel* oxCreateStaticModel(const char* path)
{
    // Create the model.
    oxModel* model = malloc(sizeof(oxModel));
    oxLoadStaticModel(model, path);

    return model;
}

oxModel* oxCreateStaticModel_Custom(oxStaticModelLoader loader, const char* path)
{
    oxModel* model = malloc(sizeof(oxModel));
    loader(model, path);

    return model;
}

void oxLoadStaticModel(oxModel* model, const char* path)
{
    debug_info("Loading OXSM.\n");

    // Existing model's vertices are no longer needed.
    // Don't free the material as it may be shared with other models. It can be done manually if needed.
    if (model)
    {
        free(model->meshVertices);
        free(model->texVertices);
        free(model->normVertices);
        free(model->indices);
        model->numMeshVertices = 0;
        model->numTexVertices = 0;
        model->numNormVertices = 0;
        model->numIndices = 0;
    }

    FILE* modelFile = fopen(path, "rb");

    if (modelFile)
    {
        // Reader header values to determine number of each vertex/index type.
        fread(&model->numMeshVertices, sizeof(u32), 4, modelFile);

        // Allocate memory for the vertices and indices.
        model->meshVertices = malloc(model->numMeshVertices * sizeof(oxVertex3D));
        model->texVertices = malloc(model->numTexVertices * sizeof(oxVertex2D));
        model->normVertices = malloc(model->numNormVertices * sizeof(oxVertex3D));
        model->indices = malloc(model->numIndices * sizeof(oxIndex));

        if (model->meshVertices)
            // Read vertices from file.
            fread(&(model->meshVertices)[0], sizeof(oxVertex3D), model->numMeshVertices, modelFile);
        else debug_err("Error allocating mesh vertices memory.\n");

        if (model->texVertices)
            // Read vertices from file.
            fread(&(model->texVertices)[0], sizeof(oxVertex2D), model->numTexVertices, modelFile);
        else
            debug_err("Error allocating tex vertices memory.\n");

        if (model->normVertices)
            // Read vertices from file.
            fread(&(model->normVertices)[0], sizeof(oxVertex3D), model->numNormVertices, modelFile);
        else
            debug_err("Error allocating norm vertices memory.\n");

        if (model->indices)
            // Read indices from file.
            fread(&(model->indices)[0], sizeof(oxIndex), model->numIndices, modelFile);
        else
            debug_err("Error allocating indices memory.\n");
    }
    else
        debug_err("File not found.\n");

    model->material = OX_DEFAULT_MATERIAL;

    fclose(modelFile);
}

void oxLoadStaticModel_Custom(oxModel* model, oxStaticModelLoader loader, const char* path)
{
    loader(model, path);
}

void oxUseModelRenderProps(oxModel* model)
{
    // Use this model's material.
    if (model->material)
    {
        glMaterialf(GL_DIFFUSE, model->material->diffuse);
        glMaterialf(GL_AMBIENT, model->material->ambient);
        glMaterialf(GL_SPECULAR, model->material->specular);
        glMaterialf(GL_EMISSION, model->material->emission);
    }
}

void oxDrawIndex(oxModel* model, u32 index)
{
    // Vertex[Index[Index #]]
    glNormal(NORMAL_PACK(model->normVertices[model->indices[index].norm].x,
                         model->normVertices[model->indices[index].norm].y,
                         model->normVertices[model->indices[index].norm].z));
    glVertex3v16(model->meshVertices[model->indices[index].mesh].x,
                 model->meshVertices[model->indices[index].mesh].y,
                 model->meshVertices[model->indices[index].mesh].z);
}

void oxDrawModelTris(oxModel* model)
{
    oxUseModelRenderProps(model);

    glBegin(GL_TRIANGLES);

    for (u32 index = 0; index < model->numIndices; index++)
        oxDrawIndex(model, index);

    glEnd();
}