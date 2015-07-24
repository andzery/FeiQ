// UserView.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"
#include "UserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserView

IMPLEMENT_DYNCREATE(CUserView, CListView)

CUserView::CUserView()
{
}

CUserView::~CUserView()
{
}


BEGIN_MESSAGE_MAP(CUserView, CListView)
	//{{AFX_MSG_MAP(CUserView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserView drawing

void CUserView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CUserView diagnostics

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CListView::AssertValid();
}

void CUserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUserView message handlers

int CUserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    ModifyStyle(0,LVS_REPORT);

	CListCtrl &theCtrl=GetListCtrl();
    theCtrl.InsertColumn(0,"计算机名称",
        LVCFMT_LEFT,100);
    theCtrl.InsertColumn(1,"IP地址",
        LVCFMT_LEFT,100);
    theCtrl.InsertColumn(2,"签名",
        LVCFMT_LEFT,100);

    //检测HeartBeat的定时器
    SetTimer(2,1000*20,NULL);

	return 0;
}

void CUserView::AddUser(CString strName,
             CString strIP,
             CString strSign)
{
    CListCtrl &theCtrl=GetListCtrl();

    //查找是否已经添加到View中
    int nItem=FindUser(strIP);
    if(-1!=nItem)
    {
        //设置HeartBeat为TRUE
        theCtrl.SetItemData(nItem,1);
        return;
    }

    //添加到View当中
    nItem=theCtrl.GetItemCount();
    nItem=theCtrl.InsertItem(nItem,strName);
    theCtrl.SetItemText(nItem,1,strIP);
    theCtrl.SetItemText(nItem,2,strSign);
    //设置HeartBeat为TRUE
    theCtrl.SetItemData(nItem,1);


}

void CUserView::DelUser(CString strIP)
{
    //查找指定IP的用户项
    int nItem=FindUser(strIP);
    if(-1==nItem)
        return;
    //删除用户
    CListCtrl &theCtrl=GetListCtrl();
    theCtrl.DeleteItem(nItem);

}


int CUserView::FindUser(CString strIP)
{
    CListCtrl& theCtrl=GetListCtrl();
    int nCount=theCtrl.GetItemCount();
    for(int nItem=0;nItem<nCount;nItem++)
    {
        CString strItemIP=
            theCtrl.GetItemText(nItem,1);
        if(0==strItemIP.CompareNoCase(strIP))
            return nItem;
    
    }
    return -1;

}



void CUserView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    if(nIDEvent!=2)
        return;

	CListCtrl& theCtrl=GetListCtrl();
    int nCount=theCtrl.GetItemCount();
    for(int nItem = nCount-1;nItem>=0;nItem--)
    {
        //获取HeartBeat数值  GetItemData:是将关联的内容取出来
        DWORD nData=theCtrl.GetItemData(nItem);
        //判断HeartBeat数值
        if(nData>0)
        {
            //清空HeartBeat数值  SetItemData的功能是把相应的条目与一个数据相关联
            theCtrl.SetItemData(nItem,0);
        }
        else
        {
            //删除项
            theCtrl.DeleteItem(nItem);
        }
    
    }


	CListView::OnTimer(nIDEvent);
}
