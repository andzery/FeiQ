#if !defined(AFX_FILESENDDLG_H__1084EC50_C657_477F_AF9C_7D3D25F578EC__INCLUDED_)
#define AFX_FILESENDDLG_H__1084EC50_C657_477F_AF9C_7D3D25F578EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSendDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSendDlg dialog
#include "FileClient.h"


class CFileSendDlg : public CDialog
{
// Construction
public:
	CFileSendDlg(CWnd* pParent = NULL);   // standard constructor
    CString m_strIP;
    CString m_strFile;
    CFileClient m_FileClient;

    static UINT SendThread(LPVOID pParam);
// Dialog Data
	//{{AFX_DATA(CFileSendDlg)
	enum { IDD = IDD_FILESEND };
	CStatic	m_wndSend;
	CProgressCtrl	m_wndProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSendDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSendDlg)
	afx_msg void OnSend();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESENDDLG_H__1084EC50_C657_477F_AF9C_7D3D25F578EC__INCLUDED_)
