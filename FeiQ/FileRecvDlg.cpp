// FileRecvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"
#include "FileRecvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileRecvDlg dialog


CFileRecvDlg::CFileRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileRecvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileRecvDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_ClientSocket=INVALID_SOCKET;
}

CFileRecvDlg::~CFileRecvDlg()
{
    if(INVALID_SOCKET!=m_ClientSocket)
        closesocket(m_ClientSocket);

}

void CFileRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileRecvDlg)
	DDX_Control(pDX, IDC_INFO, m_wndInfo);
	DDX_Control(pDX, IDC_PROGRESS, m_wndProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileRecvDlg, CDialog)
	//{{AFX_MSG_MAP(CFileRecvDlg)
	ON_BN_CLICKED(IDC_RECV, OnRecv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileRecvDlg message handlers

BOOL CFileRecvDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	 NETHEADER header={0};
    RecvData((LPSTR)&header,sizeof(header));
    RecvData((LPSTR)&m_SendFile,sizeof(m_SendFile));

    SetWindowText(m_strIP);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileRecvDlg::OnRecv() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE,NULL,m_SendFile.szFileName);
    if(IDOK!=dlg.DoModal())
        return;
    m_strFilePath=dlg.GetPathName();

    //ר�������������ݵ��߳�
    AfxBeginThread(RecvThread,this);
    
}

UINT CFileRecvDlg::RecvThread(LPVOID pParam)
{
    CFileRecvDlg *pThis=(CFileRecvDlg*)pParam;
    //�����ļ�
    CFile file;
    if(FALSE==file.Open(pThis->m_strFilePath,CFile::modeCreate|
        CFile::modeWrite))
        return 0;

    //���ý�������Χ
    pThis->m_wndProgress.SetRange32(0,
        pThis->m_SendFile.nFileLength);
    pThis->m_wndInfo.SetWindowText("���ڽ���...");


    //�������ݲ�д���ļ�
    CHAR szBuf[4096]={0};
    DWORD nLeft=pThis->m_SendFile.nFileLength;
    while(nLeft>0)
    {
        //������յ�������
        DWORD nRecv=4096;
        if(nLeft<nRecv)
            nRecv=nLeft;

        //��������
        pThis->RecvData(szBuf,nRecv);
        //д���ļ�
        file.Write(szBuf,nRecv);
        //����ʣ����յ�����
        nLeft=nLeft-nRecv;

        //���ý�����
        pThis->m_wndProgress.SetPos(
            pThis->m_SendFile.nFileLength-nLeft);
    }
    pThis->m_wndInfo.SetWindowText("�����������");
    
    //�ر��ļ�
    file.Close();

    return 0;
}

BOOL CFileRecvDlg::RecvData(LPVOID pData,DWORD nLen)
{
    //ѭ����������
    LPSTR pTmpData=(LPSTR)pData;
    long nLeft=nLen;
    while(nLeft>0)
    {
        int nRecv=recv(m_ClientSocket,pTmpData,
            nLeft,0);
        if(SOCKET_ERROR==nRecv)
            return FALSE;
        nLeft=nLeft-nRecv;
        pTmpData=pTmpData+nRecv;
    
    }

    return TRUE;
}
