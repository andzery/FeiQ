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

//��ʼ��User������
BOOL CUserServer::InitServer()
{
    //����UDP������
    m_SvrSocket=socket(AF_INET,SOCK_DGRAM,
        IPPROTO_UDP);
    //�󶨶˿ں�IP
    struct sockaddr_in addr={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_USERSVR);
    addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    bind(m_SvrSocket,(struct sockaddr*)&addr,sizeof(addr));
    //�����������߳�
    AfxBeginThread(UserThread,this);

    return TRUE;
}


//�������ݵ��߳�
UINT CUserServer::UserThread(LPVOID pParam)
{
    CUserServer *pThis=(CUserServer*)pParam;
    
    while(1)
    {
        //���տͻ��˵�����(UDP)
        UDPPACKET packet={0};
        struct sockaddr_in addr={0};
        int nLen=sizeof(addr);
        recvfrom(pThis->m_SvrSocket,
            (char*)&packet,sizeof(packet),0,
            (struct sockaddr*)&addr,
            &nLen);
        char* pszIP=inet_ntoa(addr.sin_addr);

        //�ַ��ʹ�������
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
    //���û���ӵ�UserView����
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