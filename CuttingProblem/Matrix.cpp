#include "Matrix.h"


Matrix3F& Matrix3F::operator=( const Matrix3F& m)
{
	m_tMatrix[0][0] = m.m_tMatrix[0][0]; m_tMatrix[0][1] = m.m_tMatrix[0][1]; m_tMatrix[0][2] = m.m_tMatrix[0][2];
	m_tMatrix[1][0] = m.m_tMatrix[1][0]; m_tMatrix[1][1] = m.m_tMatrix[1][1]; m_tMatrix[1][2] = m.m_tMatrix[1][2];
	m_tMatrix[2][0] = m.m_tMatrix[2][0]; m_tMatrix[2][1] = m.m_tMatrix[2][1]; m_tMatrix[2][2] = m.m_tMatrix[2][2];
	return *this;
}


Matrix3F& Matrix3F::operator*( const Matrix3F& m)
{
	const int N = 3;
	float resMatix[N][N];

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			resMatix[i][j] = 0;
			for(int k = 0; k < N; k++)
				resMatix[i][j] += m_tMatrix[i][k] * m.m_tMatrix[k][j];
		}
	}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			m_tMatrix[i][j] = resMatix[i][j];
	return *this;
}


Matrix3F::Matrix3F( const Matrix3F& m)
{
	m_tMatrix[0][0] = m.m_tMatrix[0][0]; m_tMatrix[0][1] = m.m_tMatrix[0][1]; m_tMatrix[0][2] = m.m_tMatrix[0][2];
	m_tMatrix[1][0] = m.m_tMatrix[1][0]; m_tMatrix[1][1] = m.m_tMatrix[1][1]; m_tMatrix[1][2] = m.m_tMatrix[1][2];
	m_tMatrix[2][0] = m.m_tMatrix[2][0]; m_tMatrix[2][1] = m.m_tMatrix[2][1]; m_tMatrix[2][2] = m.m_tMatrix[2][2];
}


void Matrix3F::ResetRotation()
{
	m_tMatrix[0][0] = 1; m_tMatrix[0][1] = 0;
	m_tMatrix[1][0] = 0; m_tMatrix[1][1] = 1;
}


Matrix3F::Matrix3F()
{
	m_tMatrix[0][0] = 1; m_tMatrix[0][1] = 0; m_tMatrix[0][2] = 0;
	m_tMatrix[1][0] = 0; m_tMatrix[1][1] = 1; m_tMatrix[1][2] = 0;
	m_tMatrix[2][0] = 0; m_tMatrix[2][1] = 0; m_tMatrix[2][2] = 1;
}


Vector2F     Matrix3F::Multiply(const Vector2F& vec) const
{
	return Vector2F(
		m_tMatrix[0][0] * vec.X() + m_tMatrix[0][1] * vec.Y() + m_tMatrix[0][2] * 1,
		m_tMatrix[1][0] * vec.X() + m_tMatrix[1][1] * vec.Y() + m_tMatrix[1][2] * 1);
}


void     Matrix3F::SetTransformation(const Vector2F& vec)
{
	m_tMatrix[0][2] = vec.X();
	m_tMatrix[1][2] = vec.Y();
}


void Matrix3F::AddTransformation( const Vector2F& vec )
{
	m_tMatrix[0][2] += vec.X();
	m_tMatrix[1][2] += vec.Y();
}



void Matrix3F::SetRotate( float a )
{
	float cosa = cos(a);
	float sina = sin(a);
	float tx = m_tMatrix[0][2];
	float ty = m_tMatrix[1][2];
	m_tMatrix[0][0] = cosa;    m_tMatrix[0][1] = -sina; m_tMatrix[0][2] = tx * (1 - cosa) + ty * sina;
	m_tMatrix[1][0] = sina;   m_tMatrix[1][1] =  cosa; m_tMatrix[1][2] = ty * (1 - cosa) - tx * sina;
}