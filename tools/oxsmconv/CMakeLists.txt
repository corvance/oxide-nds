# ┌────────────────────────────────────────────────────────────────────────────┐
# |                                                                            |
# |   ██████╗ ██╗  ██╗██╗██████╗ ███████╗███╗   ██╗██████╗ ███████╗            |
# |  ██╔═══██╗╚██╗██╔╝██║██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝            |
# |  ██║   ██║ ╚███╔╝ ██║██║  ██║█████╗  ██╔██╗ ██║██║  ██║███████╗            |
# |  ██║   ██║ ██╔██╗ ██║██║  ██║██╔══╝  ██║╚██╗██║██║  ██║╚════██║            |
# |  ╚██████╔╝██╔╝ ██╗██║██████╔╝███████╗██║ ╚████║██████╔╝███████║            |
# |   ╚═════╝ ╚═╝  ╚═╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝            |
# |                                                                            |
# |  OxideNDS - A 2D + 3D Game/Application Engine for the Nintendo DS (NTR),   |
# |  built on devkitARM and libnds.                                            |
# |                                                                            |
# |  Copyright (C) 2022 - 2022 Conaer Macpherson a.k.a Corvance                |
# |  OxideNDS is licensed under the terms of the MIT License.                  |
# |                                                                            |
# |  If you discover any bugs, issues or room for improvement, open an issue.  |
# |                                                                            |
# |  https://www.github.com/corvance/oxide-nds                                 |
# |                                                                            |
# └────────────────────────────────────────────────────────────────────────────┘

#####################################
# file: CMakeLists.txt              #
# author: Corvance                  #
# brief: oxsmconv CMakeLists.txt    #
# version 0.1                       #
# date 2022-02-24                   #
#####################################

cmake_minimum_required(VERSION 3.0.0)
project(oxsmconv VERSION 0.1.0)

set(CXX_STANDARD 11)

include_directories(../common-includes)

add_executable(oxsmconv
    src/Main.cpp

    # Converters
    src/OBJ.h
)