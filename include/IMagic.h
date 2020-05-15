#ifndef _MAGIC_IMAGIC_H_
#define _MAGIC_IMAGIC_H_

#include "scene/ISceneManager.h"
#include "render/IRenderer.h"
#include "resource/IResourceManager.h"
#include "ITime.h"

#include <functional>

namespace magic
{
class IMagic
{
public:
    virtual ~IMagic() {}
    virtual void Run(std::function<void()> fcall = nullptr) = 0;
    virtual void SetFPS(int fps) = 0;
    virtual int GetFPS() const = 0;
    virtual ISceneManager *GetSceneManager() const = 0;
    virtual IRenderer *GetRenderer() const = 0;
    virtual IResourceManager *GetResourceManager() const = 0;
    virtual ITime *GetTime() const = 0;
};
}

#endif
