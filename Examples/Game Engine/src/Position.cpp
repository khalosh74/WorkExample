#include "Position.h"

namespace gui {
	Position::Position(int x, int y) : x(x), y(y)
	{
	}

	Position::Position(const Position& p) : x(p.x), y(p.y)
	{
	}


}