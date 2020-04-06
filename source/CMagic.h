#ifndef _MAGIC_CMAGIC_H_
#define _MAGIC_CMAGIC_H_

#include "IMagic.h"
#include "base/CSingleton.h"
#include "CApplication.h"
#include "render/SRenderContent.h"

namespace magic
{
class CMagic : public IMagic
{
public:
    CMagic(SRenderContent *context, const char *title, int width, int height);
    ~CMagic();
    
    virtual void Run();
    virtual void SetFPS(int fps);
    virtual int GetFPS() const {return m_iFPS;}

    virtual ISceneManager *GetSceneManager() const { return m_pSceneManager; }
    virtual IRenderer *GetRenderer() const { return m_pRenderer; }
private:
    CApplication *m_pApplication;
    int m_iFPS;
    int m_iFixDelta;

    CSceneManager *m_pSceneManager;
    IRenderer *m_pRenderer;
};
}

#endif
