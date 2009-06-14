/////////////////////////////////////////////////////
// Generated By wxActiveRecordGenerator v 1.2.0-rc3
/////////////////////////////////////////////////////


#ifndef __BOOKSEQ_
#define __BOOKSEQ_

////@@begin gen include
#include "wxActiveRecord.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/datetime.h>

////@@end gen include

////@@begin custom include
////@@end custom include

////@@begin gen forward
class Bookseq;
class BookseqRow;
class BookseqRowSet;


////@@end gen forward

////@@begin custom forward
////@@end custom forward

////@@begin gen arClass
class Bookseq: public wxSqliteActiveRecord{
protected:
	BookseqRow* RowFromResult(DatabaseResultSet* result);
public:
	Bookseq();
	Bookseq(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("bookseq"));
	Bookseq(DatabaseLayer* database,const wxString& table=wxT("bookseq"));
	bool Create(const wxString& name,const wxString& server=wxEmptyString,const wxString& user=wxEmptyString,const wxString& password=wxEmptyString,const wxString& table=wxT("bookseq"));

	BookseqRow* New();
	bool Delete(int key);


	BookseqRow* IdBook(int key);

	BookseqRow* Where(const wxString& whereClause);
	BookseqRowSet* WhereSet(const wxString& whereClause,const wxString& orderBy=wxEmptyString);
	BookseqRowSet* All(const wxString& orderBy=wxEmptyString);

////@@begin custom arClass
public:
////@@end custom arClass
};
////@@end gen arClass

////@@begin gen arRow
class BookseqRow: public wxActiveRecordRow{
public:
	BookseqRow();
	BookseqRow(const BookseqRow& src);
	BookseqRow(Bookseq* activeRecord);
	BookseqRow(DatabaseLayer* database,const wxString& table=wxT("bookseq"));
	BookseqRow& operator=(const BookseqRow& src);
	bool GetFromResult(DatabaseResultSet* result);
public:
	int level;
	int number;
	int id_book;
	int id_seq;
	int id_author;

	int order; //For book sorting
public:


	bool Save();
	bool Delete();


////@@begin custom arRow
public:
////@@end custom arRow

};
////@@end gen arRow

////@@begin gen arSet
class BookseqRowSet: public wxActiveRecordRowSet{
public:
	BookseqRowSet();
	BookseqRowSet(wxActiveRecord* activeRecord);
	BookseqRowSet(DatabaseLayer* database,const wxString& table=wxT("bookseq"));
	virtual BookseqRow* Item(unsigned long item);

	virtual bool SaveAll();


protected:
	static int CMPFUNC_level(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_number(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_id_book(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_id_seq(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_id_author(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_order(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	static int CMPFUNC_global(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	virtual CMPFUNC_proto GetCmpFunc(const wxString& var) const;

////@@begin custom arSet
public:
////@@end custom arSet
};
////@@end gen arSet

#endif /* __BOOKSEQ_ */
