/////////////////////////////////////////////////////
// Generated By wxActiveRecordGenerator v 1.2.0-rc3
/////////////////////////////////////////////////////


#ifndef __FILES_
#define __FILES_

////@@begin gen include
#include "wxActiveRecord.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/datetime.h>

////@@end gen include

////@@begin custom include
////@@end custom include

////@@begin gen forward
class Files;
class FilesRow;
class FilesRowSet;


////@@end gen forward

////@@begin custom forward
////@@end custom forward

////@@begin gen arClass
class Files: public wxSqliteActiveRecord{
protected:
	FilesRow* RowFromResult(DatabaseResultSet* result);
public:
	Files();
	Files(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("files"));
	Files(DatabaseLayer* database,const wxString& table=wxT("files"));
	bool Create(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("files"));

	FilesRow* New();

	FilesRowSet* IdBook(int key);
    FilesRow* Find(const int id_book, const int id_archive);
	FilesRow* Where(const wxString& whereClause);
	FilesRowSet* WhereSet(const wxString& whereClause,const wxString& orderBy=wxEmptyString);
	FilesRowSet* All(const wxString& orderBy=wxEmptyString);

////@@begin custom arClass
public:
////@@end custom arClass
};
////@@end gen arClass

////@@begin gen arRow
class FilesRow: public wxActiveRecordRow{
public:
	FilesRow();
	FilesRow(const FilesRow& src);
	FilesRow(Files* activeRecord);
	FilesRow(DatabaseLayer* database,const wxString& table=wxT("files"));
	FilesRow& operator=(const FilesRow& src);
	bool GetFromResult(DatabaseResultSet* result);
public:
	int id_archive;
	int id_book;
	wxString file_name;

public:


	bool Save();
	bool Delete();


////@@begin custom arRow
public:
////@@end custom arRow

};
////@@end gen arRow

////@@begin gen arSet
class FilesRowSet: public wxActiveRecordRowSet{
public:
	FilesRowSet();
	FilesRowSet(wxActiveRecord* activeRecord);
	FilesRowSet(DatabaseLayer* database,const wxString& table=wxT("files"));
	virtual FilesRow* Item(unsigned long item);

	virtual bool SaveAll();


protected:
	static int CMPFUNC_id_archive(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_id_book(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_file_name(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_global(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	virtual CMPFUNC_proto GetCmpFunc(const wxString& var) const;

////@@begin custom arSet
public:
////@@end custom arSet
};
////@@end gen arSet

#endif /* __FILES_ */
