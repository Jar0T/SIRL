#include "Vector2D.h"
#include <iostream>

#pragma region constructors_destructors
Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
	//std::cout << "Vector 2D created (0,0) constructor" << std::endl;
}

Vector2D::Vector2D(float xp, float yp) {
	x = xp;
	y = yp;
	//std::cout << "Vector 2D created (x,y) constructor" << std::endl;
}

Vector2D::~Vector2D() {}
#pragma endregion

#pragma region operations
Vector2D& Vector2D::add(const Vector2D& v2) {
	this->x += v2.x;
	this->y += v2.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& v2) {
	this->x -= v2.x;
	this->y -= v2.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& v2) {
	this->x *= v2.x;
	this->y *= v2.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& v2) {
	this->x /= v2.x;
	this->y /= v2.y;

	return *this;
}
#pragma endregion

#pragma region operators_overloading
Vector2D& Vector2D::operator+(const Vector2D& v2) {
	return this->add(v2);
}

Vector2D& Vector2D::operator-(const Vector2D& v2) {
	return this->subtract(v2);
}

Vector2D& Vector2D::operator*(const Vector2D& v2) {
	return this->multiply(v2);
}

Vector2D& Vector2D::operator/(const Vector2D& v2) {
	return this->divide(v2);
}

Vector2D& Vector2D::operator=(const Vector2D& v2) {
	this->x = v2.x;
	this->y = v2.y;
	return *this;
}
#pragma endregion

#pragma region operations_overloading_=
Vector2D& Vector2D::operator+=(const Vector2D& v2) {
	return this->add(v2);
}

Vector2D& Vector2D::operator-=(const Vector2D& v2) {
	return this->subtract(v2);
}

Vector2D& Vector2D::operator*=(const Vector2D& v2) {
	return this->multiply(v2);
}

Vector2D& Vector2D::operator/=(const Vector2D& v2) {
	return this->divide(v2);
}
#pragma endregion

#pragma region operations_(int)
Vector2D Vector2D::operator+(int x) {
	Vector2D temp;
	temp.x = this->x + x;
	temp.y = this->y + x;

	return temp;
}

Vector2D Vector2D::operator-(int x) {
	Vector2D temp;
	temp.x = this->x - x;
	temp.y = this->y - x;

	return temp;
}

Vector2D Vector2D::operator*(int x) {
	Vector2D temp;
	temp.x = this->x * x;
	temp.y = this->y * x;

	return temp;
}

Vector2D Vector2D::operator/(int x) {
	Vector2D temp;
	temp.x = this->x / x;
	temp.y = this->y / x;

	return temp;
}
#pragma endregion