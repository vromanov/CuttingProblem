#include "RectangleDB.h"

#include "RectangleF.h"
#include "DB.h"

#include "wx/wx.h"

RectangleDB::RectangleDB()
{
	
	if (!m_db.empty())
	{
		wxLogError("RectangleDB::Get() m_db is not empty");
		return;
	}
	DB::CopyTo(m_db);
}

RectangleDB::RectangleDB(const RectangleDB& db)
{
	DB::Copy(db.m_db, m_db);
}

const RectangleDB& RectangleDB::operator=(const RectangleDB& db)
{
	DB::Copy(db.m_db, m_db);
	return *this;
}

RectangleDB::~RectangleDB()
{
	DB::CleanDB(m_db);
}

void RectangleDB::Clear()
{
	DB::CleanDB(m_db);
}

void RectangleDB::ReInit()
{
	DB::CleanDB(m_db);
	DB::CopyTo(m_db);
}
