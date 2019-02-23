
#ifndef VECT_H
#define VECT_H
//vect.h
//Jackson Rushing
//February 16th 2016
#include <math.h>
#define pi 3.1415926535837932

template <typename T>
class vect
{
public:
	//CONSTRUCTORS:
	vect();							//default, initialises to zero
	vect(T, T);			//takes 2 Ts, x and y
	//MATH FUNCTIONS
	T dotProduct(vect<T> &);		//takes another vector, returns the angle between the 2 vectors, in degrees. 
	vect project(vect<T> &);		//takes another vector, returns the projected vector. eg: b.project(a) projects a onto b. 
	T magnitude();				//returns the magnitude of the vector magnitude() is called on.
	vect normalize();				//returns the normalized vector(unit vector) of the vector normalize() is called on.
	vect reduce(double);			//returns a vector of the same direction with a given reduced magnitude.
	//OPERATOR OVERLOADS
	vect operator*(double operand); //multiplies a vector by a double
	vect operator+(vect<T>  operand);	//self explanitory, adds 2 vectors
	vect operator=(vect<T>  operand);	//self explanitory, adds 2 vectors
	vect operator-(vect<T>  operand);	//self explanitory, subtracts 2 vectors
	vect operator+=(vect<T>  operand);	//self explanitory,	compound addition of a vector	

	//MUTATORS
	void setx(T);					//sets the x component of the vector
	void sety(T);					//sets the y component of the vector
	//ACCESSORS
	T getx() const;			//returns the x component of the vector
	T gety() const;			//returns the x component of the vector
	T* getxp() ;			//returns the x component of the vector
	T* getyp() ;
	T getx(bool) const;			//returns the x component of the vector
	T gety(bool) const;			//returns the x component of the vector
	//PRIVATE MEMBERS
private:
	T x, y;					//x and y components of the vector
};


template <typename T>
vect<T>::vect() : x(0), y(0) {}

template <typename T>
vect<T>::vect(T _x, T _y) : x(_x), y(_y) {}

template <typename T>
T vect<T>::dotProduct(vect & vect2)
{
	return ((this->x * vect2.x) + (this->y * vect2.y));
}

template <typename T>
T vect<T>::magnitude()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

template <typename T>
vect<T> vect<T>::operator+(vect operand)
{
	vect<T> result;
	result.x = this->getx() + operand.getx();
	result.y = this->gety() + operand.gety();
	return result;
}

template <typename T>
vect<T> vect<T>::operator-(vect operand)
{
	vect<T> result;
	result.x = this->getx() - operand.getx();
	result.y = this->gety() - operand.gety();
	return result;
}

template <typename T>
vect<T> vect<T>::operator+=(vect operand)
{

	x = this->getx() + operand.getx();
	y = this->gety() + operand.gety();
	return *this;
}
template <typename T>
vect<T> vect<T>::operator*(double operand)
{
	vect<T> result((this->getx() * operand), (this->gety() * operand));
	return result;
}

template <typename T>
vect<T> vect<T>::normalize()
{
	vect<T> temp;
	T tempmagnitude = this->magnitude();
	temp.x = this->x / tempmagnitude;
	temp.y = this->y / tempmagnitude;
	return temp;
}

template <typename T>
void vect<T>::setx(T _x)
{
	this->x = _x;
}

template <typename T>
void vect<T>::sety(T _y)
{
	this->y = _y;
}

template <typename T>
T vect<T>::getx() const
{
	return this->x;
}

template <typename T>
T vect<T>::gety() const
{
	return this->y;
}

template <typename T>
T* vect<T>::getxp() 
{
	return &this->x;
}

template <typename T>
T* vect<T>::getyp() 
{
	return &this->y;
}



template <typename T>
T vect<T>::getx(bool normal) const
{
	if (normal == false)
		return this->x;
	else
	{
		if (this->x > 0)
			return this->x;
		else
			return this->x*-1;
	}
}

template <typename T>
T vect<T>::gety(bool normal) const
{
	if (normal == false)
		return this->y;
	else
	{
		if (this->y > 0)
			return this->y;
		else
			return this->y*-1;
	}
}

template <typename T>
vect<T> vect<T>::reduce(double newmag)
{
	vect<T> result;
	vect<T> unitvect = this->normalize();
	result = unitvect * newmag;
	return result;
}

template <typename T>
vect<T> vect<T>::project(vect<T> & vect2)
{

	//proj.x = (dp / (b.x*b.x + b.y*b.y)) * b.x;
	//proj.y = (dp / (b.x*b.x + b.y*b.y)) * b.y;
	vect<T> result;
	double dotProduct = this->dotProduct(vect2);
	double magnitude = (this->x*this->x + this->y*this->y);
	result.setx((dotProduct / magnitude) * this->x);
	result.sety((dotProduct / magnitude) * this->y);
	return result;
}



template <typename T>
vect<T> vect<T>::operator=(vect<T>  operand)
{
	this->x = operand.x;
	this->y = operand.y;
	return *this;
}

#endif