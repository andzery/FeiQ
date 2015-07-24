// UserClient.h: interface for the CUserClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERCLIENT_H__3BDEA98B_7312_470F_9230_CB3BE642FE14__INCLUDED_)
#define AFX_USERCLIENT_H__3BDEA98B_7312_470F_9230_CB3BE642FE14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserClient  
{
public:
	CUserClient();
	virtual ~CUserClient();

public:
    //��ʼ���ͻ���
    BOOL InitClient();
    //�㲥����
    BOOL Broadcast();
    //�˳�����
    BOOL UserQuit();
    //����
    BOOL SendChat(CString strIP,
        CString strData,BOOL bBroadcast=TRUE);
    //��������
    BOOL SendData(CHAR *pszData,UINT nLen,
        LPCSTR pszIP=NULL);

public:
    SOCKET m_ClientSocket;

};

#endif // !defined(AFX_USERCLIENT_H__3BDEA98B_7312_470F_9230_CB3BE642FE14__INCLUDED_)
