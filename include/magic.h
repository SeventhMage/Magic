#ifndef _MAGIC_H_
#define _MAGIC_H_

#include "IMagic.h"
#include "base/Log.h"
#include "render/SRenderContext.h"
#include "render/ERender.h"
#include "scene/CGameObject.h"
#include "resource/CMesh.h"
#include "resource/CMaterial.h"
#include "resource/CShader.h"
#include "resource/IImage.h"
#include "component/CCameraComponent.h"
#include "component/CMeshRendererComponent.h"

namespace magic
{
IMagic *CreateMagic(SRenderContext *context, const char *title, int width, int height);
void Clean();
}

#endif
