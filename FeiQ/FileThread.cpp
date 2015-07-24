// FileThread.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"


#include "FileThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileThread

IMPLEMENT_DYNCREATE(CFileThread, CWinThread)

CFileThread::CFileThread()
{
    m_bSendDlg=FALSE;
}

CFileThread::~CFileThread()
{
}

BOOL CFileThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

    //线程一旦创建，此对话框就被显示出来
    if(FALSE==m_bSendDlg)
    {
        //接收对话框
        m_pMainWnd=&m_FileRecvDlg;
        m_FileRecvDlg.DoModal();
    }
    else
    {
        m_pMainWnd=&m_FileSendDlg;
        m_FileSendDlg.DoModal();
    
    }
	return TRUE;
}

int CFileThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFileThread, CWinThread)
	//{{AFX_MSG_MAP(CFileThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileThread message handlers
void CFileThread::SetSocket(SOCKET clientsock,
                            CString strIP,
                            BOOL bSend)
{
    m_FileRecvDlg.m_ClientSocket=clientsock;
    m_FileRecvDlg.m_strIP=strIP;
    m_bSendDlg=bSend;

}

void CFileThread::SetSocket(CString strFile,
                            CString strIP,
                            BOOL bSend)
{
    m_FileSendDlg.m_strIP=strIP;
    m_FileSendDlg.m_strFile=strFile;
    m_bSendDlg=bSend;


}