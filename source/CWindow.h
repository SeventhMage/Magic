#ifndef _MAGIC_C_WINDOW_H_
#define _MAGIC_C_WINDOW_H_

namespace magic
{
	class CWindow
	{
	public:
		CWindow(int width, int height, bool isFullscreen);
		void OnSize(int width, int height);
	};
}

#endif
