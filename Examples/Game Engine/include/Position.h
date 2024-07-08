#ifndef POSITION_H
#define POSITION_H

namespace gui {
	class Position {
	public:
		Position(int x, int y);
		Position(const Position&);
		int x, y;
	};
}


#endif // !POSITION_H
