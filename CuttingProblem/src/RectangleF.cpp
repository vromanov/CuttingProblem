#include "RectangleF.h"

#include "Matrix.h"

void RectangleF::SetPosition( const Vector2F& position )
{
	m_Position = position;

	CalculateMinMax(position);

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

void RectangleF::Enlarge( RectangleF* pRectangle )
{
	m_Dimension = (pRectangle->m_MaxPoint - this->m_MinPoint) * 0.5f;

	Vector2F tempInitPoint;
	m_InitMinPoint = tempInitPoint - m_Dimension;
	m_InitMaxPoint = tempInitPoint + m_Dimension;

	// convert from global position to local
	pRectangle->m_Position = pRectangle->m_Position - m_Position;
	m_ConsistOf.push_back(*pRectangle);

	// get new posititon and recalculate local position
	Vector2F newPosition = (pRectangle->m_MaxPoint + this->m_MinPoint) * 0.5f;
	this->CalculateLocalPosition(newPosition - m_Position);

	// here we calculate min and max point for this rectangle and all includes
	this->SetPosition(newPosition);
}

void RectangleF::Dummy()
{
	m_InitMinPoint = m_InitMaxPoint = m_Dimension = m_MinPoint = m_MaxPoint = m_Position = Vector2F(0,0);
}

void RectangleF::CalculateLocalPosition( Vector2F newPosition )
{
	this->m_Position = newPosition;
	for (size_t i = 0, i_end = m_ConsistOf.size(); i < i_end; ++i)
	{
		m_ConsistOf[i].m_Position = m_ConsistOf[i].m_Position - newPosition;
	}
}

void RectangleF::CalculateMinMax( const Vector2F& position )
{
	Matrix3F m;
	m.SetTransformation(position);
	m_MinPoint = m.Multiply(m_InitMinPoint);
	m_MaxPoint = m.Multiply(m_InitMaxPoint);

	for (size_t i = 0, i_end = m_ConsistOf.size(); i < i_end; ++i)
	{
		m_ConsistOf[i].CalculateMinMax(position + m_ConsistOf[i].m_Position);
	}
}
