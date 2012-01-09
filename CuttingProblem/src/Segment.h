#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include "Vector2F.h"

class Segment
{
private:
	Vector2F _a, _b;

public:
	Segment(const Vector2F &start, const Vector2F &end);
	Segment(const Segment&);
	~Segment();

	Segment& operator=(const Segment&);

	const Vector2F& start() const;
	const Vector2F& end() const;

	Vector2F& start() { return _a; }
	Vector2F& end()  { return _b; }

	double length () const;
	double distance (const Vector2F&) const;
	bool inside(const Vector2F& ) const;
	//bool inLine (const Vector2F& c) const;
};

#endif