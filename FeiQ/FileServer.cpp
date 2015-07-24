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

//��ʼ��������
BOOL CFileServer::InitServer()
{
      //����TCP������
    m_SvrSocket=socket(AF_INET,SOCK_STREAM,
        IPPROTO_TCP);
    if(INVALID_SOCKET==m_SvrSocket)
        return FALSE;
    
    
    //�󶨶˿ں�IP
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_FILESVR);
    addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    bind(m_SvrSocket,(SOCKADDR*)&addr,sizeof(addr));

    //����
    listen(m_SvrSocket,5);

    //�����Ⱥ�ͻ��˵��߳�
    AfxBeginThread(FileThread,this);


    return TRUE;
}


//���տͻ��˵��߳�
UINT CFileServer::FileThread(LPVOID pParam)
{
    CFileServer *pThis=(CFileServer*)pParam;
    while(1)
    {
        //�Ⱥ�ͻ��˵�����
        SOCKADDR_IN clientaddr={0};
        int nLen=sizeof(clientaddr);
        SOCKET clientsock=accept(
            pThis->m_SvrSocket,
            (SOCKADDR*)&clientaddr,
            &nLen);
        if(INVALID_SOCKET==clientsock)
            continue;
        //����ͻ��˵�����
        CHAR *pszIP=inet_ntoa(clientaddr.sin_addr);
        pThis->OnConnect(clientsock,pszIP);
    
    }


    return 0;
}

#include "FileThread.h"


void CFileServer::OnConnect(SOCKET clientsock,LPSTR pszID)
{
    //�����̲߳�����
    CFileThread *pThread=(CFileThread*)
        AfxBeginThread(RUNTIME_CLASS(CFileThread),
        THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
    //���ò���
    pThread->SetSocket(clientsock,pszID);
    //��ʼ�߳�
    pThread->ResumeThread();

   
}
