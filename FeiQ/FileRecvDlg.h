#if !defined(AFX_FILERECVDLG_H__5E9463E9_D5CA_4DE0_86F3_D2BCC63ED55D__INCLUDED_)
#define AFX_FILERECVDLG_H__5E9463E9_D5CA_4DE0_86F3_D2BCC63ED55D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileRecvDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileRecvDlg dialog

class CFileRecvDlg : public CDialog
{
// Construction
public:
	CFileRecvDlg(CWnd* pParent = NULL);   // standard constructor
    ~CFileRecvDlg();

    static UINT RecvThread(LPVOID pParam);

    SOCKET m_ClientSocket;
    CString m_strIP;
    CString m_strFilePath;
    SENDFILE m_SendFile;

    BOOL RecvData(LPVOID pData,DWORD nLen);


// Dialog Data
	//{{AFX_DATA(CFileRecvDlg)
	enum { IDD = IDD_FILERECV };
	CStatic	m_wndInfo;
	CProgressCtrl	m_wndProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileRecvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileRecvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILERECVDLG_H__5E9463E9_D5CA_4DE0_86F3_D2BCC63ED55D__INCLUDED_)
