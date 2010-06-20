#ifndef __FBMASTERDATA_H__
#define __FBMASTERDATA_H__

#include <wx/wx.h>
#include <wx/treebase.h>
#include "FbBookTypes.h"
#include "FbDatabase.h"
#include "FbThread.h"
#include "FbMasterInfo.h"

class FbFrameBase;

class FbMasterData: public wxObject
{
	public:
		void Show(FbFrameBase * frame) const;
		virtual FbMasterData * Clone() const = 0;
		virtual FbMasterInfo * CreateInfo() const = 0;
		DECLARE_CLASS(FbMasterData);
};

class FbMasterAuthor: public FbMasterData
{
	public:
		FbMasterAuthor(const int id = 0)
			: m_id(id) {}
		FbMasterAuthor(const FbMasterAuthor & data)
			: m_id(data.m_id) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterAuthor(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterAuthorInfo(m_id); }
	private:
		int m_id;
};

class FbMasterSeqname: public FbMasterData
{
	public:
		FbMasterSeqname(const int id = 0)
			: m_id(id) {}
		FbMasterSeqname(const FbMasterSeqname & data)
			: m_id(data.m_id) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterSeqname(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterSeqnInfo(m_id); }
	private:
		int m_id;
};

class FbMasterGenre: public FbMasterData
{
	public:
		FbMasterGenre(const wxString & id)
			: m_id(id) {}
		FbMasterGenre(const FbMasterGenre & data)
			: m_id(data.m_id) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterGenre(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterGenrInfo(m_id); }
	private:
		const wxString m_id;
};

class FbMasterDownld: public FbMasterData
{
	public:
		FbMasterDownld(const int id = 0)
			: m_id(id) {}
		FbMasterDownld(const FbMasterDownld & data)
			: m_id(data.m_id) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterDownld(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterDownInfo(m_id); }
	private:
		int m_id;
};

class FbMasterSearch: public FbMasterData
{
	public:
		FbMasterSearch(const wxString &title, const wxString &author = wxEmptyString)
			: m_title(title), m_author(author) {}
		FbMasterSearch(const FbMasterSearch & data)
			: m_title(data.m_title), m_author(data.m_author) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterSearch(*this); }
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterSearchInfo(m_title, m_author); }
	private:
		wxString m_title;
		wxString m_author;
};

class FbMasterDate: public FbMasterData
{
	public:
		static wxDateTime GetDate(int code);

		FbMasterDate(const int id = 0)
			: m_id(id) {}
		FbMasterDate(const FbMasterDate & data)
			: m_id(data.m_id) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterDate(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterDateInfo(m_id); }
	private:
		int m_id;
};

class FbMasterFolder: public FbMasterData
{
	public:
		FbMasterFolder(const int id, const FbFolderType type)
			: m_id(id), m_type(type) {}
		FbMasterFolder(const FbMasterFolder & data)
			: m_id(data.m_id), m_type(data.m_type) {}
		virtual FbMasterData * Clone() const
			{ return new FbMasterFolder(*this); };
		virtual FbMasterInfo * CreateInfo() const
			{ return new FbMasterFldrInfo(m_id, m_type); }
	private:
		int m_id;
		FbFolderType m_type;
};

#endif // __FBMASTERDATA_H__
