#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector2F.h"

#include <cmath>

class Matrix3F
{
public:
    Matrix3F();
    ~Matrix3F() {}
    Matrix3F(const Matrix3F&);
    Matrix3F& operator=(const Matrix3F&);

    Vector2F		Multiply(const Vector2F&) const;
    void            SetTransformation(const Vector2F& vec);
    void            AddTransformation(const Vector2F& vec);
    void            SetRotate(float angle);

    void            ResetRotation();

    Vector2F     t() const { return Vector2F(m_tMatrix[0][2], m_tMatrix[1][2]); }
                                                    
    Matrix3F&        operator*(const Matrix3F&);
private:
    float   m_tMatrix[3][3];
};

#endif