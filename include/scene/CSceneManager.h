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
    void Update();
private:
    CScene *m_pScene;
};
} // namespace magic

#endif