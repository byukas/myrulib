/////////////////////////////////////////////////////
// Generated By wxActiveRecordGenerator v 1.2.0-rc3
/////////////////////////////////////////////////////

#include "Archives.h"

/** ACTIVE_RECORD **/
Archives::Archives():wxSqliteActiveRecord(){
}

Archives::Archives(const wxString& name,const wxString& server,const wxString& user,const wxString& password,const wxString& table):wxSqliteActiveRecord(name,server,user,password,table){
}

Archives::Archives(DatabaseLayer* database,const wxString& table):wxSqliteActiveRecord(database,table){
}

bool Archives::Create(const wxString& name,const wxString& server,const wxString& user,const wxString& password,const wxString& table){
	return wxSqliteActiveRecord::Create(name,server,user,password,table);
}

ArchivesRow* Archives::RowFromResult(DatabaseResultSet* result){
	ArchivesRow* row=new ArchivesRow(this);

	row->GetFromResult(result);

	return row;
}

ArchivesRow* Archives::New(){
	ArchivesRow* newRow=new ArchivesRow(this);
	garbageRows.Add(newRow);
	return newRow;
}

bool Archives::Delete(int key){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("DELETE FROM %s WHERE id=?"),m_table.c_str()));
		pStatement->SetParamInt(1,key);
		pStatement->ExecuteUpdate();
		return true;
	}
	catch(DatabaseLayerException& e){
		throw(e);
		return false;
	}
}

ArchivesRow* Archives::Id(int key){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("SELECT * FROM %s WHERE id=?"),m_table.c_str()));
		pStatement->SetParamInt(1,key);
		DatabaseResultSet* result= pStatement->ExecuteQuery();

		result->Next();
		ArchivesRow* row=RowFromResult(result);
		garbageRows.Add(row);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return row;
	}
	catch (DatabaseLayerException& e)
	{
		ProcessException(e);
		return NULL;
	}
}

ArchivesRow* Archives::Where(const wxString& whereClause){
	try{
		wxString prepStatement = wxString::Format(wxT("SELECT * FROM %s WHERE %s"),m_table.c_str(),whereClause.c_str());
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);
		DatabaseResultSet* result= pStatement->ExecuteQuery();

		if(!result->Next())
			return NULL;
		ArchivesRow* row=RowFromResult(result);

		garbageRows.Add(row);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return row;
	}
	catch (DatabaseLayerException& e)
	{
		ProcessException(e);
		return 0;
	}
}

ArchivesRow* Archives::FindFile(const wxString& file_name, const wxString& file_path) {
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("SELECT * FROM %s WHERE file_name=? AND file_path=?"),m_table.c_str()));
		pStatement->SetParamString(1, file_name);
		pStatement->SetParamString(2, file_path);
		DatabaseResultSet* result= pStatement->ExecuteQuery();

		if(!result->Next())
			return NULL;
		ArchivesRow* row=RowFromResult(result);

		garbageRows.Add(row);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return row;
	}
	catch (DatabaseLayerException& e)
	{
		ProcessException(e);
		return 0;
	}
}

ArchivesRowSet* Archives::WhereSet(const wxString& whereClause,const wxString& orderBy){
	ArchivesRowSet* rowSet=new ArchivesRowSet();
	try{
		wxString prepStatement=wxString::Format(wxT("SELECT * FROM %s WHERE %s"),m_table.c_str(),whereClause.c_str());
		if(!orderBy.IsEmpty())
			prepStatement+=wxT(" ORDER BY ")+orderBy;
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);
		DatabaseResultSet* result= pStatement->ExecuteQuery();

		if(result){
			while(result->Next()){
				rowSet->Add(RowFromResult(result));
			}
		}

		garbageRowSets.Add(rowSet);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return rowSet;

	}
	catch (DatabaseLayerException& e)
	{
		ProcessException(e);
		return 0;
	}
}

