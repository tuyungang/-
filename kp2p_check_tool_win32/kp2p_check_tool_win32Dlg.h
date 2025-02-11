﻿
// kp2p_check_tool_win32Dlg.h : Í·ÎÄ¼þ
//

#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <getopt/getopt.h>
#include <Iptypes.h>
#include <iphlpapi.h>
#include <kp2psdk.h>
#include <string.h>
#include <semaphore.h>
#include <exception>
//#include <stdbool.h>

#include "DevConfigDlg.h"
#include "DevStatusDlg.h"
#include "KQueryDevInfoDetailDlg.h"
#include "KpingDlg.h"
#include "KdevSettingDlg.h"
#include "KliveDlg.h"
#include "KvideoDlg.h"
#include "GenReportDlg.h"
#include "KdevSysTimeSettingDlg.h"
#include "KdevStatusInfoDetailDlg.h"
#include "KTestCmdDlg.h"
#include "ParseJson.h"
//#include "DevInfoDetailDlg.h"

#include "iot_shell.h"
#include "iot_shell_def.h"
#include "md5.h"

#include "Util.h"

using namespace std;

class CDevSysInfoObject;
class CDevStatusInfoObject;

class Ckp2p_check_tool_win32Dlg : public CDialogEx
{

public:
	Ckp2p_check_tool_win32Dlg(CWnd* pParent = NULL);	


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KP2P_CHECK_TOOL_WIN32_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	



protected:
	HICON m_hIcon;
	
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT  OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	CSplitterWnd m_wndSplitter;
public:
	//afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedConnectButton();
	afx_msg void OnBnClickedOk();

public:
	enum TEST_DEV_ITEM_TYPE { DEV_CONFIG = 1, DEV_STATUS };

public:
	CString   m_EditDevID;
	CString   m_EditDevUser;
	CString   m_EditDevPassword;
	CString   m_EditSvrUser;
	CString   m_EditSvrPassword;
	CString   m_LableCurGateWay;
	CString   m_LableCurDNS;
	CString   m_LableCurMTU;
	CComboBox m_comboBoxTestItem;
	CComboBox m_ComboBoxDevIDItem;
	CComboBox m_ComboBoxDevUserItem;
	CComboBox m_ComboBoxSvrUserItem;
	CListBox  m_ListBoxTestItem;
	CCheckListBox  m_CheckListBoxTestItem;
	CListBox  m_ListBoxStatusShow;
	CTabCtrl  m_TabCtrlInfo;
	CStatic   m_LableCurMAC;

	CButton   *m_BtnStartCheck;
	CButton   *m_BtnStopCheck;
	CButton   *m_BtnStartTest;
	CButton   *m_BtnConnect;
	CButton   *m_BtnDisconnect;
	CButton   *m_BtnDevCfgModify;
	CButton   *m_BtnVideo;
	CButton   *m_BtnLive;
	CButton   *m_BtnGetDEVStatusInfo;
	CButton   *m_BtnDevSysTimeModify;
	CButton   *m_BtnRestartDev;
	CButton   *m_BtnRemoteSetting;
	CButton   *m_BtnExportData;

	CListCtrl  m_listData;
	CStatusBar m_Statusbar;

	//查询设备信息
	CDevStatusInfoObject m_CurStatusInfo;
	CDevSysInfoObject m_CurSysInfo;

	//缓存数据
	vector<CString>                  m_TestItemVec;
	vector<CString>                  m_TestStatusItemVec;
	vector<CString>                  m_TestFuncItemVec;
	map<LONG64, pkp2p_dev_config_t>	 m_DevConfigInfoMap;
	map<LONG64, pkp2p_dev_status_t>  m_DevStatusInfoMap;
	vector<MyAdpterInfo>             m_AdpterInfo;
	vector<CString>					 m_DevIDHistoryVec;
	vector<CString>                  m_DevUserHistoryVec;
	vector<CString>                  m_SvrUserHistoryVec;

	static INT           m_nConfigItemCount;
	INT                  m_nCurConfigItemCount;
	static INT           m_nStatusItemCount;
	INT                  m_nCurStatusItemCount;
	static BOOL          m_bInitInfoPage0;
	static BOOL          m_bInitInfoPage1;
	static BOOL          m_bShellLogin;
	void                 *m_Session;
	iot_shell_t          *m_Shell;
	BOOL                 m_bOnDataFlag;
	MD5_CTX              m_Md5;
	auth_psd_req_data_t  m_ReqData;
	static int           m_Ecode;
	static Ckp2p_check_tool_win32Dlg *m_This;
	static FILE                      *dumpFp[64];
	char                             m_sdns[1024 * 4];
	kp2p_handle_t                    m_Handle;
	INT                              m_Channel;
	HANDLE                           m_ExecHandleThr;
	HANDLE                           m_ModHandleThr;
	HANDLE                           m_CacheHandleThr;
	HANDLE                           m_LoginHistoryCacheHandleThr;
	HANDLE                           m_OperateControlHandleThr;
	HANDLE                           m_CheckDevOfflineStatusHandleThr;
	HANDLE						     m_ThreadNotifyCmdEvent;
	HANDLE                           m_DevOfflineNotifyEvent;
	HANDLE                           m_TerminateCheckNotifyEvent;
	HANDLE                           m_QueryDevInfoHistoryCacheThreadUpdateEvent;
	HANDLE                           m_CheckDevOfflineStatusThreadStartEvent;
	HANDLE                           m_CheckDevOfflineStatusThreadExitEvent;

