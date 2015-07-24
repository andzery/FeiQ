// ChatView.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"
#include "FileClient.h"
#include "ChatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(CChatView::IDD)
{
	//{{AFX_DATA_INIT(CChatView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pUserClient=NULL;
}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatView)
	DDX_Control(pDX, IDC_CHATUSER, m_wndChatUser);
	DDX_Control(pDX, IDC_CHATLIST, m_wndChatList);
	DDX_Control(pDX, IDC_CHATDATA, m_wndChatData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatView, CFormView)
	//{{AFX_MSG_MAP(CChatView)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SENDFILE, OnSendfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatView diagnostics

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatView message handlers

void CChatView::OnSend() 
{
	// TODO: Add your control notification handler code here
	if(NULL==m_pUserClient)
        return;

    
    CString strChat;
    m_wndChatData.GetWindowText(strChat);
    
    int nSel=m_wndChatUser.GetCurSel();
    if(nSel==0)
    {
        m_pUserClient->SendChat("",strChat);
    }
    else
    {
        CString strIP;
        m_wndChatUser.GetLBText(nSel,strIP);
        m_pUserClient->SendChat(strIP,strChat,FALSE);
    }

}

void CChatView::AddUser(CString strIP)
{
    if(-1!=m_wndChatUser.FindString(0,strIP))
        return;

    m_wndChatUser.AddString(strIP);


}

void CChatView::DelUser(CString strIP)
{
    int nItem=m_wndChatUser.FindString(0,strIP);
    if(-1!=nItem)
        return;

    m_wndChatUser.DeleteString(nItem);

}

void CChatView::AddChat(CString strChat,CString strIP)
{
    //将聊天数据添加到list中
    CTime tmCur=CTime::GetCurrentTime();
    CString strTime=tmCur.Format("%Y-%m-%d %H:%M:%S");

    CString strData=strIP+"  "+strTime+" : "+strChat;
    int nItem=m_wndChatList.AddString(strData);
    m_wndChatList.SetCurSel(nItem);//选中最后一条消息


}

int CChatView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CChatView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_wndChatUser.SetCurSel(0);
}

#include "FileThread.h"

void CChatView::OnSendfile() 
{
	// TODO: Add your control notification handler code here
    //选择当前要发送的IP地址
    int nSel=m_wndChatUser.GetCurSel();
    if(nSel==0)
    {
        AfxMessageBox("请选择要发送的IP地址");
        return;
    }

    CString strIP;
    m_wndChatUser.GetLBText(nSel,strIP);
       

    //选择发送的文件
    CFileDialog dlg(TRUE);
    if(IDOK!=dlg.DoModal())
        return;
    CString strFilePath=dlg.GetPathName();


    //创建线程并挂起
    CFileThread *pThread=(CFileThread*)
        AfxBeginThread(RUNTIME_CLASS(CFileThread),
        THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
    //设置参数
    pThread->SetSocket(strFilePath,strIP,TRUE);
    //开始线程
    pThread->ResumeThread();
   

}
