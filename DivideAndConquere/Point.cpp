#include <Point.h>
#include <math.h>
#include <iostream>

Point::Point(){
	x = 0;
	y = 0;
}

Point::Point(char iName, float iX, float iY){
	name = iName;
	x = iX;
	y = iY;
}

Point* makeRandomPoint(float max){
	Point* point = new Point();
	point->x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	point->y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	return point;
}


float Point::distanceBetweenPoints(Point* p1, Point* p2){
	float dist = sqrtf((p1->x - p2->x)*(p1->x - p2->x) + (p1->y - p2->y)*(p1->y - p2->y));
	//std::cout << "distance between " << p1->name << " and " << p2->name << " is : " << dist << std::endl;
	return dist;
}

