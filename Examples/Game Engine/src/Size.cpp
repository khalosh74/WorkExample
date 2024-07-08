#include "Size.h"

namespace gui {
	Size::Size(int w, int h) : w(w), h(h)
	{
	}

	Size::Size(const Size& s) : w(s.w), h(s.h)
	{
	}

}