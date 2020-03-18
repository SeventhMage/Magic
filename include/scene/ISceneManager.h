#ifndef _MAGIC_SCENE_ISCENEMANAGER_H_
#define _MAGIC_SCENE_ISCENEMANAGER_H_

#include "IScene.h"

namespace magic
{
class ISceneManager
{
public:
    virtual IScene *LoadScene(const char *fileName) = 0;
    virtual void UnloadScene(IScene *) = 0;
    virtual void Update(int delta) = 0;
    virtual void FixUpdate(int delta) = 0;
    virtual void Render() = 0;
};
}

#endif