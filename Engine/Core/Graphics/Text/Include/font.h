// MIT License
//
// Copyright (c) 2024 Oleksandr
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "glm/vec2.hpp"
#include "texture2D.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <filesystem>
#include <unordered_map>

namespace BondEngine
{
    struct Character
    {
        Texture2D* Texture;   // ID handle of the glyph texture
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance; // Horizontal offset to advance to next glyph
    };

    class Font final
    {
    public:
        Font() = default;
        explicit Font(const std::filesystem::path& path, unsigned int size = 12);

        [[nodiscard]] std::unordered_map<char, Character>& getCharacters() { return _characters; };

    private:
        void loadCharacters();

    private:
        FT_Face _face{};
        std::unordered_map<char, Character> _characters;
    };
} // namespace BondEngine