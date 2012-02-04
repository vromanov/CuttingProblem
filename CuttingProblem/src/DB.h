#pragma once

#include <vector>

class RectangleF;

class DB
{
public:
	static void	CreateDB(const char* file);
	static void	CleanDB();
	static void	CleanDB(std::vector<RectangleF*>& db);

	static void	CopyTo(std::vector<RectangleF*>& newDB);
	static void Copy(const std::vector<RectangleF*>& from, std::vector<RectangleF*>& to);

	static void WipeDB(std::vector<RectangleF*>& db);
private:
	DB();
	~DB();

	void			LoadRectangles( const char* file );
	RectangleF*		ParseLineToRectangle( std::string& line );

	static DB*					s_pDB;
	std::vector<RectangleF*>	m_pInitRectangles;
};