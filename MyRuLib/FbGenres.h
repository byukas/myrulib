#ifndef FBGENRES_H
#define FBGENRES_H

#include <wx/wx.h>
#include "FbTreeModel.h"

class FbGenreParentData: public FbParentData
{
	public:
		FbGenreParentData(FbModel & model, FbParentData * parent, const wxString &name)
			: FbParentData(model, parent), m_name(name) {}
		virtual wxString GetValue(FbModel & model, size_t col) const
			{ return col ? (wxString)wxEmptyString : m_name; }
	private:
		wxString m_name;
		DECLARE_CLASS(FbGenreParentData);
};

class FbGenreChildData: public FbChildData
{
	public:
		FbGenreChildData(FbModel & model, FbParentData * parent, const wxString &code, const wxString &name)
			: FbChildData(model, parent), m_code(code), m_name(name) {}
		virtual wxString GetValue(FbModel & model, size_t col) const
			{ return col ? (wxString)wxEmptyString : m_name; }
		wxString GetCode()
			{ return m_code; }
	private:
		wxString m_code;
		wxString m_name;
		DECLARE_CLASS(FbGenreChildData);
};

class FbGenres
{
	public:
		static wxString Char(const wxString &code);
		static wxString Name(const wxString &letter);
		static wxString DecodeList(const wxString &genres);
		static FbModel * CreateModel();
	private:
		enum ID {
			ID_CHAR,
			ID_NAME,
			ID_FILL,
		};
		static void Do(ID id, const void * value, void * result);
};

#endif //FBGENRES_H

