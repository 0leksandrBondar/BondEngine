#pragma once

#include "noncopyable.h"

#include <memory>

namespace BondEngine
{
    template <class T>
    class Singleton : public NonCopyable
    {
    public:
        static T* getInstance()
        {
            static std::unique_ptr<T> instance;
            if (instance == nullptr)
            {
                instance = std::unique_ptr<T>(new T);
            }
            return instance.get();
        }
    };
} // namespace BondEngine