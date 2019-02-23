#ifndef BOX_H
#define BOX_H
struct Box
{
public:
	Box() :rX(0), lX(0), tY(0), bY(0) {};
	Box(float _rX, float _tY, float _lX, float _bY) :rX(_rX), tY(_tY), lX(_lX), bY(_bY) {};
	float rX, lX, tY, bY;
};
#endif
