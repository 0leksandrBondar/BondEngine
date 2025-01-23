#pragma once

namespace BondEngine
{
    class Updatable
    {
    public:
        Updatable() = default;
        virtual ~Updatable() = default;

        virtual void update() = 0;
    };
} // namespace BondEngine
