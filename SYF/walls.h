#ifndef WALLS_H
#define WALLS_H
struct wall
{
	wall(float _rX, float _tY, float _lX, float _bY){ rX = _rX; tY = _tY; lX = _lX;  bY = _bY; }
	float rX;//right x value
	float lX;//left x value
	float tY;//top y value
	float bY;//bottom y value

#endif