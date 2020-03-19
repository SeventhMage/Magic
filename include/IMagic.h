#ifndef _MAGIC_IMAGIC_H_
#define _MAGIC_IMAGIC_H_

#include "scene/ISceneManager.h"
#include "render/IRenderer.h"

namespace magic
{
class IMagic
{
public:
    virtual bool InitEngine() = 0;
    virtual void StartApplication() = 0;
    virtual void SetFPS(int fps) = 0;
    virtual int GetFPS() const = 0;
    virtual ISceneManager *GetSceneManager() const = 0;
    virtual IRenderer *GetRenderer() const = 0;
};
}

#endif