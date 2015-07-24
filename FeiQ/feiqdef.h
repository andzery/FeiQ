#ifndef _FEIQDEF_H_
#define _FEIQDEF_H_

#define PORT_USERSVR  5681  //UDP
#define PORT_FILESVR  5682  //TCP

//#pragma pack(1)�ֽڶ���ķ�ʽ��1�ǵ��ֽڶ���

//���ݰ��İ�ͷ
typedef struct _tagNetHeader
{
    DWORD nVersion;
    DWORD nCmdID;
    DWORD nDataLength;


}NETHEADER,LPNETHEADER;

//��׼UDP���ݱ�
typedef struct _tagUDPPacket
{
    NETHEADER header;
    CHAR szData[256];

}UDPPACKET,LPUDPPACKET;

//�û��㲥����  ���ݰ�
#define NETCMDID_USERBROADCAST  0x00000001
typedef struct _tagUserBroadcast
{
    NETHEADER header;
    CHAR szName[128];
    CHAR szSign[128];

}USERBROADCAST,*LPUSERBROADCAST;

//�û��˳�����
#define NETCMDID_USERQUIT  0x00000002
typedef struct _tagUserQuit
{
    NETHEADER header;
    DWORD nExitCode;

}USERQUIT,*LPUSERQUIT;


//��������
#define NETCMDID_USERCHAT  0x00000003
typedef struct _tagUserChat
{
    NETHEADER header;
    CHAR szChat[256];

}USERCHAT,*LPUSERCHAT;

//�����ļ�
#define NETCMDID_SENDFILE 0x00000004
typedef struct _tagSendFile
{
    CHAR szFileName[256];
    DWORD nFileLength;

}SENDFILE,*LPSENDFILE;

#endif //_FEIQDEF_H_