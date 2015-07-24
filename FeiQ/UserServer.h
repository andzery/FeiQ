// UserServer.h: interface for the CUserServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSERVER_H__015E20C2_18EE_4D46_BB1F_34BDB0DECEA3__INCLUDED_)
#define AFX_USERSERVER_H__015E20C2_18EE_4D46_BB1F_34BDB0DECEA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UserView.h"
#include "ChatView.h"
class CUserServer  
{
public:
	CUserServer();
	virtual ~CUserServer();
    
public:
    //初始化User服务器
    BOOL InitServer();
    //接收数据的线程
    static UINT UserThread(LPVOID pParam);
    //处理用户信息数据
    BOOL OnUserBroadcast(
        LPUSERBROADCAST pUserBroadcast,
        CHAR *pszIP
        );
    //处理用户退出
    BOOL OnUserQuit(LPUSERQUIT pUserQuit,CHAR * pszIP);
    //聊天
    BOOL OnUserChat(LPUSERCHAT pUserChat,
        CHAR* pszIP);

public:
    SOCKET m_SvrSocket;
    CUserView *m_pUserView;
    CChatView *m_pChatView;
};

#endif // !defined(AFX_USERSERVER_H__015E20C2_18EE_4D46_BB1F_34BDB0DECEA3__INCLUDED_)
