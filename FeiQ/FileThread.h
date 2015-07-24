#if !defined(AFX_FILETHREAD_H__C06A65DC_05F3_41DD_A913_0145B0BA6C53__INCLUDED_)
#define AFX_FILETHREAD_H__C06A65DC_05F3_41DD_A913_0145B0BA6C53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileThread.h : header file
//

#include "FileRecvDlg.h"
#include "FileSendDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CFileThread thread

class CFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CFileThread)
protected:
	CFileThread();           // protected constructor used by dynamic creation

// Attributes
public:
    //���նԻ���
    CFileRecvDlg m_FileRecvDlg;
    //���ͶԻ���
    CFileSendDlg m_FileSendDlg;
    //���ͻ���նԻ����ʶ
    BOOL m_bSendDlg;
// Operations
public:
    void SetSocket(SOCKET clientsock,CString strIP,
        BOOL bSend=FALSE);

    void SetSocket(CString strFile,CString strIP,
        BOOL bSend=TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileThread();

	// Generated message map functions
	//{{AFX_MSG(CFileThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETHREAD_H__C06A65DC_05F3_41DD_A913_0145B0BA6C53__INCLUDED_)
