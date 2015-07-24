#ifndef _FEIQDEF_H_
#define _FEIQDEF_H_

#define PORT_USERSVR  5681  //UDP
#define PORT_FILESVR  5682  //TCP

//#pragma pack(1)字节对齐的方式，1是单字节对齐

//数据包的包头
typedef struct _tagNetHeader
{
    DWORD nVersion;
    DWORD nCmdID;
    DWORD nDataLength;


}NETHEADER,LPNETHEADER;

//标准UDP数据报
typedef struct _tagUDPPacket
{
    NETHEADER header;
    CHAR szData[256];

}UDPPACKET,LPUDPPACKET;

//用户广播数据  数据包
#define NETCMDID_USERBROADCAST  0x00000001
typedef struct _tagUserBroadcast
{
    NETHEADER header;
    CHAR szName[128];
    CHAR szSign[128];

}USERBROADCAST,*LPUSERBROADCAST;

//用户退出数据
#define NETCMDID_USERQUIT  0x00000002
typedef struct _tagUserQuit
{
    NETHEADER header;
    DWORD nExitCode;

}USERQUIT,*LPUSERQUIT;


//聊天数据
#define NETCMDID_USERCHAT  0x00000003
typedef struct _tagUserChat
{
    NETHEADER header;
    CHAR szChat[256];

}USERCHAT,*LPUSERCHAT;

//发送文件
#define NETCMDID_SENDFILE 0x00000004
typedef struct _tagSendFile
{
    CHAR szFileName[256];
    DWORD nFileLength;

}SENDFILE,*LPSENDFILE;

#endif //_FEIQDEF_H_