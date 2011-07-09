#include "FbBookData.h"
#include "ZipReader.h"
#include "FbBookEvent.h"
#include "FbParams.h"
#include "FbCollection.h"
#include "FbColumns.h"
#include "FbConst.h"
#include "FbSmartPtr.h"
#include "MyRuLibApp.h"
#include "FbMainFrame.h"
#include "frames/FbCoolReader.h"
#include <wx/mimetype.h>
#include <wx/stdpaths.h>

bool FbTempEraser::sm_erase = true;

FbTempEraser::~FbTempEraser()
{
	if (sm_erase)
		for (size_t i=0; i<filelist.GetCount(); i++)
			wxRemoveFile(filelist[i]);
}

void FbTempEraser::Add(const wxString &filename)
{
	static FbTempEraser eraser;
	eraser.filelist.Add(filename);
}

wxString FbBookData::GetExt() const
{
	return FbCollection::GetBook(m_id, BF_TYPE);
}

void FbBookData::Open() const
{
	ZipReader reader(m_id, m_id<0);
	if ( reader.IsOk() ) {
		DoOpen( &reader.GetZip(), reader.GetMd5() );
	} else if ( m_id>0 ) {
		if ( wxMessageBox(_("Download book file?"), _("Confirmation"), wxOK | wxCANCEL) == wxOK) DoDownload();
	}
}

void FbBookData::LoadIcon() const
{
	FbCollection::LoadIcon(GetExt());
}

void FbBookData::SaveFile(wxInputStream & in, const wxString &filepath) const
{
	FbTempEraser::Add(filepath);
	wxFileOutputStream out(filepath);
	out.Write(in);
	out.Close();
}

bool FbBookData::GetSystemCommand(const wxString &filepath, const wxString &filetype, wxString &command) const
{
	wxFileType * ft = wxTheMimeTypesManager->GetFileTypeFromExtension(filetype);
	if ( ft ) {
		bool res = ft->GetOpenCommand(&command, wxFileType::MessageParameters(filepath, wxEmptyString));
		delete ft;
		return res;
	}
	return false;
}

#ifdef __WXGTK__

// helper class for storing arguments as char** array suitable for passing to
// execvp(), whatever form they were passed to us
class FbArgsArray
{
public:
    FbArgsArray(const wxArrayString& args)
    {
        Init(args.size());

        for ( int i = 0; i < m_argc; i++ )
        {
            wxWX2MBbuf arg = wxSafeConvertWX2MB(args[i]);
            m_argv[i] = strdup(arg);
        }
    }

    ~FbArgsArray()
    {
        for ( int i = 0; i < m_argc; i++ )
        {
            free(m_argv[i]);
        }

        delete [] m_argv;
    }

    operator char**() const { return m_argv; }

private:
    void Init(int argc)
    {
        m_argc = argc;
        m_argv = new char *[m_argc + 1];
        m_argv[m_argc] = NULL;
    }

    int m_argc;
    char **m_argv;
};

static void FbExecute(wxString & command, wxFileName & filename)
{
	wxArrayString args;
	args.Add(command);
	if (command.BeforeFirst(wxT(' ')) == wxT("wine")) {
		args.Add(wxT("wine"));
		args.Add(command.AfterFirst(wxT(' ')));
		filename.SetPath( FbParams(FB_WINE_DIR));
	}
	args.Add(filename.GetFullPath());

	FbArgsArray argv(args);
	if (fork() == 0) execvp(*argv, argv);
}

static void FbExecute(wxString & command)
{
	wxArrayString args;
	args.Add(command);
	FbArgsArray argv(args);
	if (fork() == 0) execvp(*argv, argv);
}

#else // __WXGTK__

static void FbExecute(wxString & command, wxFileName & filename)
{
	wxString filepath = filename.GetFullPath();
	filepath.Prepend(wxT('"')).Append(wxT('"'));
	command << wxT(' ') << filepath;
	wxExecute(command);
}

