#pragma once

#include <vector>

class RectangleF;

class RectangleDB
{
public:
	RectangleDB();
	~RectangleDB();
	RectangleDB(const RectangleDB&);
	const RectangleDB& operator=(const RectangleDB&);

	const RectangleF*	operator[](const size_t index) const { return m_db[index]; }
	RectangleF*	operator[](const size_t index) { return m_db[index]; }

	const int			Size() const { return m_db.size(); }
	void				Clear();
private:
	std::vector<RectangleF*> m_db;
};