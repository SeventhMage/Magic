#include "CMagic.h"
#include "scene/CSceneManager.h"
#include "render/gles3/CGLES3Renderer.h"
#include "resource/CResourceManager.h"
#include "base/magicDef.h"

namespace magic
{
CMagic::CMagic(SRenderContext *context, const char *title, int width, int height)
:m_pApplication(new CApplication())
,m_iMaxFPS(60)
,m_iFixDelta(16)
{
    m_pSceneManager = new CSceneManager();
    m_pResourceManager = new CResourceManager();
    m_pRenderer = new CGLES3Renderer(context, title, width, height);
    m_pTime = new CTime();
}

CMagic::~CMagic()
{
    SAFE_DEL(m_pResourceManager);
    SAFE_DEL(m_pSceneManager);
    SAFE_DEL(m_pRenderer);
    SAFE_DEL(m_pTime);
    SAFE_DEL(m_pApplication);
}

void CMagic::Run(std::function<void()> fcall)
{
    static long lastTime = m_pTime->GetSystemTime();
    static long compensationTime = 0;
    long passTime = m_pTime->GetSystemTime() - lastTime;
    if (passTime >= m_iFixDelta)
    {
        if (fcall)
            fcall();
        m_pRenderer->Render();
        m_pSceneManager->Update();
        
        m_pTime->SetDeltaTime(passTime);
        
        compensationTime += passTime;
        
        do
        {
            m_pSceneManager->FixedUpdate();
            compensationTime -= m_iFixDelta;
        } while (compensationTime > m_iFixDelta);
        lastTime = m_pTime->GetSystemTime();
    }
}

void CMagic::SetMaxFPS(int fps)
{
    m_iMaxFPS = fps;
    if (m_iMaxFPS > 0)
    {
        m_iFixDelta = 1000 / m_iMaxFPS;
    }
}

int CMagic::GetFPS() const
{
	int deltaTime = (int)m_pTime->GetDeltaTime();
	return deltaTime > 0 ? 1000 / deltaTime : 0;
}

} // namespace magic
