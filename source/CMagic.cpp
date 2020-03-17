#include "CMagic.h"

namespace magic
{
CMagic::CMagic()
{
    
}

CMagic::~CMagic()
{

}

bool CMagic::InitEngine()
{
    
}

bool CMagic::StartApplication()
{
    while (m_pApplication->Run())
    {
        static long lastTime = m_pApplication->GetSystemTime();
        static long compensationTime = 0;
        long passTime = m_pApplication->GetSystemTime() - lastTime;
        if (passTime >= m_iFixDelta)
        {
            m_pSceneManager->Update(passTime);
            compensationTime += passTime;
            do
            {
                m_pSceneManager->FixUpdate(m_iFixDelta);
                compensationTime -= m_iFixDelta;
            }while(compensationTime > m_iFixDelta);

            m_pSceneManager->Render();
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