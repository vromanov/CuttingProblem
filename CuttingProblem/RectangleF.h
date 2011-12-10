#pragma once

#include "Vector2F.h"
#include "Matrix.h"

#include <string>

class RectangleF;

enum Status
{
	FREE = 0,
	ON_FIELD,
};


class RectangleF
{
public:
	RectangleF() : eStatus(FREE) { return; }
	RectangleF(const Vector2F& minPoint, const Vector2F& maxPoint);
	~RectangleF() { return; }

	inline void				SetStatus(Status position) { eStatus = position; }
	inline Status			GetStatus() const { return eStatus; }

	void					SetPosition(const Vector2F& position);
	inline const Vector2F&	GetPosition() { return m_Position; }

	const Vector2F&			GetTopLeft() const { return m_MinPoint; }
	const Vector2F&			GetBottomRight() const { return m_MaxPoint; }

	const Vector2F&			GetDimension() const { return m_Dimension; }

private:
	Vector2F m_InitMinPoint, m_InitMaxPoint, m_Dimension;
	Vector2F m_MinPoint, m_MaxPoint, m_Position;
	Status eStatus;
};