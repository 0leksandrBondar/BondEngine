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

namespace BondEngine
{
    /**
     * @brief A utility base class that prevents derived classes from being moveable.
     *
     * The `NonMoveable` class is designed to be inherited by other classes to disable move
     * construction and move assignment. This is useful for types where moving could lead
     * to incorrect behavior or resource management issues.
     *
     * Usage:
     * - Inherit from `NonMoveable` to automatically delete the move constructor and move
     *   assignment operator in your class.
     * - This class provides a protected default constructor and destructor, allowing derived
     *   classes to be instantiated but not moved.
     */

    class NonMoveable
    {
    protected:
        NonMoveable() = default;
        virtual ~NonMoveable() = default;

        NonMoveable(NonMoveable&&) = delete;
        NonMoveable& operator=(NonMoveable&&) = delete;
    };
} // namespace BondEngine