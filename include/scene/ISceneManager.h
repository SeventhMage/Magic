#ifndef _MAGIC_I_SCENE_MANAGER_H_
#define _MAGIC_I_SCENE_MANAGER_H_

#include "IScene.h"

namespace magic
{
class ISceneManager
{
public:
    virtual ~ISceneManager(){}
    virtual IScene *LoadScene() = 0;
    virtual IScene *LoadScene(const char *fileName) = 0;
    virtual void UnloadScene() = 0;
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
};
}

#endif
