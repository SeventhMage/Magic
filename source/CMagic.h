#ifndef _MAGIC_CMAGIC_H_
#define _MAGIC_CMAGIC_H_

#include "../include/IMagic.h"
#include "../common/base/CSingleton.h"
#include "CApplication.h"
namespace magic
{
class CMagic : public IMagic, public CSingleton<CMagic>
{
public:
    virtual bool InitEngine();
    virtual void StartApplication();
    virtual void SetFPS(int fps);
    virtual int GetFPS() const {return m_iFPS;}

    virtual ISceneManager *GetSceneManager() const { return m_pSceneManager; }
    virtual IRenderer *GetRenderer() const { return m_pRenderer; }
private:
    friend class CSingleton<CMagic>;
    CMagic();
    ~CMagic();
    CApplication *m_pApplication;
    int m_iFPS;
    int m_iFixDelta;

    ISceneManager *m_pSceneManager;
    IRenderer *m_pRenderer;
};
}

#endif