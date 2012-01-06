#include "RectangleF.h"

#include "Matrix.h"

void RectangleF::SetPosition( const Vector2F& position )
{
	m_Position = position;
	Matrix3F m;
	m.SetTransformation(m_Position);
	m_MinPoint = m.Multiply(m_InitMinPoint);
	m_MaxPoint = m.Multiply(m_InitMaxPoint);
}

RectangleF::RectangleF( const Vector2F& minPoint, const Vector2F& maxPoint ) 
: eStatus(FREE)
, m_InitMinPoint(minPoint)
, m_InitMaxPoint(maxPoint)
, m_Dimension(maxPoint)
, m_MinPoint(minPoint)
, m_MaxPoint(maxPoint)
{
	return;
}
