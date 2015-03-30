#pragma once



template <typename T>
class Vec2
{
public:
	T x;
	T y;

public:
	Vec2(T x = 0, T y = 0);
	~Vec2();

	T length() const;
	Vec2<T> normalized() const;
	T dot(const Vec2<T>& other) const;

	Vec2<T>& operator+=(const Vec2<T>& other);
	Vec2<T>& operator-=(const Vec2<T>& other);
	Vec2<T>& operator=(const Vec2<T>& other);

	Vec2<T> operator+(const Vec2<T>& vec2);
	Vec2<T> operator-(const Vec2<T>& vec2);

	Vec2<T> operator/(T scalar);
	Vec2<T> operator*(T scalar);
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

template <typename T>
Vec2<T>::Vec2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
Vec2<T>::~Vec2()
{
}

template <typename T>
T Vec2<T>::length() const
{
	return sqrt(x * x + y * y);
}

template <typename T>
Vec2<T> Vec2<T>::normalized() const
{
	T len = length();
	return Vec2<T>(x / l, y / l);
}

template <typename T>
T Vec2<T>::dot(const Vec2<T>& other) const
{
	return (x * other.x) + (y * other.y);
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2<T>& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& other)
{
	return Vec2<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& other)
{
	return Vec2<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator/(T scalar)
{
	return Vec2<T>(this->x / scalar, this->y / scalar);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(T scalar)
{
	return Vec2<T>(this->x * scalar, this->y * scalar);
}