static void FbExecute(wxString & command)
{
	wxExecute(command);
}

#endif // __WXGTK__

//class FbTempInputStream: public wxFileInputStream

void FbBookData::DoOpen(wxInputStream * in, const wxString &md5sum) const
{
	wxString filetype = GetExt();
	wxString command;
	bool ok = false;

	wxString sql = wxT("SELECT command FROM types WHERE file_type=?");
	if (!ok) ok = !(command = FbLocalDatabase().Str(filetype, sql)).IsEmpty();
	if (!ok) ok = !(command = FbCommonDatabase().Str(filetype, sql)).IsEmpty();
	
	wxString tempfile;
	#ifdef FB_INCLUDE_READER
	FbSmartPtr<wxInputStream> file;
	if (!ok) {
		FbMainFrame * frame = wxDynamicCast(wxGetApp().GetTopWindow(), FbMainFrame);
		if (frame) {
			tempfile = wxFileName::CreateTempFileName(wxT("fb"));
			SaveFile(*in, tempfile);
			bool ok = FbCoolReader::Open(frame->GetNotebook(), GetId(), tempfile);
			if (ok) {
				wxRemoveFile(tempfile);
				return;
			} else {
				in = file = new wxFileInputStream(tempfile);
			}
		}
	}
	#endif

	#ifdef __WXGTK__
	if (!ok) { command = wxT("xdg-open"); ok = true; }
    #endif

	wxFileName filename = md5sum;
	filename.SetPath( FbParamItem::GetPath(FB_TEMP_DIR) );
	filename.SetExt(filetype);

	if ( !filename.DirExists())
		filename.Mkdir(0755, wxPATH_MKDIR_FULL);

	wxString filepath = filename.GetFullPath();
	if (!filename.FileExists()) SaveFile(*in, filepath);
	if (!tempfile.IsEmpty()) wxRemoveFile(tempfile);

	if (ok) {
		#ifdef __WXMSW__
		filepath.Prepend(wxT('"')).Append(wxT('"'));
		ShellExecute(NULL, NULL, command, filepath, NULL, SW_SHOW);
		#else
		FbExecute(command, filename);
		#endif
	} else {
		if (GetSystemCommand(filepath, filetype, command)) {
			FbExecute(command);
		} else {
			FbMessageBox(_("Associated application not found"), filetype);
		}
	}
}

void FbBookData::DoDownload() const
{
	if (m_id<0) return;
	wxString md5sum = FbCommonDatabase().GetMd5(m_id);
	if (md5sum.IsEmpty()) return;

	bool ok = false;
	FbLocalDatabase database;
	int folder = - database.NewId(FB_NEW_DOWNLOAD);
	{
		wxString sql = wxT("UPDATE states SET download=? WHERE md5sum=?");
		wxSQLite3Statement stmt = database.PrepareStatement(sql);
		stmt.Bind(1, folder);
		stmt.Bind(2, md5sum);
		ok = stmt.ExecuteUpdate();
	}
	if (!ok) {
		wxString sql = wxT("INSERT INTO states(download, md5sum) VALUES (?,?)");
		wxSQLite3Statement stmt = database.PrepareStatement(sql);
		stmt.Bind(1, folder);
		stmt.Bind(2, md5sum);
		stmt.ExecuteUpdate();
	}

	{
		FbMasterDownInfo info = FbMasterDownInfo::DT_WAIT;
		FbMasterEvent(ID_UPDATE_MASTER, info, m_id, true).Post();
	}

	{
		FbMasterDownInfo info = FbMasterDownInfo::DT_ERROR;
		FbMasterEvent(ID_UPDATE_MASTER, info, m_id, false).Post();
	}

	wxGetApp().StartDownload();
}

void FbBookData::Show(wxEvtHandler * frame, bool bVertical, bool bEditable) const
{
}

