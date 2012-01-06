#include "DB.h"

#include "RectangleF.h"

#include "wx/wx.h"
#include "wx/thread.h"

#include <fstream>

DB::DB()
{
	return;
}

DB::~DB()
{

}

void DB::LoadRectangles( const char* file )
{
	std::ifstream dbFile(file);
	std::string line;

	if (dbFile.is_open())
	{
		while ( dbFile.good() )
		{
			getline (dbFile, line);

			s_pDB->m_pInitRectangles.push_back(s_pDB->ParseLineToRectangle(line));
		}
		dbFile.close();
	}
}

RectangleF* DB::ParseLineToRectangle( std::string& line )
{
	RectangleF* pRectangle = NULL;
	int separator_pos = 0, separator_next_pos = 0;
	while (true)
	{
		separator_next_pos = line.find(';', separator_pos);

		// if end of the line we go out
		if (separator_next_pos == -1)
			break;

		// get the format like that 'xx,xx' here
		std::string str_coord = line.substr(separator_pos + 1, separator_next_pos - separator_pos - 2);

		int coma_pos = str_coord.find(',');

		std::string str_x = str_coord.substr(0, coma_pos);
		std::string str_y = str_coord.substr(coma_pos + 1);

		float X = atof(str_x.c_str());
		float Y = atof(str_y.c_str());

		float halfX = X / 2.f;
		float halfY = Y / 2.f;

		pRectangle = new RectangleF(Vector2F(-halfX, -halfY), Vector2F(halfX, halfY));

		separator_pos = separator_next_pos + 1;
	}


	return pRectangle;
}

/*static*/void DB::Copy(const std::vector<RectangleF*>& from, std::vector<RectangleF*>& to)
{
	to.reserve(from.size());
	std::vector<RectangleF*>::const_iterator it = from.begin();
	while (it != from.end())
	{
		RectangleF* rectangle = new RectangleF(**it);
		to.push_back(rectangle);

		++it;
	}
}

/*static*/void DB::CopyTo(std::vector<RectangleF*>& newDB)
{
	
	if (!s_pDB)
	{
		wxLogDebug("DB is not initialized");
		return;
	}
	DB::Copy(s_pDB->m_pInitRectangles, newDB);
}

/*static*/void DB::CreateDB( const char* file )
{
	if (s_pDB)
		return;
	s_pDB = new DB();
	s_pDB->LoadRectangles(file);
}

/*static*/ void DB::CleanDB()
{
	if (s_pDB)
	{
		CleanDB(s_pDB->m_pInitRectangles);
		delete s_pDB;
		s_pDB = NULL;
	}
}

void DB::CleanDB( std::vector<RectangleF*>& db )
{
	if (db.empty())
		return;
	std::vector<RectangleF*>::iterator it = db.begin();
	while (it != db.end())
	{
		delete *it;
		++it;
	}
	db.clear();
}

DB*					DB::s_pDB = NULL;