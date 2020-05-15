#ifndef _MAGIC_CMAGIC_H_
#define _MAGIC_CMAGIC_H_

#include "IMagic.h"
#include "base/CSingleton.h"
#include "CApplication.h"
#include "render/SRenderContext.h"
#include "CTime.h"

namespace magic
{
class CMagic : public IMagic
{
public:
    CMagic(SRenderContext *context, const char *title, int width, int height);
    ~CMagic();
    
    virtual void Run(std::function<void()> fcall = nullptr);
    virtual void SetFPS(int fps);
    virtual int GetFPS() const {return m_iFPS;}

    virtual ISceneManager *GetSceneManager() const { return m_pSceneManager; }
    virtual IRenderer *GetRenderer() const { return m_pRenderer; }
    virtual IResourceManager *GetResourceManager() const { return m_pResourceManager; }
    virtual ITime *GetTime() const { return m_pTime; }
private:
    CApplication *m_pApplication;
    int m_iFPS;
    int m_iFixDelta;

    ISceneManager *m_pSceneManager;
    IRenderer *m_pRenderer;
    IResourceManager *m_pResourceManager;
    CTime *m_pTime;
};
}

#endif
