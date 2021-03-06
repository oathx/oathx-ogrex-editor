#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("GamePlaza");						//广场类名
const TCHAR SZ_PLAZANAME[]	=	TEXT("YouLe");


#define CAPTION_SIZE						35							//标题大小

#define LESS_SCREEN_CY						738							//最小高度
#define LESS_SCREEN_CX						1024						//最小宽度
//#define CAPTION_SIZE						79							//标题大小

//圆角大小
#define ROUND_CX							5							//圆角宽度
#define ROUND_CY							5							//圆角高度
//阴影定义
#define SHADOW_CX							1							//阴影宽度
#define SHADOW_CY							1							//阴影高度

//头像大小
#define FACE_CX					48						//头像宽度
#define FACE_CY					48						//头像高度

//性别定义
#define GENDER_FEMALE			0						//女性性别
#define GENDER_MANKIND			1						//男性性别

// 视图页面创建的个数
#define MAX_GICOL							3
#define MAX_GIROW							3

//GameItem偏移量
#define GTP_OFFSETX							5
#define GTP_OFFSETY							45

//按钮ID 对应相应page
#define IDC_BT_GAME							100							//游戏专区
#define IDC_BT_MATCH						101							//比赛专区
#define IDC_BT_PROPERTY						102							//道具商城
#define IDC_BT_PRIZE						103							//奖品中心
#define IDC_BT_RECHARGE						104							//充值中心

//用户中心page按钮
#define IDC_BT_USERSET						105							//用户信息
#define IDC_BT_REFLASH						106							//信息刷新
#define IDC_BT_USERBAG						107							//角色背包
#define IDC_BT_SQUARE						108							
#define IDC_BT_TILL							109
#define IDC_BT_IM							110

//视图对应ID
#define IDP_GAME_VIEW						55530						//导航游戏对应界面
#define IDP_MATCH_VIEW						55529	
#define IDP_PROPERTY_VIEW					55528
#define IDP_PRIZE_VIEW						55527
#define IDP_RECHARGE_VIEW					55526
#define IDP_USERSET_VIEW					55525

//用户设置按钮
#define IDC_BT_MODIFY_USER					300							//更改用户
#define IDC_BT_MODIFY_INFO					301							//更改资料
#define IDC_BT_MODIFY_PASSWORD				302							//更改密码

#define IDC_BT_MD_USERINFO_OK				303							//修改用户资料确认
#define IDC_BT_MD_USERINFO_CANCEL			304							//取消用户资料修改

#define IDC_BT_MD_PASSWORD_OK				305							//确认修改用户密码
#define IDC_BT_MD_PASSWORD_CANCEL			306							//取消修改用户密码

// 返回按钮ID
#define IDB_GPRETURN						45535

//////////////////////////////////////////////////////////////////////////
//大厅UI位置
#define PGP_OFFSETX							222
#define PGP_OFFSETY							147
#define PGP_WITH							580
#define	PGP_HEIGHT							591

//用户UI位置
#define PUP_OFFSETX							0
#define PUP_OFFSETY							147
#define PUP_WITH							222
#define PUP_HEIGHT							591


//////////////////////////////////////////////////////////////////////////
//UI指令
#define WM_SHOW_USERSET						WM_USER + 1					//打开用户设置
#define	WM_SHOW_GAMEPAGE					WM_USER + 2
#define	WM_CREATEGAMETABLE					WM_USER + 3					//创建游戏桌子	

#define WM_SHOW_FRAMECLOSE					WM_USER + 101
#define WM_CLOSE_FRAME						WM_USER + 102
#define WM_SWITCH_ACCOUNT					WM_USER + 103
#define WM_START_KEYBOSS					WM_USER + 104
#define WM_SAVE_KEYBOSS						WM_USER + 105
#endif