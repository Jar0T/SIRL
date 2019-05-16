#pragma once

class Vector2D {
private:

public:
	float x;
	float y;

	Vector2D();
	Vector2D(float, float);
	~Vector2D();

	Vector2D& add(const Vector2D&);
	Vector2D& subtract(const Vector2D&);
	Vector2D& multiply(const Vector2D&);
	Vector2D& divide(const Vector2D&);

	Vector2D& operator+(const Vector2D&);
	Vector2D& operator-(const Vector2D&);
	Vector2D& operator*(const Vector2D&);
	Vector2D& operator/(const Vector2D&);
	Vector2D& operator=(const Vector2D&);

	Vector2D& operator+=(const Vector2D&);
	Vector2D& operator-=(const Vector2D&);
	Vector2D& operator*=(const Vector2D&);
	Vector2D& operator/=(const Vector2D&);

	Vector2D operator+(int);
	Vector2D operator-(int);
	Vector2D operator*(int);
	Vector2D operator/(int);

};