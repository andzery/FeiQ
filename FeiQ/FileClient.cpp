// FileClient.cpp: implementation of the CFileClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FeiQ.h"

#include "FileClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileClient::CFileClient()
{
    m_ClientSocket=INVALID_SOCKET;
}

CFileClient::~CFileClient()
{
    if(INVALID_SOCKET!=m_ClientSocket)
        closesocket(m_ClientSocket);
    
}


//��ʼ���ͻ���
BOOL CFileClient::InitClient()
{
    //����SOCKET
    m_ClientSocket=socket(AF_INET,SOCK_STREAM,
        IPPROTO_TCP);
    if(INVALID_SOCKET==m_ClientSocket)
        return FALSE;
    //���ӷ�����
//    ConnectServer();

    return TRUE;
}

BOOL CFileClient::ConnectServer(LPCSTR pszSvrIP)
{
     //���ӷ�����
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_FILESVR);
    addr.sin_addr.S_un.S_addr=inet_addr(pszSvrIP);
    if(SOCKET_ERROR==
        connect(m_ClientSocket,(SOCKADDR*)&addr,sizeof(addr)))
        return FALSE;

    return TRUE;

}

//�����ļ�
BOOL CFileClient::SendFile(LPCTSTR pszFilePath,
                           CStatic *pwnStaticSend,
                           CProgressCtrl *pwndProgress
                           )
{
    //��������ͷ
    NETHEADER header={0};
    header.nVersion=1;
    header.nCmdID=NETCMDID_SENDFILE;
    header.nDataLength=sizeof(SENDFILE);

    SendData(&header,sizeof(header));

    //�����ļ���Ϣ �ļ����ƺʹ�С
    CFile file;
    if(FALSE==file.Open(pszFilePath,CFile::modeRead))
        return FALSE;
    SENDFILE sendfile={0};
    strcpy(sendfile.szFileName,file.GetFileName());
    sendfile.nFileLength=file.GetLength();

    SendData(&sendfile,sizeof(sendfile));

    //�����ļ�����
    if(pwndProgress!=NULL)
    {
        pwndProgress->SetRange32(0,sendfile.nFileLength);

    }
    pwnStaticSend->SetWindowText("���ڷ���...");

    CHAR szBuf[4096]={0};
    DWORD nLeft=file.GetLength();
    while(nLeft>0)
    { //�����ȡ��������
        DWORD nSend=4096;
        if(nLeft < nSend)
        {
            nSend=nLeft;
        }
        //��ȡ����
        file.Read(szBuf,nSend);
        //��������
        SendData(szBuf,nSend);   
        //����ʣ��δ���͵�������
        nLeft=nLeft-nSend;
        if(pwndProgress!=NULL)
        {
            pwndProgress->SetPos(sendfile.nFileLength-nLeft);
                
        }
    }
    pwnStaticSend->SetWindowText("�������!");
    
    //�ر��ļ�
    file.Close();
    return TRUE;
}

BOOL CFileClient::SendData(LPVOID pData,DWORD nLen)
{
    //ѭ���������ݣ�ֱ��������
    LPSTR pTmpData=(LPSTR)pData;
    int nLeft=nLen;
    while(nLeft>0)
    {
        int nSend=send(m_ClientSocket,pTmpData,nLeft,0);

        if(SOCKET_ERROR==nSend)
            return FALSE;

        nLeft=nLeft-nSend;
        pTmpData=pTmpData+nSend;
    
    }


    return TRUE;
}