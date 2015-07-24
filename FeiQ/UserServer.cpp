// UserServer.cpp: implementation of the CUserServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FeiQ.h"
#include "UserServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserServer::CUserServer()
{
    m_pUserView=NULL;
    m_pChatView=NULL;
}

CUserServer::~CUserServer()
{

}

//初始化User服务器
BOOL CUserServer::InitServer()
{
    //创建UDP服务器
    m_SvrSocket=socket(AF_INET,SOCK_DGRAM,
        IPPROTO_UDP);
    //绑定端口和IP
    struct sockaddr_in addr={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_USERSVR);
    addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    bind(m_SvrSocket,(struct sockaddr*)&addr,sizeof(addr));
    //创建服务器线程
    AfxBeginThread(UserThread,this);

    return TRUE;
}


//接收数据的线程
UINT CUserServer::UserThread(LPVOID pParam)
{
    CUserServer *pThis=(CUserServer*)pParam;
    
    while(1)
    {
        //接收客户端的数据(UDP)
        UDPPACKET packet={0};
        struct sockaddr_in addr={0};
        int nLen=sizeof(addr);
        recvfrom(pThis->m_SvrSocket,
            (char*)&packet,sizeof(packet),0,
            (struct sockaddr*)&addr,
            &nLen);
        char* pszIP=inet_ntoa(addr.sin_addr);

        //分发和处理数据
        switch(packet.header.nCmdID)
        {
        case NETCMDID_USERBROADCAST:
            pThis->OnUserBroadcast(
                (LPUSERBROADCAST)&packet,pszIP);
            break;
        case NETCMDID_USERQUIT:
            pThis->OnUserQuit((LPUSERQUIT)&packet,pszIP);
            break;  
        case NETCMDID_USERCHAT:
            pThis->OnUserChat((LPUSERCHAT)&packet,pszIP);
            break;
        }

    }
    return 0;
}

BOOL CUserServer::OnUserBroadcast(
        LPUSERBROADCAST pUserBroadcast,
        CHAR *pszIP
        )
{
    //将用户添加到UserView窗口
    if(m_pUserView!=NULL)
    {
        m_pUserView->AddUser(pUserBroadcast->szName,
            pszIP,pUserBroadcast->szSign);
    
    }
    if(m_pChatView!=NULL)
    {
        m_pChatView->AddUser(pszIP);
    }

    return TRUE;
}

BOOL CUserServer::OnUserQuit(LPUSERQUIT pUserQuit,CHAR * pszIP)
{
    if(m_pUserView!=NULL)
    {
        m_pUserView->DelUser(pszIP);
    
    }

    if(m_pChatView!=NULL)
    {
        m_pChatView->DelUser(pszIP);
    
    }

    return TRUE;
}

BOOL CUserServer::OnUserChat(LPUSERCHAT pUserChat,
        CHAR* pszIP)
{
    if(m_pChatView!=NULL)
    {
        m_pChatView->AddChat(pUserChat->szChat,pszIP);
    
    }
    
    return TRUE;
}