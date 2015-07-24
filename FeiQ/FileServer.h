// FileServer.h: interface for the CFileServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESERVER_H__89BF1999_1276_4721_B3C5_2219995AF1DD__INCLUDED_)
#define AFX_FILESERVER_H__89BF1999_1276_4721_B3C5_2219995AF1DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileServer  
{
public:
	CFileServer();
	virtual ~CFileServer();
public:
    //初始化服务器
    BOOL InitServer();
    //接收客户端的线程
    static UINT FileThread(LPVOID pParam);
    //处理客户端连接
    void OnConnect(SOCKET clientsock,LPSTR pszID);
public:
    SOCKET m_SvrSocket;

};

#endif // !defined(AFX_FILESERVER_H__89BF1999_1276_4721_B3C5_2219995AF1DD__INCLUDED_)
