#ifndef __FBBOOKPANEL_H__
#define __FBBOOKPANEL_H__

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "FbBookList.h"
#include "FbBookData.h"
#include "FbParams.h"
#include "FbThread.h"

enum FbListMode {
	FB2_MODE_LIST = 0,
	FB2_MODE_TREE = 1,
};

class FbBookPanel: public wxSplitterWindow
{
	public:
		FbBookPanel();
		FbBookPanel(wxWindow *parent, const wxSize& size, long style, int keyType, int keyMode);
		bool Create(wxWindow *parent, const wxSize& size, long style, int keyType, int keyMode);
		void UpdateInfo(int id);
		void SetOrderID(int id);
		int GetOrderID();
		bool IsOrderDesc();
		void RevertOrder();
		void ShowHTML(const wxString &html);
		wxString GetOrderSQL();
	public:
		FbBookList * m_BookList;
		wxHtmlWindow * m_BookInfo;
		FbBookData * GetSelectedBook();
		void EmptyBooks(const int selected  = 0);
		void AppendBook(BookTreeItemData & data, const wxString & authors = wxEmptyString);
		void AppendAuthor(int id, const wxString title = wxEmptyString);
		void AppendSequence(const wxString title = wxEmptyString);
		void CreateColumns(FbListMode mode);
		FbListMode GetListMode() { return m_ListMode;};
		void SetFolder(int folder) { m_folder = folder; };
		void SetType(int type) { m_type = type; };
		void CreateBookInfo(bool bVertical);
		void UpdateFonts(bool refresh = true);
	private:
		static void DoOpenBook(int id, const wxString &file_type);
		void DoFolderAdd(const int folder);
		static void DoDeleteDownload(const wxString &sel, const int folder);
		static void DoCreateDownload(const wxString &sel, int count = 1);
		static void DoOpenDownload(int id);
		int GetRatingColumn();
		int UpdateChildRating(wxTreeItemId parent, int iRating, const wxString &sRating);
		int UpdateSelectionRating(int iRating, const wxString &sRating);
		void ShowContextMenu(const wxPoint& pos, wxTreeItemId item);
		wxString F(const int number);
		wxString m_AuthorName;
		FbListMode m_ListMode;
		wxTreeItemId m_AuthorItem;
		wxTreeItemId m_SequenceItem;
		int m_folder;
		int m_type;
		int m_selected;
	private:
		void OnBooksListViewSelected(wxTreeEvent & event);
		void OnBooksListActivated(wxTreeEvent & event);
		void OnBooksListKeyDown(wxTreeEvent & event);
		void OnBooksListCollapsing(wxTreeEvent & event);
		void OnDeleteDownload(wxCommandEvent & event);
		void OnDownloadBook(wxCommandEvent & event);
		void OnEditComments(wxCommandEvent & event);
		void OnFavoritesAdd(wxCommandEvent & event);
		void OnFolderAdd(wxCommandEvent& event);
		void OnOpenAuthor(wxCommandEvent& event);
		void OnOpenBook(wxCommandEvent & event);
		void OnBookPage(wxCommandEvent & event);
		void OnSystemDownload(wxCommandEvent & event);
		void OnImageClick(wxTreeEvent &event);
		void OnInfoUpdate(wxCommandEvent& event);
		void OnSubmenu(wxCommandEvent& event);
		void OnContextMenu(wxTreeEvent& event);
		void OnSelectAll(wxCommandEvent& event);
		void OnUnselectAll(wxCommandEvent& event);
		void OnChangeRating(wxCommandEvent& event);
		void OnDeleteBooks(wxCommandEvent& event);
		void OnModifyBooks(wxCommandEvent& event);
		void OnLinkClicked(wxHtmlLinkEvent& event);
		DECLARE_EVENT_TABLE();
	private:
		class AuthorThread: public FbThread
		{
			public:
				AuthorThread(wxWindow * frame, int author): m_frame(frame), m_author(author) {};
			protected:
				virtual void * Entry();
			private:
				wxWindow * m_frame;
				int m_author;
		};

};


#endif // __FBBOOKPANEL_H__
