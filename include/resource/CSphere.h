#ifndef _MAGICX_C_SPHERE_H_
#define _MAGICX_C_SPHERE_H_

#include "CMesh.h"

namespace magic
{
class CSphere : public CMesh
{
public:
    CSphere(float fRadius, int iSlices, int iStacks);
    ~CSphere();
};
}

#endif
