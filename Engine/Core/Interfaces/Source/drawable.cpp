#include "drawable.h"

#include "resourcemanager.h"
#include "shaderprogram.h"

namespace BondEngine
{

    Drawable::Drawable() { initDefaultShaderProgram(); }

    void Drawable::setShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram)
    {
        _shaderProgram = shaderProgram;
    }

    void Drawable::initDefaultShaderProgram()
    {
        _shaderProgram = ResourceManager::getInstance()->getShaderProgram("DefaultShaderProgram");
    }
} // namespace BondEngine