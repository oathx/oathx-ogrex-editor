#include "Stdafx.h"
#include "TCPSocket.h"

//////////////////////////////////////////////////////////////////////////

//宏定义
#define ID_SOCKET_WND				10								//SOCKET 窗口 ID
#define WM_SOCKET_NOTIFY			WM_USER+10						//SOCKET 消息

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTCPSocket, CWnd)
	ON_MESSAGE(WM_SOCKET_NOTIFY,OnSocketNotify)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

////发送字节映射表
//BYTE CTCPSocket::g_SendByteMap[256]=				
//{
//	0x70,0x2F,0x40,0x5F,0x44,0x8E,0x6E,0x45,0x7E,0xAB,0x2C,0x1F,0xB4,0xAC,0x9D,0x91,
//	0x0D,0x36,0x9B,0x0B,0xD4,0xC4,0x39,0x74,0xBF,0x23,0x16,0x14,0x06,0xEB,0x04,0x3E,
//	0x12,0x5C,0x8B,0xBC,0x61,0x63,0xF6,0xA5,0xE1,0x65,0xD8,0xF5,0x5A,0x07,0xF0,0x13,
//	0xF2,0x20,0x6B,0x4A,0x24,0x59,0x89,0x64,0xD7,0x42,0x6A,0x5E,0x3D,0x0A,0x77,0xE0,
//	0x80,0x27,0xB8,0xC5,0x8C,0x0E,0xFA,0x8A,0xD5,0x29,0x56,0x57,0x6C,0x53,0x67,0x41,
//	0xE8,0x00,0x1A,0xCE,0x86,0x83,0xB0,0x22,0x28,0x4D,0x3F,0x26,0x46,0x4F,0x6F,0x2B,
//	0x72,0x3A,0xF1,0x8D,0x97,0x95,0x49,0x84,0xE5,0xE3,0x79,0x8F,0x51,0x10,0xA8,0x82,
//	0xC6,0xDD,0xFF,0xFC,0xE4,0xCF,0xB3,0x09,0x5D,0xEA,0x9C,0x34,0xF9,0x17,0x9F,0xDA,
//	0x87,0xF8,0x15,0x05,0x3C,0xD3,0xA4,0x85,0x2E,0xFB,0xEE,0x47,0x3B,0xEF,0x37,0x7F,
//	0x93,0xAF,0x69,0x0C,0x71,0x31,0xDE,0x21,0x75,0xA0,0xAA,0xBA,0x7C,0x38,0x02,0xB7,
//	0x81,0x01,0xFD,0xE7,0x1D,0xCC,0xCD,0xBD,0x1B,0x7A,0x2A,0xAD,0x66,0xBE,0x55,0x33,
//	0x03,0xDB,0x88,0xB2,0x1E,0x4E,0xB9,0xE6,0xC2,0xF7,0xCB,0x7D,0xC9,0x62,0xC3,0xA6,
//	0xDC,0xA7,0x50,0xB5,0x4B,0x94,0xC0,0x92,0x4C,0x11,0x5B,0x78,0xD9,0xB1,0xED,0x19,
//	0xE9,0xA1,0x1C,0xB6,0x32,0x99,0xA3,0x76,0x9E,0x7B,0x6D,0x9A,0x30,0xD6,0xA9,0x25,
//	0xC7,0xAE,0x96,0x35,0xD0,0xBB,0xD2,0xC8,0xA2,0x08,0xF3,0xD1,0x73,0xF4,0x48,0x2D,
//	0x90,0xCA,0xE2,0x58,0xC1,0x18,0x52,0xFE,0xDF,0x68,0x98,0x54,0xEC,0x60,0x43,0x0F
//};
//
////接收字节映射表
//BYTE CTCPSocket::m_RecvByteMap[256]=				
//{
//	0x51,0xA1,0x9E,0xB0,0x1E,0x83,0x1C,0x2D,0xE9,0x77,0x3D,0x13,0x93,0x10,0x45,0xFF,
//	0x6D,0xC9,0x20,0x2F,0x1B,0x82,0x1A,0x7D,0xF5,0xCF,0x52,0xA8,0xD2,0xA4,0xB4,0x0B,
//	0x31,0x97,0x57,0x19,0x34,0xDF,0x5B,0x41,0x58,0x49,0xAA,0x5F,0x0A,0xEF,0x88,0x01,
//	0xDC,0x95,0xD4,0xAF,0x7B,0xE3,0x11,0x8E,0x9D,0x16,0x61,0x8C,0x84,0x3C,0x1F,0x5A,
//	0x02,0x4F,0x39,0xFE,0x04,0x07,0x5C,0x8B,0xEE,0x66,0x33,0xC4,0xC8,0x59,0xB5,0x5D,
//	0xC2,0x6C,0xF6,0x4D,0xFB,0xAE,0x4A,0x4B,0xF3,0x35,0x2C,0xCA,0x21,0x78,0x3B,0x03,
//	0xFD,0x24,0xBD,0x25,0x37,0x29,0xAC,0x4E,0xF9,0x92,0x3A,0x32,0x4C,0xDA,0x06,0x5E,
//	0x00,0x94,0x60,0xEC,0x17,0x98,0xD7,0x3E,0xCB,0x6A,0xA9,0xD9,0x9C,0xBB,0x08,0x8F,
//	0x40,0xA0,0x6F,0x55,0x67,0x87,0x54,0x80,0xB2,0x36,0x47,0x22,0x44,0x63,0x05,0x6B,
//	0xF0,0x0F,0xC7,0x90,0xC5,0x65,0xE2,0x64,0xFA,0xD5,0xDB,0x12,0x7A,0x0E,0xD8,0x7E,
//	0x99,0xD1,0xE8,0xD6,0x86,0x27,0xBF,0xC1,0x6E,0xDE,0x9A,0x09,0x0D,0xAB,0xE1,0x91,
//	0x56,0xCD,0xB3,0x76,0x0C,0xC3,0xD3,0x9F,0x42,0xB6,0x9B,0xE5,0x23,0xA7,0xAD,0x18,
//	0xC6,0xF4,0xB8,0xBE,0x15,0x43,0x70,0xE0,0xE7,0xBC,0xF1,0xBA,0xA5,0xA6,0x53,0x75,
//	0xE4,0xEB,0xE6,0x85,0x14,0x48,0xDD,0x38,0x2A,0xCC,0x7F,0xB1,0xC0,0x71,0x96,0xF8,
//	0x3F,0x28,0xF2,0x69,0x74,0x68,0xB7,0xA3,0x50,0xD0,0x79,0x1D,0xFC,0xCE,0x8A,0x8D,
//	0x2E,0x62,0x30,0xEA,0xED,0x2B,0x26,0xB9,0x81,0x7C,0x46,0x89,0x73,0xA2,0xF7,0x72
//};
//
////数据加密密钥
//const static DWORD g_dwPacketKey=0xA55AA55A;

