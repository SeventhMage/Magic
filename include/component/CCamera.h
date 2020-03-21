#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "CComponent.h"

namespace magic
{
class CCamera : public CComponent
{
public:
    CCamera();
    ~CCamera();

    virtual void Update();
};

} // namespace magic

#endif