#ifndef _MAGIC_CAPPLICATION_H_
#define _MAGIC_CAPPLICATION_H_

#include "CWindow.h"
#include "../include/IApplication.h"

namespace magic
{
class CApplication : public IApplication
{
public:
	CApplication();
	virtual bool Run();
    virtual long GetSystemTime();
	CWindow *GetWindow() { return m_Window; }

private:
	CWindow *m_Window;
};
} // namespace magic

#endif