//////////////////////////////////////////////////////////////////////////

//构造函数
CTCPSocket::CTCPSocket()
{
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;
	//m_cbSocketStatus=SHUT_REASON_NORMAL;
	m_hSocket=INVALID_SOCKET;
	m_pITCPSocketSink=NULL;
	//m_ProxyInfo.wProxyPort=0;
	//m_ProxyInfo.cbProxyType=PROXY_NONE;
	m_cbSocketStatus=SOCKET_STATUS_IDLE;
}

//析构函数
CTCPSocket::~CTCPSocket()
{
	CloseSocket();
}

//接口查询
void * __cdecl CTCPSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocket,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocket,Guid,dwQueryVer);
	return NULL;
}

//取消代理
/*void __cdecl CTCPSocket::CancelProxyServer()
{
	memset(&m_ProxyInfo,0,sizeof(m_ProxyInfo));
	m_ProxyInfo.wProxyPort=0;
	m_ProxyInfo.strHttpDomain.Empty();
	m_ProxyInfo.strProxyName.Empty();
	m_ProxyInfo.strProxyPass.Empty();
	m_ProxyInfo.strProxyServer.Empty();
	m_ProxyInfo.cbProxyType=PROXY_NONE;
	return;
}*/

//代理服务器
bool __cdecl CTCPSocket::SetProxyServerInfo(enProxyServerType ProxyServerType, const tagProxyServerInfo & ProxyServerInfo)
{
	m_ProxyServerInfo=ProxyServerInfo;
	return true;
}

//设置接口
bool __cdecl CTCPSocket::SetTCPSocketSink(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pITCPSocketSink=(ITCPSocketSink *)pIUnknownEx->QueryInterface(IID_ITCPSocketSink,VER_ITCPSocketSink);
	ASSERT(m_pITCPSocketSink!=NULL);
	return (m_pITCPSocketSink!=NULL);
}

