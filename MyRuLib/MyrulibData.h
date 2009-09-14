/***************************************************************
 * Name:      DBCreator.h
 * Purpose:   Code for Application Class
 * Author:    Kandrashin Denis (mail@kandr.ru)
 * Created:   2009-05-22
 * Copyright: Kandrashin Denis (www.lintest.ru)
 * License:
 **************************************************************/

#ifndef DBCREATOR_H
#define DBCREATOR_H

#include <wx/wx.h>
#include <DatabaseLayer.h>
#include <SqliteDatabaseLayer.h>

class MyrulibDatabaseLayer
	: public SqliteDatabaseLayer
{
	public:
		virtual bool Open(const wxString& strDatabase);
		bool CreateDatabase(const wxString & filename);
		bool UpgradeDatabase();
		static int sm_Progress;
		static int sm_Current;
		static int sm_Delta;
		static wxString sm_msg;
};

#endif // DBCREATOR_H