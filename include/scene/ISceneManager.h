#ifndef _MAGIC_SCENE_ISCENEMANAGER_H_
#define _MAGIC_SCENE_ISCENEMANAGER_H_

#include "IScene.h"
#include "../render/IRenderer.h"
namespace magic
{
class ISceneManager
{
public:
    virtual IScene *LoadScene(const char *fileName) = 0;
    virtual void UnloadScene(IScene *) = 0;
    virtual void Update(int delta) = 0;
    virtual void FixUpdate(int delta) = 0;
    /**
     *Submit scene data to IRenderer.
     *Different material submit to different IRenderQueue. 
     **/
    virtual void Render(IRenderer *) = 0;
};
}

#endif