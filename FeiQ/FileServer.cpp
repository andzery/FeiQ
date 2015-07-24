// FileServer.cpp: implementation of the CFileServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FeiQ.h"
#include "FileServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileServer::CFileServer()
{
    
}

CFileServer::~CFileServer()
{
    
}

//初始化服务器
BOOL CFileServer::InitServer()
{
      //创建TCP服务器
    m_SvrSocket=socket(AF_INET,SOCK_STREAM,
        IPPROTO_TCP);
    if(INVALID_SOCKET==m_SvrSocket)
        return FALSE;
    
    
    //绑定端口和IP
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_FILESVR);
    addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    bind(m_SvrSocket,(SOCKADDR*)&addr,sizeof(addr));

    //侦听
    listen(m_SvrSocket,5);

    //创建等候客户端的线程
    AfxBeginThread(FileThread,this);


    return TRUE;
}


//接收客户端的线程
UINT CFileServer::FileThread(LPVOID pParam)
{
    CFileServer *pThis=(CFileServer*)pParam;
    while(1)
    {
        //等候客户端的连接
        SOCKADDR_IN clientaddr={0};
        int nLen=sizeof(clientaddr);
        SOCKET clientsock=accept(
            pThis->m_SvrSocket,
            (SOCKADDR*)&clientaddr,
            &nLen);
        if(INVALID_SOCKET==clientsock)
            continue;
        //处理客户端的连接
        CHAR *pszIP=inet_ntoa(clientaddr.sin_addr);
        pThis->OnConnect(clientsock,pszIP);
    
    }


    return 0;
}

#include "FileThread.h"


void CFileServer::OnConnect(SOCKET clientsock,LPSTR pszID)
{
    //创建线程并挂起
    CFileThread *pThread=(CFileThread*)
        AfxBeginThread(RUNTIME_CLASS(CFileThread),
        THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
    //设置参数
    pThread->SetSocket(clientsock,pszID);
    //开始线程
    pThread->ResumeThread();

   
}
