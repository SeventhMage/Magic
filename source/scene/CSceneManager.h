#ifndef _MAGIC_C_SCENE_MANAGER_H_
#define _MAGIC_C_SCENE_MANAGER_H_

#include "../../include/scene/ISceneManager.h"

namespace magic
{
class CSceneManager : public ISceneManager
{
public:
    virtual IScene *LoadScene(const char *fileName) { return nullptr; }
    virtual void UnloadScene(IScene *){}
    virtual void Update(int delta){}
    virtual void FixUpdate(int delta){}
    virtual void Render(IRenderer *){}

};
}

#endif