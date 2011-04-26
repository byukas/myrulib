#ifndef __FBTHREAD_H__
#define __FBTHREAD_H__

#include <wx/thread.h>
#include <wx/object.h>

class FbCondition
	: public wxCondition
{
public:
	FbCondition(): wxCondition(m_mutex) {}
private:
	wxMutex m_mutex;
};

class FbThread
	: public wxThread
{
public:
    FbThread(wxThreadKind kind = wxTHREAD_DETACHED)
		: wxThread(kind), m_closed(false) {}
	void Execute()
		{ if ( Create() == wxTHREAD_NO_ERROR ) Run(); }
    bool IsClosed();
    virtual void Close();
private:
	static wxCriticalSection sm_section;
	bool m_closed;
};

class FbProgressThread
	: public FbThread
{
protected:
	static wxCriticalSection sm_queue;
	void SetInfo(const wxString & info) { m_info = info; }
	void DoStart(const wxString & msg, int max = 0);
	void DoStep(const wxString & msg);
	void DoFinish();
private:
	wxString m_info;
	wxString m_text;
	int m_pos;
	int m_max;
};

#endif // __FBTHREAD_H__