//获取接口
void * __cdecl CTCPSocket::GetTCPSocketSink(const IID & Guid, DWORD dwQueryVer)
{
	if (m_pITCPSocketSink==NULL) return NULL;
	return m_pITCPSocketSink->QueryInterface(Guid,dwQueryVer);
}

//连接服务器
DWORD __cdecl CTCPSocket::Connect(DWORD dwServerIP, WORD wPort)
{
	//效验参数
	ASSERT(m_hSocket==INVALID_SOCKET);
	ASSERT(m_cbSocketStatus==SOCKET_STATUS_IDLE);

	//效验状态
	if (m_hSocket!=INVALID_SOCKET) throw TEXT("连接 SOCKET 句柄已经存在");
	if (m_cbSocketStatus!=SOCKET_STATUS_IDLE) throw TEXT("连接状态不是等待连接状态");
	if (dwServerIP==INADDR_NONE) throw TEXT("目标服务器地址格式不正确，请检查后再次尝试！");

	//设置参数
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0x86753182;
	m_dwRecvXorKey=0x86753182;
	m_dwSendTickCount=GetTickCount()/1000L;
	m_dwRecvTickCount=GetTickCount()/1000L;

	try
	{
		//建立 SOCKET
		m_hSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if (m_hSocket==INVALID_SOCKET) throw TEXT("SOCKET 创建失败");
		if ((m_hWnd==NULL)&&(!Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),GetDesktopWindow(),ID_SOCKET_WND,NULL)))
			throw TEXT("SOCKET 内部窗口创建失败");

		//填写服务器地址
		m_wSocketID=m_hSocket;
		SOCKADDR_IN SocketAddr;
		memset(&SocketAddr,0,sizeof(SocketAddr));
		SocketAddr.sin_family=AF_INET;
		SocketAddr.sin_port=htons(wPort);
		SocketAddr.sin_addr.S_un.S_addr=dwServerIP;

		//连接服务器
		int iErrorCode=0;
		WSASetLastError(0);
		//if (m_ProxyInfo.cbProxyType!=PROXY_NONE)
		//{
		//	throw TEXT("未支持代理服务器");
		//}
		//else
		{
			//绑定窗口
			iErrorCode=WSAAsyncSelect(m_hSocket,m_hWnd,WM_SOCKET_NOTIFY,FD_READ|FD_CONNECT|FD_CLOSE);
			if (iErrorCode==SOCKET_ERROR) throw TEXT("绑定内部窗口错误");

			//连接服务器
			iErrorCode=connect(m_hSocket,(SOCKADDR *)&SocketAddr,sizeof(SocketAddr));
			if (iErrorCode==SOCKET_ERROR)
			{
				iErrorCode=WSAGetLastError();
				if (iErrorCode!=WSAEWOULDBLOCK)
				{
					static TCHAR szBuffer[64];
					_snprintf(szBuffer,sizeof(szBuffer),TEXT("连接发生错误，错误代码 [ %d ]"),iErrorCode);
					throw szBuffer;
				}
			}

			//设置变量
			m_cbSocketStatus=SOCKET_STATUS_WAIT;
		}

		return CONNECT_SUCCESS;
	}
	catch (LPCTSTR pszError)
	{
		CloseSocket();
		throw pszError;
		return CONNECT_FAILURE;
	}
	catch (...)
	{
		CloseSocket();
		throw TEXT("连接产生未知异常错误");
		return CONNECT_EXCEPTION;
	}

	
}

//连接服务器
DWORD __cdecl CTCPSocket::Connect(const LPCTSTR szServerIP, WORD wPort)
{
	//效验数据
	ASSERT(wPort!=0);
	ASSERT(szServerIP!=NULL);
	if ((szServerIP==NULL)||(wPort==0)) return false;
	return Connect(TranslateAddr(szServerIP),wPort);
}

//发送函数
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID)
{
	return SendData(wMainCmdID,wSubCmdID,NULL,0);
}

