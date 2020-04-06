#ifndef _MAGIC_SCENE_ISCENEMANAGER_H_
#define _MAGIC_SCENE_ISCENEMANAGER_H_

#include "scene/ISceneManager.h"
#include "render/IRenderer.h"
namespace magic
{
class CSceneManager : public ISceneManager
{
public:
    CSceneManager();
    virtual ~CSceneManager();
    virtual IScene *LoadScene();
    virtual IScene *LoadScene(const char *fileName);
    virtual void UnloadScene();
    virtual void Update();
private:
    IScene *m_pScene;
};
} // namespace magic

#endif
