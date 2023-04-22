#ifndef BOUNDINGBOX_H
# define BOUNDINGBOX_H

class BoundingBox
{
	public:
		int x, y, w, h;
		bool belong_to(int x, int y);

		BoundingBox(int x, int y, int w, int h);
};

#endif