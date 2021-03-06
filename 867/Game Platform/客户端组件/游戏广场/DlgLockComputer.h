#ifndef CUSTOM_LOCKCOMPUTER_FILE
#define CUSTOM_LOCKCOMPUTER_FILE

#pragma once
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

//锁机功能
class CDlgLockComputer : public CSkinPngDialog 
{
	//变量定义
protected:
	enOperateStatus				m_enOperateStatus;					//状态变量
	CBrush						m_brBkground;						//背景刷子

	//控件变量
protected:
	CSkinButton					m_btOk;								//确定锁机
	ITCPSocket					* m_pIClientSocket;					//网络组件
	TCHAR						m_szLogonPws[PASS_LEN];				//游戏密码

	//函数定义
public:
	//构造函数
	CDlgLockComputer(CWnd* pParent = NULL);
	//虚构函数
	virtual ~CDlgLockComputer();

	//函数定义
public:
	//发送数据
	bool SendData();

	//函数定义
protected:
	//交换函数
	virtual void DoDataExchange(CDataExchange* pDX);
	//初始函数
	virtual BOOL OnInitDialog();

	//辅助函数
public:
	//显示消息
	void ShowMessage(TCHAR *pMessage);
	//网络链接
	bool ConnectServer();
	//更新控件
	void UpdateControls();
	//设置状态
	void SetStatus(enOperateStatus enOperateStatus){m_enOperateStatus = enOperateStatus;}

	//消息函数
protected:
	//确定
	afx_msg void OnBnClickedOK();
	//绘画函数
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	//销毁消息
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////////

#endif