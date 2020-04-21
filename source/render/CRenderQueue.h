#ifndef _MAGIC_C_RENDERQUEUE_H_
#define _MAGIC_C_RENDERQUEUE_H_

#include "render/IRenderInput.h"

#include <vector>

namespace magic
{
class CRenderQueue
{
public:
    CRenderQueue();
    ~CRenderQueue();
    
    void AddRenderInput(IRenderInput *pRenderInput);
    void Clear();
private:
    std::vector<IRenderInput *> m_Queue;
};
}

#endif