	static sem_t					 m_EndNotifySem;
	BOOL                             m_bQueryModDevConfigInfoFlag;

	static volatile LONG			 m_OnDataFlagCountLock;

	PMIB_TCPTABLE_OWNER_PID			 m_pTcpTable;

	class MyException : public exception
	{
	public:
		MyException() : exception() {}
		const char *what()const throw() { return "ERROR!, something wrong happened!"; }
	};

public:
	CDevStatusDlg             m_DevStatusDlg;
	CDevConfigDlg             m_DevConfigDlg;
	CKQueryDevInfoDetailDlg   m_QueryDevInfoDlg;
	CKpingDlg                 m_PingSettingDlg;
	CKdevSettingDlg           m_DevSettingDlg;
	CKvideoDlg                m_VideoDlg;
	CKliveDlg                 m_LiveDlg;
	CGenReportDlg             m_GenReportDlg;
	CKdevSysTimeSettingDlg    m_DevSysTimeSettingDlg;
	CKdevStatusInfoDetailDlg  m_DevStatusInfoDetailDlg;
	CKTestCmdDlg              m_TestCmdDlg;
	//CDevInfoDetailDlg m_DevInfoDetailDlg;
	
private:
	BOOL                     m_bReadyStartFlag;
	BOOL                     m_bReadyLoadFlag;
	BOOL                     m_bDevConnectStatusFlag;
	BOOL                     m_bShellSendReqFlag;

	static CRITICAL_SECTION  m_OnDataFlagLock;
	//static volatile LONG     m_OnDataFlagCountLock;
	static volatile LONG     m_FstCurDevConfigInfoCountLock;
	static volatile LONG     m_OnSaveCacheCountLock;
	static volatile LONG     m_OnOperateControlCountLock;

	static HANDLE            m_OnDataFlagEvent;
	HANDLE                   m_ExcuteCmdThreadExitEvent;
	HANDLE                   m_ModifyDevConfigThreadExitEvent;
	HANDLE                   m_SaveCacheThreadExitEvent;
	//HANDLE                   m_ThreadNotifyCmdEvent;
	HANDLE                   m_ExecThreadStartCmdEvent;
	HANDLE                   m_ModThreadStartCmdEvent;
	HANDLE                   m_SaveCacheThreadStartCmdEvent;
	HANDLE                   m_ReadyExitEvent;
	//static HANDLE            m_EndRunCheck;
	HANDLE                   m_LoginInfoHistoryCacheThreadUpdateEvent;
	//HANDLE                   m_QueryDevInfoHistoryCacheThreadUpdateEvent;
	HANDLE                   m_LoginInfoHistoryCacheThreadExitEvent;
	HANDLE                   m_OperateControlThreadStartEvent;
	HANDLE                   m_OperateControlThreadExitEvent;
	//HANDLE                   m_CheckDevOfflineStatusThreadStartEvent;
	//HANDLE                   m_CheckDevOfflineStatusThreadExitEvent;

	//HANDLE                   m_RestartDevThreadNotifyFailEvent;
	//HANDLE                   m_RestartDevThreadNotifySucessEvent;
	//HANDLE                   m_DevOfflineNotifyEvent;

	static BOOL              m_bFstCurDevConfigInfoFlag;
	CString                  m_TurnServerIp;
	CString                  m_TurnServerPort;
	UINT                     m_LoginHistoryCmd;

	CString                  m_sCurRestartDevID;
	INT                      m_nCurRestartDevIDCount;
	CString                  m_sCurLocalIP;
	volatile INT             m_nReShellLoginCount;

public:
	//afx_msg void OnEnChangeEditParaUser();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDisconnectButton();

public:
	BOOL p2p_context_init();
	VOID config_info_init();
	VOID status_info_init();
	VOID info_deinit();
	BOOL Run_Check();
	VOID start_work_thread();
	int get_mac(char* mac);
	VOID get_cur_mac_init();
	//INT get_mac_info_init();
	//INT get_tcp_network_info_init(LPCWSTR item = _T("all"));
	INT check_cur_devid_status_info_once(LPCWSTR item = NULL, BOOL flag = FALSE);
	void format_dev_info_and_show(UINT n, void *arg);

