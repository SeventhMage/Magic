#include "CMagic.h"
#include "scene/CSceneManager.h"
#include "render/gles3/CGLES3Renderer.h"

namespace magic
{
CMagic::CMagic(void *context, const char *title, int width, int height, unsigned int flags)
:m_pApplication(new CApplication())
{
    m_pSceneManager = new CSceneManager();
    m_pRenderer = new CGLES3Renderer(context, title, width, height, flags);
}

CMagic::~CMagic()
{
    if (m_pApplication)
        delete m_pApplication;
    if (m_pRenderer)
        delete m_pRenderer;
}

bool CMagic::InitEngine()
{
    return true;   
}

void CMagic::StartApplication()
{
    while (m_pApplication->Run())
    {
        static long lastTime = m_pApplication->GetSystemTime();
        static long compensationTime = 0;
        long passTime = m_pApplication->GetSystemTime() - lastTime;
        if (passTime >= m_iFixDelta)
        {
            m_pSceneManager->Update();
            compensationTime += passTime;
            do
            {
                //m_pSceneManager->FixedUpdate(m_iFixDelta);
                compensationTime -= m_iFixDelta;
            }while(compensationTime > m_iFixDelta);

            //m_pSceneManager->Render();
            lastTime = m_pApplication->GetSystemTime();
        }
    }
}

void CMagic::SetFPS(int fps)
{
    m_iFPS = fps;
    if (m_iFPS > 0)
    {
        m_iFixDelta = 1000 / m_iFPS;
    }
}

} // namespace magic