ArchivesRowSet* Archives::All(const wxString& orderBy){
	ArchivesRowSet* rowSet=new ArchivesRowSet();
	try{
		wxString prepStatement=wxString::Format(wxT("SELECT * FROM %s"),m_table.c_str());
		if(!orderBy.IsEmpty())
			prepStatement+=wxT(" ORDER BY ")+orderBy;
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);

		DatabaseResultSet* result= pStatement->ExecuteQuery();

		if(result){
			while(result->Next()){
				rowSet->Add(RowFromResult(result));
			}
		}
		garbageRowSets.Add(rowSet);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return rowSet;

	}
	catch (DatabaseLayerException& e)
	{
		ProcessException(e);
		return 0;
	}
}

/** END ACTIVE RECORD **/

/** ACTIVE RECORD ROW **/

ArchivesRow::ArchivesRow():wxActiveRecordRow(){
	newRow=true;
}

ArchivesRow::ArchivesRow(Archives* activeRecord):wxActiveRecordRow(activeRecord){
	newRow=true;
}

ArchivesRow::ArchivesRow(const ArchivesRow& src){
	if(&src==this)
		return;
	newRow=src.newRow;

	id=src.id;
	file_name=src.file_name;
	file_path=src.file_path;
	file_size=src.file_size;
	file_count=src.file_count;
	description=src.description;
}

ArchivesRow::ArchivesRow(DatabaseLayer* database,const wxString& table):wxActiveRecordRow(database,table){
	newRow=true;
}

ArchivesRow& ArchivesRow::operator=(const ArchivesRow& src){
	if(&src==this)
		return *this;
	newRow=src.newRow;

	id=src.id;
	file_name=src.file_name;
	file_path=src.file_path;
	file_size=src.file_size;
	file_count=src.file_count;
	description=src.description;

	return *this;
}

bool ArchivesRow::GetFromResult(DatabaseResultSet* result){

	newRow=false;

	id=result->GetResultInt(wxT("id"));
	file_name=result->GetResultString(wxT("file_name"));
	file_path=result->GetResultString(wxT("file_path"));
	file_size=result->GetResultInt(wxT("file_size"));
	file_count=result->GetResultInt(wxT("file_count"));
	description=result->GetResultString(wxT("description"));

	return true;
}


bool ArchivesRow::Save(){
	try{
		if(newRow){
			PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("INSERT INTO %s (file_name,file_path,file_size,file_count,description,id) VALUES (?,?,?,?,?,?)"),m_table.c_str()));
			pStatement->SetParamString(1,file_name);
			pStatement->SetParamString(2,file_path);
			pStatement->SetParamInt(3,file_size);
			pStatement->SetParamInt(4,file_count);
			pStatement->SetParamString(5,description);
			pStatement->SetParamInt(6,id);
			pStatement->RunQuery();
			m_database->CloseStatement(pStatement);
			newRow=false;
		}
		else{
			PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("UPDATE %s SET file_name=?,file_path=?,file_size=?,file_count=?,description=? WHERE id=?"),m_table.c_str()));
			pStatement->SetParamString(1,file_name);
			pStatement->SetParamString(2,file_path);
			pStatement->SetParamInt(3,file_size);
			pStatement->SetParamInt(4,file_count);
			pStatement->SetParamString(5,description);
			pStatement->SetParamInt(6,id);
			pStatement->RunQuery();
			m_database->CloseStatement(pStatement);

		}
		return true;
	}
	catch (DatabaseLayerException& e)
	{
		wxActiveRecord::ProcessException(e);
		return false;
	}
}

bool ArchivesRow::Delete(){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("DELETE FROM %s WHERE id=?"),m_table.c_str()));
		pStatement->SetParamInt(1,id);
		pStatement->ExecuteUpdate();
		return true;
	}
	catch(DatabaseLayerException& e){
		throw(e);
		return false;
	}
}