////发送函数
//DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
//{
//	//效验状态
//	if (m_hSocket==INVALID_SOCKET) return false;
//	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return false;
//	//效验大小
//	ASSERT(wDataSize<=SOCKET_PACKET);
//	if (wDataSize>SOCKET_PACKET) return false;
//
//	char bSendBuffer[SOCKET_BUFFER];
//	UINT uSendSize=wDataSize+sizeof(NetMessageHead);
//	NetMessageHead * pNetHead=(NetMessageHead *)bSendBuffer;
//	pNetHead->wMainCmdID=wMainCmdID;
//	pNetHead->wSubCmdID=wSubCmdID;
//	pNetHead->uMessageSize=uSendSize;
//	pNetHead->cbVersion=SOCKET_VER;
//
//	if(pData!=NULL && wDataSize>0)
//	{
//		byte *pByte=(byte*)(pNetHead+1);
//		ULONG  destLen=m_Encrypt.CompressBound(wDataSize);
//		if(m_Encrypt.CompressNetData(pByte,&destLen,(BYTE *)pData,wDataSize))
//		{//压缩成功
//			uSendSize=destLen+sizeof(NetMessageHead);
//			pNetHead->uMessageSize=uSendSize;
//			pNetHead->bReserve=wDataSize;//压缩前的大小
//		}
//		else
//		{//加密
//			::CopyMemory(pByte,pData,wDataSize);
//			m_Encrypt.EncryptNetData(pByte,wDataSize);
//			pNetHead->bReserve=0;//数据未压缩
//		}
//	}
//	m_dwSendPacketCount++;
//	//发送数据
//	return SendDataBuffer(bSendBuffer,uSendSize);
//}


//发送函数
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//效验状态
	if (m_hSocket==INVALID_SOCKET) return false;
	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return false;

	//效验大小
	ASSERT(wDataSize<=SOCKET_PACKET);
	if (wDataSize>SOCKET_PACKET) return false;

	//构造数据
	BYTE cbDataBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;
	if (wDataSize>0)
	{
		ASSERT(pData!=NULL);
		CopyMemory(pHead+1,pData,wDataSize);
	}

	//加密数据
	WORD wSendSize=EncryptBuffer(cbDataBuffer,sizeof(CMD_Head)+wDataSize,sizeof(cbDataBuffer));

	//发送数据
	return SendDataBuffer(cbDataBuffer,wSendSize);
}


//关闭连接
void __cdecl CTCPSocket::CloseSocket(BYTE cbShutReason)
{
	//关闭连接
	bool bClose=(m_hSocket!=INVALID_SOCKET);
	m_cbSocketStatus=SOCKET_STATUS_IDLE;
	if (m_hSocket!=INVALID_SOCKET)
	{
		WSAAsyncSelect(m_hSocket,GetSafeHwnd(),WM_SOCKET_NOTIFY,0);
		closesocket(m_hSocket);
		m_hSocket=INVALID_SOCKET;
		m_cbSocketStatus=SOCKET_STATUS_IDLE;
	}
	if ((bClose==true)&&(m_pITCPSocketSink!=NULL))
	{
		ASSERT(m_pITCPSocketSink!=NULL);
		try 
		{
			m_pITCPSocketSink->OnEventTCPSocketShut(m_wSocketID,cbShutReason);
		}
		catch (...)
		{

		}
	}

	//恢复数据
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;
	return;
}

//发送数据
DWORD CTCPSocket::SendDataBuffer(void * pBuffer, WORD wSendSize)
{
	//效验参数
	ASSERT(wSendSize!=0);
	ASSERT(pBuffer!=NULL);
	
	//发送数据
	WORD wSended=0;
	while (wSended<wSendSize)
	{
		int iErrorCode=send(m_hSocket,(char *)pBuffer+wSended,wSendSize-wSended,0);
		if (iErrorCode==SOCKET_ERROR)
		{
			if (WSAGetLastError()==WSAEWOULDBLOCK)
			{
				m_dwSendTickCount=GetTickCount()/1000L;
				return true;
			}
			return false;
		}
		wSended+=iErrorCode;
	}
	m_dwSendTickCount=GetTickCount()/1000L;

	return true;
}

//随机映射
WORD CTCPSocket::SeedRandMap(WORD wSeed)
{
	DWORD dwHold=wSeed;
	return (WORD)((dwHold=dwHold*241103L+2533101L)>>16);
}

//映射发送数据
BYTE CTCPSocket::MapSendByte(BYTE const cbData)
{
	BYTE cbMap=g_SendByteMap[(BYTE)(cbData+m_cbSendRound)];
	m_cbSendRound+=3;
	return cbMap;
}

//映射接收数据
BYTE CTCPSocket::MapRecvByte(BYTE const cbData)
{
	BYTE cbMap=g_RecvByteMap[cbData]-m_cbRecvRound;
	m_cbRecvRound+=3;
	return cbMap;
}

//解释服务器地址
DWORD CTCPSocket::TranslateAddr(LPCTSTR pszServerAddr)
{
	//转化地址
	DWORD dwServerIP=inet_addr(pszServerAddr);
	if (dwServerIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(pszServerAddr);
		if (lpHost==NULL) return INADDR_NONE;
		dwServerIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}
	return dwServerIP;
}