	static void test_shell_OnShellData(void *ctx, void *session, const void *data, int datasz, int ecode);
	static unsigned int __stdcall ExcuteCmdWorkThreadProc(PVOID arg);
	static unsigned int __stdcall ModifyDevConfigWorkThreadProc(PVOID arg);
	static unsigned int __stdcall SaveCacheWorkThreadProc(PVOID arg);
	static unsigned int __stdcall LoadCacheWorkThreadProc(PVOID arg);
	static unsigned int __stdcall ShowInfoWorkThreadProc(PVOID arg);
	static unsigned int __stdcall LoginInfoHistoryCacheWorkThreadProc(PVOID arg);
	static unsigned int __stdcall OperateControlWorkThreadProc(PVOID arg);
	static unsigned int __stdcall CheckDevOfflineStatusWorkThreadProc(PVOID arg);

	static void OnConnect(kp2p_handle_t p2p_handle, void *context, const char *conn_type);
	static void OnDisconnect(kp2p_handle_t p2p_handle, void *context, int ret);
	static void OnOpenStream(kp2p_handle_t p2p_handle, void *context, uint32_t channel, uint32_t stream, int err, const char *cam_des);
	static void OnCloseStream(kp2p_handle_t p2p_handle, void *context, uint32_t channel, uint32_t stream, int err);
	static void dumpH264(const char *path, void *frame, size_t frame_len);
	static void OnDumpVideo(int ch, const char *enc, void *frame, size_t frame_size);
	static void OnRecvFrameEx(kp2p_handle_t p2p_handle, void *context,
		uint32_t frame_type,
		void *frame, size_t frame_size,
		uint32_t channel,
		uint64_t time_stamp,
		uint32_t width,
		uint32_t height,
		uint32_t sample_rate,
		uint32_t sample_width,
		uint32_t sample_channels,
		const char *enc);
	static void OnVOP2PCallResult(kp2p_handle_t p2p_handle, void *context, int result);
	static void OnVOP2PHangupResult(kp2p_handle_t p2p_handle, void *context, int result);
	static void OnRecvRecFrame(kp2p_handle_t p2p_handle, void *context,
		uint32_t frame_type,
		void *frame, size_t frame_size, uint32_t channel, uint64_t time_stamp,
		uint32_t width, uint32_t height,
		uint32_t sample_rate, uint32_t sample_width, uint32_t sample_channels,
		uint32_t gen_time,
		const char *enc);
	static void OnLoginResult(kp2p_handle_t p2p_handle, void *context, int ret);
	static void OnPtzResult(kp2p_handle_t p2p_handle, void *context, int ret);
	static void OnVconRecv(kp2p_handle_t p2p_handle, void *context, uint32_t channel, const void *buf, size_t len);
	static void OnRemoteSetup(kp2p_handle_t p2p_handle, void *context, const void *data, size_t data_size);
	static void OnLogUpload(kp2p_handle_t p2p_handle, void *context, const char *log, size_t log_len);
	static void OnP2PError(kp2p_handle_t p2p_handle, void *context, const char *msg, size_t msg_len);

private:
	BOOL check_p2p_ex(const char *id, const char *ip, const char *user, const char *passwd, int func, int channel);
	LPCTSTR int_to_string(int arg, LPCTSTR input);
	BOOL start_dev_config_test();
	BOOL start_dev_status_test();
	VOID init_info_list();
	VOID check_current_config_info_once(LPCWSTR item = _T("all"));
	BOOL init_from_config_ini();
	INT get_mac_info_init();
	INT get_tcp_network_info_init(LPCWSTR item = _T("all"));
	//INT check_cur_devid_status_info_once(LPCWSTR item = NULL);
	static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

	//void front_info_in_queue(TEST_DEV_ITEM_TYPE type, LONG64 id, PVOID arg);
	void push_info_in_queue(TEST_DEV_ITEM_TYPE type, LONG64 id, PVOID arg);
	void pop_info_out_queue(TEST_DEV_ITEM_TYPE type, PVOID arg);
	void pop_info_out_queue(TEST_DEV_ITEM_TYPE type, LONG64 arg);
	void del_info_out_queue(TEST_DEV_ITEM_TYPE type, LONG64 arg);
	void clear_queue(TEST_DEV_ITEM_TYPE type);

public:
	afx_msg void OnBnClickedCannelTestButton();
	afx_msg void OnBnClickedStartTestButton();
	afx_msg void OnBnClickedLoadTestItemButton();
	afx_msg void OnBnClickedVedioButton();
	afx_msg void OnBnClickedLiveButton();
	afx_msg void OnBnClickedModConfigButton();
	afx_msg void OnBnClickedRestartIotdaemonButton();
	afx_msg void OnBnClickedRestartAppButton();
	afx_msg void OnBnClickedRestartDevButton();
	afx_msg void OnBnClickedRemoteConfigButton();
	afx_msg void OnBnClickedExportDataButton();
	afx_msg void OnBnClickedDelTestItemButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartCheckMainButton();
	afx_msg void OnBnClickedConfigSettingMainButton();
	afx_msg void OnBnClickedStopCheckMainButton();
	afx_msg void OnBnClickedInfoStatusDevButton();
	afx_msg void OnBnClickedModTimeDevButton();
	afx_msg void OnCbnEditchangeIdDevCombo();
	afx_msg void OnLbnSelchangeUntestItemList();
};
