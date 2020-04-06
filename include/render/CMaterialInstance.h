#ifndef _MAGIC_C_MATERIAL_INSTANCE_H_
#define _MAGIC_C_MATERIAL_INSTANCE_H_

#include "IObject.h"
#include "resource/IMaterial.h"
#include "render/IShaderProgram.h"
#include "render/IRenderer.h"

namespace magic
{
class CMaterialInstance : public IObject
{
public:
    CMaterialInstance();
    ~CMaterialInstance();

    void Initialize(IRenderer *pRenderer, IMaterial *pMaterial);
    IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }

private:
    IShaderProgram *m_pShaderProgram;
    IMaterial *m_pMaterial;
};
} // namespace magic

#endif
