// FileClient.h: interface for the CFileClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECLIENT_H__C3B1407C_AFB9_4669_A1EB_6D3A2A600BBF__INCLUDED_)
#define AFX_FILECLIENT_H__C3B1407C_AFB9_4669_A1EB_6D3A2A600BBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileClient  
{
public:
	CFileClient();
	virtual ~CFileClient();
public:
    //初始化客户端
    BOOL InitClient();
    //连接服务器
    BOOL ConnectServer(LPCSTR pszSvrIP);
    //发送文件
    BOOL SendFile(LPCTSTR pszFilePath,CStatic *pwnStaticSend,
        CProgressCtrl *pwndProgress=NULL);
    //发送数据
    BOOL SendData(LPVOID pData,DWORD nLen);

public:
    SOCKET m_ClientSocket;
   
};

#endif // !defined(AFX_FILECLIENT_H__C3B1407C_AFB9_4669_A1EB_6D3A2A600BBF__INCLUDED_)
