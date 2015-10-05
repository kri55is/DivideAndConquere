#ifndef POINT_H
#define POINT_H

class Point {
public:
	char name;
	float x;
	float y;
	Point();
	Point(char iName, float iX, float iY);

	static float distanceBetweenPoints(Point* p1, Point* p2);
};

#endif