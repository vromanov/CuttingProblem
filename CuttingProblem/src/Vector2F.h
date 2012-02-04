#pragma once

class Vector2F
{
public:
	Vector2F(float x = 0, float y = 0) : m_fX(x), m_fY(y) { return; }
	~Vector2F() { return;}

	// getters
	inline const float& X() const { return m_fX; }
	inline const float& Y() const { return m_fY; }

	// setters
	inline float& X() { return m_fX; }
	inline float& Y() { return m_fY; }

	const Vector2F operator- (const Vector2F& v) const { return Vector2F(X() - v.X(), Y() - v.Y()); }
	const Vector2F operator+ (const Vector2F& v) const { return Vector2F(X() + v.X(), Y() + v.Y()); }
	const Vector2F operator* (const float& v) const { return Vector2F(X() * v, Y() * v); }

	bool operator<( const Vector2F& v ) const { return (X() <= v.X() && Y() <= v.Y()); }
	bool operator>( const Vector2F& v ) const { return (X() >= v.X() && Y() >= v.Y()); }

	bool operator==(const Vector2F& v) const { return (X() == v.X() && Y() == v.Y()); }
	bool operator!=(const Vector2F& v) const { return !(*this == v); }

private:
	float m_fX, m_fY;
};