//解释错误
/*LPCTSTR CTCPSocket::GetConnectError(int iErrorCode, LPTSTR pszBuffer, WORD wBufferSize)
{
	//效验参数
	ASSERT(pszBuffer!=NULL);
	if (pszBuffer==NULL) return NULL;

	//解释错误
	switch (iErrorCode)
	{
	case 0:					//没有错误
		{
			lstrcpyn(pszBuffer,TEXT("操作执行成功"),wBufferSize);
			break;
		}
	case WSAEADDRNOTAVAIL:	//地址格式错误
		{
			lstrcpyn(pszBuffer,TEXT("目标服务器地址格式不正确，请检查后再次尝试！"),wBufferSize);
			break;
		}
	case WSAECONNREFUSED:	//服务器没有启动
		{
			lstrcpyn(pszBuffer,TEXT("目标服务器繁忙或者没有启动！"),wBufferSize);
			break;
		}
	case WSAETIMEDOUT:		//连接超时
		{
			lstrcpyn(pszBuffer,TEXT("连接超时，可能是目标服务器不存在或者服务器地址格式不正确！"),wBufferSize);
			break;
		}
	case WSAEHOSTUNREACH:
		{
			lstrcpyn(pszBuffer,TEXT("网络连接失败，请检查是否已经成功拨号和连接 Internet ！"),wBufferSize);
			break;
		}
	default:				//默认错误
		{
			_snprintf(pszBuffer,wBufferSize,TEXT("连接错误号：%ld，详细错误信息请参考操作帮助手册！"),iErrorCode);
			break;
		}
	}

	return pszBuffer;
}*/
//代理测试
DWORD  CTCPSocket::ProxyServerTesting()
{
	return 0;
}

