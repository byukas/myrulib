/////////////////////////////////////////////////////
// Generated By wxActiveRecordGenerator v 1.2.0-rc3
/////////////////////////////////////////////////////


#ifndef __ARCHIVES_
#define __ARCHIVES_

////@@begin gen include
#include "wxActiveRecord.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include "Books.h"

////@@end gen include

////@@begin custom include
////@@end custom include

////@@begin gen forward
class Archives;
class ArchivesRow;
class ArchivesRowSet;

class Books;
class BooksRow;
class BooksRowSet;

////@@end gen forward

////@@begin custom forward
////@@end custom forward

////@@begin gen arClass
class Archives: public wxSqliteActiveRecord{
protected:
	ArchivesRow* RowFromResult(DatabaseResultSet* result);
public:
	Archives();
	Archives(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("archives"));
	Archives(DatabaseLayer* database,const wxString& table=wxT("archives"));
	bool Create(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("archives"));

	ArchivesRow* New();
	bool Delete(int key);


	ArchivesRow* Id(int key);

	ArchivesRow* Where(const wxString& whereClause);
	ArchivesRowSet* WhereSet(const wxString& whereClause,const wxString& orderBy=wxEmptyString);
	ArchivesRowSet* All(const wxString& orderBy=wxEmptyString);

////@@begin custom arClass
public:



////@@end custom arClass
};
////@@end gen arClass

////@@begin gen arRow
class ArchivesRow: public wxActiveRecordRow{
public:
	ArchivesRow();
	ArchivesRow(const ArchivesRow& src);
	ArchivesRow(Archives* activeRecord);
	ArchivesRow(DatabaseLayer* database,const wxString& table=wxT("archives"));
	ArchivesRow& operator=(const ArchivesRow& src);
	bool GetFromResult(DatabaseResultSet* result);
public:
	wxString description;
	int id;
	int file_size;
	wxString file_name;
	wxString file_path;

public:
	BooksRowSet* GetBooks(const wxString& orderBy=wxEmptyString);


	bool Save();
	bool Delete();


////@@begin custom arRow
public:



////@@end custom arRow

};
////@@end gen arRow

////@@begin gen arSet
class ArchivesRowSet: public wxActiveRecordRowSet{
public:
	ArchivesRowSet();
	ArchivesRowSet(wxActiveRecord* activeRecord);
	ArchivesRowSet(DatabaseLayer* database,const wxString& table=wxT("archives"));
	virtual ArchivesRow* Item(unsigned long item);

	virtual bool SaveAll();


protected:
	static int CMPFUNC_description(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_id(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_file_size(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_file_name(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_file_path(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_global(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	virtual CMPFUNC_proto GetCmpFunc(const wxString& var) const;

////@@begin custom arSet
public:



////@@end custom arSet
};
////@@end gen arSet

#endif /* __ARCHIVES_ */
