// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FeiQ.h"

#include "ChatView.h"
#include "UserView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    Initialize();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//创建切分窗口
    m_wndSplitter.CreateStatic(this,2,1);
    m_wndSplitter.CreateView(0,0,
        RUNTIME_CLASS(CUserView),
        CSize(200,200),pContext);
    m_wndSplitter.CreateView(1,0,
        RUNTIME_CLASS(CChatView),
        CSize(200,200),pContext);

    //获取UserView的地址
    CChatView* pChatView=
        (CChatView*)m_wndSplitter.GetPane(1,0);
    m_UserServer.m_pChatView=pChatView;
    m_UserServer.m_pUserView=
        (CUserView*)m_wndSplitter.GetPane(0,0);

    pChatView->m_pUserClient=&m_UserClient;
    

    return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::Initialize()
{

    if(TRUE!=m_UserServer.InitServer())
        AfxMessageBox("用户服务器创建失败");

    if(TRUE!=m_UserClient.InitClient())
        AfxMessageBox("用户客户端创建失败");

    if(TRUE!=m_FileServer.InitServer())
        AfxMessageBox("文件服务器创建失败");

    m_UserClient.Broadcast();
     SetTimer(1,5000*10,NULL);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    //heartbeat
    
	m_UserClient.Broadcast();

}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//客户端退出
    m_UserClient.UserQuit();

	CFrameWnd::OnClose();
}
