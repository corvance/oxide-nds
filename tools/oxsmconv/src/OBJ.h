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
 * @file OBJ.h
 * @author Corvance
 * @brief Wavefront OBJ -> OXSM Conversion
 * @version 0.1
 * @date 2022-02-24
 */

#pragma once

#include <fstream>
#include <string>

#include <oxtool_log.h>
#include <oxtool_stringutils.h>

#define floattot16(n) ((int16_t)((n) * (1 << 4)))
#define floattov16(n) ((int16_t)((n) * (1 << 12)))
#define floattov10(n) ((n > 0.998) ? 0x1FF : ((short int)((n)*(1<<9))))

class OBJConv
{
public:

    static bool convert(const std::string& inPath, const std::string& outPath)
    {
        // Open input OBJ as text file.
        std::ifstream objIn(inPath);

        std::vector<std::vector<int16_t>> vertices = {};
        std::vector<std::vector<int16_t>> t_vertices = {};
        std::vector<std::vector<int16_t>> n_vertices = {};
        std::vector<std::vector<uint32_t>> indices = {};

        if (objIn.is_open())
        {
            for (std::string str; std::getline(objIn, str);)
            {
                std::string elem_type = StringUtils::splitString(str, ' ')[0];
                std::vector<std::string> vals = StringUtils::splitString(str, ' ');
                vals.erase(vals.begin()); // Remove elem type to leave only the vals.

                // Mesh vertex.
                if (elem_type == "v")
                {
                    // Vertex must have 3 coordinates
                    if (vals.size() != 3)
                    {
                        log_err("Vertex has %i coordinates, should have 3.\n", vals.size());
                        return false;
                    }

                    vertices.push_back({0, 0, 0});
                    for (int v = 0; v < 3; v++)
                        vertices[vertices.size() - 1][v] = floattov16(std::stof(vals[v]));
                }
                // Texture vertex.
                else if (elem_type == "vt")
                {
                    // Texture vertex must have 2 coordinates.
                    if (vals.size() != 2)
                    {
                        log_err("Mesh vertex has %i coordinates, should have 2.\n", vals.size());
                        return false;
                    }
                    t_vertices.push_back({0, 0});
                    for (int vt = 0; vt < 2; vt++)
                        t_vertices[t_vertices.size() - 1][vt] = floattot16(std::stof(vals[vt]));
                }
                // Normal vertex.
                else if (elem_type == "vn")
                {
                    // Vertex must have 3 coordinates
                    if (vals.size() != 3)
                    {
                        log_err("Normal vertex has %i coordinates, should have 3.\n", vals.size());
                        return false;
                    }

                    n_vertices.push_back({0, 0, 0});
                    for (int vn = 0; vn < 3; vn++)
                        n_vertices[n_vertices.size() - 1][vn] = floattov10(std::stof(vals[vn]));
                }
                // Index triangle.
                else if (elem_type == "f")
                {
                    // Index must have 3 elements.
                    if (vals.size() != 3)
                    {
                        log_err("Index has %i vertices, should have 3.\n", vals.size());
                        return false;
                    }

                    std::vector<std::string> vertex_vals;
                    for (int i = 0; i < 3; i++)
                    {
                        vertex_vals = StringUtils::splitString(vals[i], '/');
                        // Triangle vertex must have 3 elements, v/vt/vn.
                        if (vertex_vals.size() != 3)
                        {
                            log_err("Index triangle vertex has %i elements, should have 3.\n", vals.size());
                            return false;
                        }
                        indices.push_back({(uint32_t)std::stoi(vertex_vals[0]) - 1, (uint32_t)std::stoi(vertex_vals[1]) - 1, (uint32_t)std::stoi(vertex_vals[2]) - 1});
                    }
                }
            }

            uint32_t header[4] = {(uint32_t)vertices.size(), (uint32_t)t_vertices.size(), (uint32_t)n_vertices.size(), (uint32_t)indices.size()};

            // Write to binary .oxsm format.
            std::ofstream out(outPath, std::ios::out | std::ios::binary);

            out.write((char*)header, sizeof(header));
            for (auto vertex: vertices)
            {
                for (int16_t elem: vertex)
                    out.write((char*)&elem, sizeof(elem));
            }
            for (auto t_vertex: t_vertices)
            {
                for (int16_t elem: t_vertex)
                    out.write((char*)&elem, sizeof(elem));
            }
            for (auto n_vertex: n_vertices)
            {
                for (int16_t elem: n_vertex)
                    out.write((char*)&elem, sizeof(elem));
            }
            for (auto index: indices)
            {
                for (uint32_t elem: index)
                    out.write((char*)&elem, sizeof(elem));
            }

            out.flush();
            out.close();
        }
        else
        {
            // File doesn't exist, incorrect access rights, already in use, etc.
            log_err("Cannot open file %s\n", inPath.c_str());
            return false;
        }

        // Conversion succeeded.
        return true;
    }
};