//加密数据
WORD CTCPSocket::EncryptBuffer(BYTE pcbDataBuffer[], WORD wDataSize, WORD wBufferSize)
{
	//效验参数
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(wBufferSize>=(wDataSize+2*sizeof(DWORD)));
	ASSERT(wDataSize<=(sizeof(CMD_Head)+SOCKET_PACKET));

	//调整长度
	WORD wEncryptSize=wDataSize-sizeof(CMD_Command),wSnapCount=0;
	if ((wEncryptSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wEncryptSize%sizeof(DWORD);
		memset(pcbDataBuffer+sizeof(CMD_Info)+wEncryptSize,0,wSnapCount);
	}

	//效验码与字节映射
	BYTE cbCheckCode=0;
	for (WORD i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		cbCheckCode+=pcbDataBuffer[i];
		pcbDataBuffer[i]=MapSendByte(pcbDataBuffer[i]);
	}

	//填写信息头
	CMD_Head * pHead=(CMD_Head *)pcbDataBuffer;
	pHead->CmdInfo.cbCheckCode=~cbCheckCode+1;
	pHead->CmdInfo.wPacketSize=wDataSize;
	pHead->CmdInfo.cbVersion=SOCKET_VER;

	//创建密钥
	DWORD dwXorKey=m_dwSendXorKey;
	if (m_dwSendPacketCount==0)
	{
		//生成第一次随机种子
		GUID Guid;
		CoCreateGuid(&Guid);
		dwXorKey=GetTickCount()*GetTickCount();
		dwXorKey^=Guid.Data1;
		dwXorKey^=Guid.Data2;
		dwXorKey^=Guid.Data3;
		dwXorKey^=*((DWORD *)Guid.Data4);
		
		//随机映射种子
		dwXorKey=SeedRandMap((WORD)dwXorKey);
		dwXorKey|=((DWORD)SeedRandMap((WORD)(dwXorKey>>16)))<<16;
		dwXorKey^=g_dwPacketKey;
		m_dwSendXorKey=dwXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//加密数据
	WORD * pwSeed=(WORD *)(pcbDataBuffer+sizeof(CMD_Info));
	DWORD * pdwXor=(DWORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wEncryptSize+wSnapCount)/sizeof(DWORD);
	for (i=0;i<wEncrypCount;i++)
	{
		*pdwXor++^=dwXorKey;
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
	}

	//插入密钥
	if (m_dwSendPacketCount==0)
	{
		MoveMemory(pcbDataBuffer+sizeof(CMD_Head)+sizeof(DWORD),pcbDataBuffer+sizeof(CMD_Head),wDataSize);
		*((DWORD *)(pcbDataBuffer+sizeof(CMD_Head)))=m_dwSendXorKey;
		pHead->CmdInfo.wPacketSize+=sizeof(DWORD);
		wDataSize+=sizeof(DWORD);
	}

	//设置变量
	m_dwSendPacketCount++;
	m_dwSendXorKey=dwXorKey;

	return wDataSize;
}

//解密数据
WORD CTCPSocket::CrevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize)
{
	//效验参数
	ASSERT(m_dwSendPacketCount>0);
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(((CMD_Head *)pcbDataBuffer)->CmdInfo.wPacketSize==wDataSize);

	//调整长度
	WORD wSnapCount=0;
	if ((wDataSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wDataSize%sizeof(DWORD);
		memset(pcbDataBuffer+wDataSize,0,wSnapCount);
	}

	//解密数据
	DWORD dwXorKey=m_dwRecvXorKey;
	DWORD * pdwXor=(DWORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD  * pwSeed=(WORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wDataSize+wSnapCount-sizeof(CMD_Info))/4;
	for (WORD i=0;i<wEncrypCount;i++)
	{
		if ((i==(wEncrypCount-1))&&(wSnapCount>0))
		{
			BYTE * pcbKey=((BYTE *)&m_dwRecvXorKey)+sizeof(DWORD)-wSnapCount;
			CopyMemory(pcbDataBuffer+wDataSize,pcbKey,wSnapCount);
		}
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
		*pdwXor++^=m_dwRecvXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//效验码与字节映射
	CMD_Head * pHead=(CMD_Head *)pcbDataBuffer;
	BYTE cbCheckCode=pHead->CmdInfo.cbCheckCode;
	for (int i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		pcbDataBuffer[i]=MapRecvByte(pcbDataBuffer[i]);
		cbCheckCode+=pcbDataBuffer[i];
	}
	if (cbCheckCode!=0) throw TEXT("数据包效验码错误");

	return wDataSize;
}

//网络连接
LRESULT CTCPSocket::OnSocketNotifyConnect(WPARAM wParam, LPARAM lParam)
{
	//判断状态
	int iErrorCode=WSAGETSELECTERROR(lParam);
	if (iErrorCode==0) m_cbSocketStatus=SOCKET_STATUS_CONNECT;
	else CloseSocket();

	//发送通知
	//TCHAR szErrorDesc[128]=TEXT("");
	//GetConnectError(iErrorCode,szErrorDesc,sizeof(szErrorDesc));
	m_pITCPSocketSink->OnEventTCPSocketLink(m_wSocketID,iErrorCode);

	return 1;
}
//
////网络读取
//LRESULT CTCPSocket::OnSocketNotifyRead(WPARAM wParam, LPARAM lParam)
//{
//	try
//	{
//		TCHAR Temp[255];
//		int nErrPos = 0;
////#ifdef _DEBUG
//		sprintf(Temp,"错误ID:%d \r\n",nErrPos);
//		OutputDebugString(Temp);
////#endif
//		//读取数据
//		int iRetCode=recv(m_hSocket,(char *)m_cbRecvBuf+m_wRecvSize,sizeof(m_cbRecvBuf)-m_wRecvSize,0);
//		if (iRetCode==SOCKET_ERROR) 
//			throw TEXT("网络连接关闭，读取数据失败");
//		ASSERT(m_dwSendPacketCount>0);
//		m_wRecvSize+=iRetCode;
//		m_dwRecvTickCount=GetTickCount()/1000L;
//
//		 nErrPos = 1;
////#ifdef _DEBUG
//		sprintf(Temp,"错误ID:%d \r\n",nErrPos);
//		OutputDebugString(Temp);
////#endif
//		WORD wPacketSize=0;
//		BYTE cbDataBuffer[SOCKET_PACKET+sizeof(NetMessageHead)];
//		do
//		{
//			//#ifdef _DEBUG
//			sprintf(Temp,"准备解析数据 \r\n",nErrPos);
//			OutputDebugString(Temp);
//			//#endif
//			NetMessageHead * pNetHead=(NetMessageHead *)m_cbRecvBuf;
//			if ((m_wRecvSize<sizeof(NetMessageHead))||(m_wRecvSize<(int)pNetHead->uMessageSize))
//			{
//				throw TEXT("数据包非法");
//				return 0;
//			}
//			CMD_Command Command;
//			Command.wMainCmdID = pNetHead->wMainCmdID;
//			Command.wSubCmdID = pNetHead->wSubCmdID;
//			UINT uMessageSize=pNetHead->uMessageSize;
//			nErrPos = 2;
////#ifdef _DEBUG
//			sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//			OutputDebugString(Temp);
////#endif
//			if (uMessageSize>sizeof(cbDataBuffer)) 
//				throw TEXT("数据包过大");
//			::CopyMemory(cbDataBuffer,m_cbRecvBuf,uMessageSize);
//			m_wRecvSize-=uMessageSize;
//			::MoveMemory(m_cbRecvBuf,m_cbRecvBuf+uMessageSize,(m_wRecvSize)*sizeof(BYTE));
//
//			UINT uHandleSize=uMessageSize-sizeof(NetMessageHead);
//			NetMessageHead * pHandleNetData=(NetMessageHead *)cbDataBuffer;
//
//			nErrPos = 3;
////#ifdef _DEBUG
//			sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//			OutputDebugString(Temp);
////#endif
//			byte *pDestBuff=NULL;
//			ULONG  destLen=0;
//			if(uHandleSize>0)
//			{
//				byte *pByte=(byte*)(pHandleNetData+1);
//				DWORD  dwSourSize=pHandleNetData->bReserve;
//				if(dwSourSize>=SOCKET_PACKET)
//				{
//					ASSERT(false);
//					return 0;
//				}
//
//				if(dwSourSize>0)
//				{/*网络数据解压缩*/
//					pDestBuff=new byte[dwSourSize];
//					if(pDestBuff==NULL)
//					{
//						ASSERT(false);
//						return 0;
//					}
//
//					destLen=dwSourSize;
//					nErrPos = 4;
////#ifdef _DEBUG
//					sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//					OutputDebugString(Temp);
////#endif
//					if(m_Encrypt.UnCompressNetData(pDestBuff,&destLen,(BYTE *)pByte,uHandleSize) && dwSourSize==destLen)
//					{//解压成功
//						pHandleNetData->uMessageSize=destLen+sizeof(NetMessageHead);
//						uHandleSize=destLen;
//					}
//					else
//					{
//						delete [] pDestBuff;
//						ASSERT(false);
//						return 0;
//					}
//					nErrPos = 5;
////#ifdef _DEBUG
//					sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//					OutputDebugString(Temp);
////#endif
//				}
//				else
//				{//解密
//					m_Encrypt.DecryptNetData(pByte,uHandleSize);
//				}
//				nErrPos = 6;
////#ifdef _DEBUG
//				sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//				OutputDebugString(Temp);
////#endif
//			}
//			char *pTempBuff=NULL;
//			if(uHandleSize>0)
//			{
//				if(pDestBuff==NULL)
//					pTempBuff=(char*)(pHandleNetData+1);
//				else
//					pTempBuff=(char*)pDestBuff;
//			}
//			//内核命令
//			if (Command.wMainCmdID==MDM_KN_COMMAND)
//			{
//				switch (Command.wSubCmdID)
//				{
//				case SUB_KN_DETECT_SOCKET:	//网络检测
//					{
//						//发送数据
//						SendData(MDM_KN_COMMAND,SUB_KN_DETECT_SOCKET,pTempBuff,uHandleSize);
//						delete []pDestBuff;
//						break;
//					}
//				}
//				delete []pDestBuff;
//				continue;
//			}
//			nErrPos = 7;
////#ifdef _DEBUG
//			sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//			OutputDebugString(Temp);
////#endif
//			//处理数据
//			bool bSuccess=m_pITCPSocketSink->OnEventTCPSocketRead(m_wSocketID,Command,pTempBuff,uHandleSize);
//			delete []pDestBuff;
//			if (bSuccess==false) 
//				throw TEXT("网络数据包处理失败");
//			nErrPos = 8;
////#ifdef _DEBUG
//			sprintf(Temp,"错误ID:%d -- 主ID：%d  -- 子ID：%d --  数据包大小：%d\r\n",nErrPos,pNetHead->wMainCmdID,pNetHead->wSubCmdID,pNetHead->uMessageSize);
//			OutputDebugString(Temp);
////#endif
//		} while (m_wRecvSize>=sizeof(NetMessageHead));
//	}
//	catch (...) 
//	{ 
////#ifdef _DEBUG
//		OutputDebugString("-----------------------异常了！\r\n");
////#endif
//		CloseSocket(); 
//	}
//	return 1;
//}


//网络读取
LRESULT CTCPSocket::OnSocketNotifyRead(WPARAM wParam, LPARAM lParam)
{
	try
	{
		//读取数据
		int iRetCode=recv(m_hSocket,(char *)m_cbRecvBuf+m_wRecvSize,sizeof(m_cbRecvBuf)-m_wRecvSize,0);
		if (iRetCode==SOCKET_ERROR) throw TEXT("网络连接关闭，读取数据失败");
		ASSERT(m_dwSendPacketCount>0);
		m_wRecvSize+=iRetCode;
		m_dwRecvTickCount=GetTickCount()/1000L;

		//变量定义
		WORD wPacketSize=0;
		BYTE cbDataBuffer[SOCKET_PACKET+sizeof(CMD_Head)];
		CMD_Head * pHead=(CMD_Head *)m_cbRecvBuf;

		while (m_wRecvSize>=sizeof(CMD_Head))
		{
			//效验参数
			wPacketSize=pHead->CmdInfo.wPacketSize;
			ASSERT(pHead->CmdInfo.cbVersion==SOCKET_VER);
			ASSERT(wPacketSize<=(SOCKET_PACKET+sizeof(CMD_Head)));
			if (pHead->CmdInfo.cbVersion!=SOCKET_VER) throw TEXT("数据包版本错误");
			if (wPacketSize>(SOCKET_PACKET+sizeof(CMD_Head))) throw TEXT("数据包太大");
			if (m_wRecvSize<wPacketSize) return 1;

			//拷贝数据
			m_dwRecvPacketCount++;
			CopyMemory(cbDataBuffer,m_cbRecvBuf,wPacketSize);
			m_wRecvSize-=wPacketSize;
			MoveMemory(m_cbRecvBuf,m_cbRecvBuf+wPacketSize,m_wRecvSize);

			//解密数据
			WORD wRealySize=CrevasseBuffer(cbDataBuffer,wPacketSize);
			ASSERT(wRealySize>=sizeof(CMD_Head));

			//解释数据
			WORD wDataSize=wRealySize-sizeof(CMD_Head);
			void * pDataBuffer=cbDataBuffer+sizeof(CMD_Head);
			CMD_Command Command=((CMD_Head *)cbDataBuffer)->CommandInfo;

			//内核命令
			if (Command.wMainCmdID==MDM_KN_COMMAND)
			{
				switch (Command.wSubCmdID)
				{
				case SUB_KN_DETECT_SOCKET:	//网络检测
					{
						//发送数据
						SendData(MDM_KN_COMMAND,SUB_KN_DETECT_SOCKET,pDataBuffer,wDataSize);
						break;
					}
				}
				continue;
			}

			//处理数据
			bool bSuccess=m_pITCPSocketSink->OnEventTCPSocketRead(m_wSocketID,Command,pDataBuffer,wDataSize);
			if (bSuccess==false) throw TEXT("网络数据包处理失败");
		};
	}
	catch (...) 
	{ 
		CloseSocket(); 
	}

	return 1;
}


//网络关闭
LRESULT CTCPSocket::OnSocketNotifyClose(WPARAM wParam, LPARAM lParam)
{
	//m_cbSocketStatus=SHUT_REASON_NORMAL;
#ifdef _DEBUG
	OutputDebugString("收到服务器socket断开\r\n");
#endif
	CloseSocket(SHUT_REASON_REMOTE);
	return 1;
}

//SOCKET 消息处理程序
LRESULT	CTCPSocket::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:	//网络连接
		{ 
			return OnSocketNotifyConnect(wParam,lParam); 
		}
	case FD_READ:		//数据读取
		{ 
			return OnSocketNotifyRead(wParam,lParam); 
		}
	case FD_CLOSE:		//网络关闭
		{ 
			return OnSocketNotifyClose(wParam,lParam);	
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

//建立对象函数
DECLARE_CREATE_MODULE(TCPSocket)
/*extern "C" __declspec(dllexport) void * __cdecl CreateTCPSocket(const GUID & Guid, DWORD dwInterfaceVer)
{
	//建立对象
	CTCPSocket * pTCPSocket=NULL;
	try
	{
		pTCPSocket=new CTCPSocket();
		if (pTCPSocket==NULL) throw TEXT("创建失败");
		void * pObject=pTCPSocket->QueryInterface(Guid,dwInterfaceVer);
		if (pObject==NULL) throw TEXT("接口查询失败");
		return pObject;
	}
	catch (...) {}

	//清理对象
	SafeDelete(pTCPSocket);
	return NULL;
}*/

//////////////////////////////////////////////////////////////////////////
