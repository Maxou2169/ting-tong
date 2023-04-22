#include "includes/boundingbox.h"

BoundingBox::BoundingBox(int x, int y, int w, int h)
: x(x), y(y), w(w), h(h) {}

bool BoundingBox::belong_to(int x, int y)
{
	return (
		(x >= this->x) && (x <= (this->x + this->w)) &&
		(y >= this->y) && (y <= (this->y + this->h))
	);
}