BooksRowSet* ArchivesRow::GetBooks(const wxString& orderBy){
	BooksRowSet* set= new BooksRowSet(m_database,wxT("books"));
	wxString str_statement =wxT("SELECT * FROM books WHERE id_archive=?");
	if(!orderBy.IsEmpty())
		str_statement+=wxT(" ORDER BY ")+orderBy;
	PreparedStatement* pStatement=m_database->PrepareStatement(str_statement);
	pStatement->SetParamInt(1,id);
	DatabaseResultSet* result= pStatement->ExecuteQuery();

	while(result->Next()){
		BooksRow* toAdd=new BooksRow(m_database,wxT("books"));
		toAdd->GetFromResult(result);
		set->Add(toAdd);
	}
	garbageRowSets.Add(set);
	m_database->CloseResultSet(result);
	m_database->CloseStatement(pStatement);
	return set;
}



/** END ACTIVE RECORD ROW **/

/** ACTIVE RECORD ROW SET **/

ArchivesRowSet::ArchivesRowSet():wxActiveRecordRowSet(){
}

ArchivesRowSet::ArchivesRowSet(wxActiveRecord* activeRecord):wxActiveRecordRowSet(activeRecord){
}

ArchivesRowSet::ArchivesRowSet(DatabaseLayer* database,const wxString& table):wxActiveRecordRowSet(database,table){
}

ArchivesRow* ArchivesRowSet::Item(unsigned long item){
	return (ArchivesRow*)wxActiveRecordRowSet::Item(item);
}


bool ArchivesRowSet::SaveAll(){
	try{
		m_database->BeginTransaction();
		for(unsigned long i=0;i<Count();i++)
			Item(i)->Save();
		m_database->Commit();
		return true;
	}
	catch (DatabaseLayerException& e)
	{
		m_database->RollBack();
		wxActiveRecord::ProcessException(e);
		return false;
	}
}


int ArchivesRowSet::CMPFUNC_file_count(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	if((*m_item1)->file_count<(*m_item2)->file_count)
		return -1;
	else if((*m_item1)->file_count>(*m_item2)->file_count)
		return 1;
	else
		return 0;
}

int ArchivesRowSet::CMPFUNC_description(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	return (*m_item1)->description.Cmp((*m_item2)->description);
}

int ArchivesRowSet::CMPFUNC_id(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	if((*m_item1)->id<(*m_item2)->id)
		return -1;
	else if((*m_item1)->id>(*m_item2)->id)
		return 1;
	else
		return 0;
}

int ArchivesRowSet::CMPFUNC_file_path(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	return (*m_item1)->file_path.Cmp((*m_item2)->file_path);
}

int ArchivesRowSet::CMPFUNC_file_size(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	if((*m_item1)->file_size<(*m_item2)->file_size)
		return -1;
	else if((*m_item1)->file_size>(*m_item2)->file_size)
		return 1;
	else
		return 0;
}

int ArchivesRowSet::CMPFUNC_file_name(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	ArchivesRow** m_item1=(ArchivesRow**)item1;
	ArchivesRow** m_item2=(ArchivesRow**)item2;
	return (*m_item1)->file_name.Cmp((*m_item2)->file_name);
}

CMPFUNC_proto ArchivesRowSet::GetCmpFunc(const wxString& var) const{
	if(var==wxT("file_count"))
		return (CMPFUNC_proto)CMPFUNC_file_count;
	else if(var==wxT("description"))
		return (CMPFUNC_proto)CMPFUNC_description;
	else if(var==wxT("id"))
		return (CMPFUNC_proto)CMPFUNC_id;
	else if(var==wxT("file_path"))
		return (CMPFUNC_proto)CMPFUNC_file_path;
	else if(var==wxT("file_size"))
		return (CMPFUNC_proto)CMPFUNC_file_size;
	else if(var==wxT("file_name"))
		return (CMPFUNC_proto)CMPFUNC_file_name;
	else
	return (CMPFUNC_proto)CMPFUNC_default;
}

/** END ACTIVE RECORD ROW SET **/

////@@begin custom implementations



////@@end custom implementations
