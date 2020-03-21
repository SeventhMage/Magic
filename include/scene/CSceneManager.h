#ifndef _MAGIC_SCENE_ISCENEMANAGER_H_
#define _MAGIC_SCENE_ISCENEMANAGER_H_

#include "CScene.h"
#include "render/IRenderer.h"
namespace magic
{
class CSceneManager
{
public:
    CSceneManager();
    ~CSceneManager();
    CScene *LoadScene(const char *fileName);
    void UnloadScene(CScene *);
    void Update(int delta);
    void FixedUpdate(int delta);
    /**
     *Submit scene data to IRenderer.
     *Different material submit to different IRenderQueue. 
     **/
    void Render();

private:
    CScene *m_pScene;
};
} // namespace magic

#endif