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

#include "font.h"
#include <iostream>

#include "freetypelib.h"

namespace BondEngine
{
    Font::Font(const std::filesystem::path& path, unsigned int size)
    {
        if (const FT_Library& ft = FreeTypeLibrary::getInstance()->getFreeTypeLib();
            FT_New_Face(ft, path.string().c_str(), 0, &_face))
            throw std::runtime_error("Failed to load font");
        else
            std::cout << "Successfully loaded font " << path.string() << std::endl;

        FT_Set_Pixel_Sizes(_face, 0, size);
        loadCharacters();
    }

    void Font::loadCharacters()
    {
        FT_Set_Pixel_Sizes(_face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            auto* glyphTexture
                = new Texture2D(_face->glyph->bitmap.width, _face->glyph->bitmap.rows,
                                _face->glyph->bitmap.buffer, 1);

            Character characterTexture{};
            characterTexture.Texture = glyphTexture;
            characterTexture.Advance = static_cast<unsigned int>(_face->glyph->advance.x);
            characterTexture.Bearing
                = glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top);

            _characters[c] = characterTexture;
        }
    }
} // namespace BondEngine