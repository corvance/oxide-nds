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
 * @file Main.cpp
 * @author Corvance
 * @brief oxsmconv Main file, parses arguments.
 * @version 0.1
 * @date 2022-02-24
 */

#include <string>
#include <cxxopts.hpp>
#include <oxtool_log.h>

#include "OBJ.h"

typedef struct
{
    bool success;
    cxxopts::ParseResult parsed;
} ParseArgsResult;

ParseArgsResult parse_args(int argc, const char *argv[])
{
    ParseArgsResult result;
    result.success = true;

    try
    {
        cxxopts::Options options("oxsmconv", "Converter utility to convert common 3D model formats to OXide Static Model .oxsm format.");

        options.add_options("Flags")("h,help", "Print help");
        options.add_options("File Arguments")("i,input", "Input model file (positional)", cxxopts::value<std::string>())("o,output", "Output OXSM file (positional)", cxxopts::value<std::string>());
        options.add_options("Arguments")("f,format", "Input model format", cxxopts::value<std::string>());

        options
            .positional_help("File Arguments")
            .show_positional_help();
        options.allow_unrecognised_options();

        options.parse_positional("input", "output");

        result.parsed = options.parse(argc, argv);

        if (result.parsed.count("help"))
        {
            printf("%s\n", options.help({"Flags", "File Arguments", "Arguments"}).c_str());
            // Exit early but successfully.
            exit(0);
        }
        if (!result.parsed.count("input"))
        {
            log_err("No input file provided.\n");
            result.success = false;
        }
        if (!result.parsed.count("output"))
        {
            log_err("No output filepath provided.\n");
            result.success = false;
        }
        if (!result.parsed.count("format"))
        {
            log_err("Input model format not specified.\n");
            result.success = false;
        }
        else
        {
            std::vector<std::string> validFormats = {"obj"};
            std::string format = StringUtils::toLowerCase(result.parsed["f"].as<std::string>());
            if (std::find(validFormats.begin(), validFormats.end(), format) == validFormats.end())
            {
                log_err("Invalid input format provided.\n");
                result.success = false;
            }
        }
    }
    catch (cxxopts::OptionException &e)
    {
        log_err("Error parsing options. Did you do -a/--argument but fail to provide a prameter?\n");
    }

    return result;
}

int main(int argc, const char *argv[])
{
    bool success = false;

    ParseArgsResult result = parse_args(argc, argv);

    if (result.success)
    {
        if (StringUtils::toLowerCase(result.parsed["f"].as<std::string>()) == "obj")
            success = OBJConv::convert(result.parsed["i"].as<std::string>(), result.parsed["o"].as<std::string>());
    }

    exit(success ? 0 : 1);
}