#ifndef SIZE_H
#define SIZE_H

namespace gui {
	class Size {
	public:
		Size(int w, int h);
		Size(const Size&);
		int w, h;
	};
}


#endif // !SIZE_H
