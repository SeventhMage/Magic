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
};

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

} // namespace magic

#endif