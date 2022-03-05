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
//------------------------------------------------------------------------------//

/**
 * @file StringUtils.h
 * @author Corvance
 * @brief A simple and convenient header-only std::string utility library for use in OxideNDS tools.
 * @version 0.1
 * @date 2022-02-24
 */

#pragma once

#include <vector>
#include <iterator>
#include <algorithm>

class StringUtils
{
public:
    /**
     * @brief A fast string-splitting function for a given string and delimiter char.
     *
     * @param original A reference to the string which will be split.
     * @param delimiter A char delimiter to split the string around.
     *
     * @return std::vector<std::string> The split string.
     */
    static std::vector<std::string> splitString(std::string const &original, char delimiter)
    {
        // Reserve a capacity equal to the number of words in the string to avoid constant resizing
        // No. of words = No. of spaces + 1 as the string is later split around places to get the vector of words
        std::vector<std::string> splitVec;

        std::string::const_iterator start = original.begin();
        std::string::const_iterator end = original.end();
        std::string::const_iterator next = std::find(start, end, delimiter);

        while (next != end)
        {
            splitVec.emplace_back(start, next);
            start = next + 1;
            next = std::find(start, end, delimiter);
        }

        splitVec.push_back(std::string(start, next));

        return splitVec;
    }

    /**
     * @brief Checks if a given string contains a search term substring.
     *
     * @param input The string to search.
     * @param term The substring to look for.
     * @return true if input contains term.
     * @return false if input does not contain term.
     */
    static bool stringContains(std::string &input, const std::string &term)
    {
        return input.find(term) != std::string::npos;
    }

    /**
     * @brief Converts a string to lowercase in-place.
     *
     * @param input A reference to the string to convert to lowercase.
     */
    static std::string toLowerCase(std::string input)
    {
        for (char &character : input)
        {
            character = std::tolower(character);
        }

        return input;
    }

    /**
     * @brief Converts a string to uppercase in-place.
     *
     * @param input A reference to the string to convert to uppercase.
     */
    static std::string toUpperCase(std::string input)
    {
        for (char &character : input)
        {
            character = std::toupper(character);
        }

        return input;
    }

    /**
     * @brief Replaces all occurences of a substring within a given string with a given replacement string, in-place.
     *
     * @param subject The string to be searched and replaced within.
     * @param search The substring to replace.
     * @param replace The string to replace the search substring with.
     */
    static void replaceStringInPlace(std::string &subject, const std::string &search, const std::string &replace)
    {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    /**
     * @brief Get the number of occurences of a substring in a string.
     *
     * @param str The string to search.
     * @param substr The substring.
     * @return int The number of occurences of substr in str.
     */
    static int getNumOccurences(std::string &str, std::string &substr)
    {
        std::vector<std::string> words = splitString(str, ' ');

        int count = 0;
        for (int i = 0; i < words.size(); i++)
        {
            count += (words[i] == substr) ? 1 : 0;
        }

        return count;
    }
};
