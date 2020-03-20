#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "IComponent.h"

namespace magic
{
class CCamera : public IComponent
{
public:
    CCamera();
    ~CCamera();
};

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

} // namespace magic

#endif