﻿#pragma once
// #pragma warning (disable:4793)

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include <conio.h>
#include <tchar.h>
#include <errno.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <algorithm>
#include <time.h>
////
//#include <winsock2.h>
//#include <MSWSock.h>
//#include <windows.h>

#include <process.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <tlhelp32.h>  
#include <atlstr.h>    
#include <locale.h>
#include <winuser.h>
#include <Psapi.h>
//#include <ntstatus.h> 
//#include <atlstr.h>
#include <atlconv.h>

#include <curl/curl.h>
#include <curl/easy.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
//#include "rapidjson/filestream.h"

#include "ProcDataDef.h"

using namespace rapidjson;
using namespace std;


//ID调试
#define T_DEBUG   0

//#pragma comment(lib,"shlwapi.lib")
//#pragma comment ( lib,"user32.lib" )  
//#pragma comment(lib,"psapi.lib")
//#pragma warning (disable:4793)
//#pragma warning(disable: 4996) 

#if _WIN64
//#pragma comment(lib, "NetFX4.0/EasyHook64.lib")
//#pragma comment(lib, "curl_release/64/libcurl.lib")
#else
#if _DEBUG
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib,"zlog.lib")
#pragma comment(lib, "libpthread.lib")
#pragma comment(lib, "P2PSDKClient.lib")
#pragma comment(lib, "iotlink.lib")
#pragma comment(lib, "arq.lib")
#pragma comment(lib, "websockets.lib")
#pragma comment(lib, "kdp.lib")
#pragma comment(lib, "libcurld.lib")
#else
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib,"zlog.lib")
#pragma comment(lib, "libpthread.lib")
#pragma comment(lib, "P2PSDKClient.lib")
#pragma comment(lib, "iotlink.lib")
#pragma comment(lib, "arq.lib")
#pragma comment(lib, "websockets.lib")
#pragma comment(lib, "kdp.lib")
#pragma comment(lib, "libcurl.lib")
#endif
#endif

#if _WIN32
#define msleep_c(t) Sleep(t)
#define timegm _mkgmtime
#define gmtime_r gmtime_s
#else
#define msleep_c(t) usleep(t * 1000)
#endif

extern CRITICAL_SECTION g_cs_log;

#define DISALLOW_ASSIGN(TypeName) \
void operator=(const TypeName&){}

#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
TypeName(const TypeName&);                    \
DISALLOW_ASSIGN(TypeName)

#define DISALLOW_EVIL_CONSTRUCTORS(TypeName) \
DISALLOW_COPY_AND_ASSIGN(TypeName)

#undef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
TypeName();                                    \
DISALLOW_EVIL_CONSTRUCTORS(TypeName)

#define LIBJINGLE_DEFINE_STATIC_LOCAL(type, name, arguments) \
static type& name = *new type arguments


#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

//USES_CONVERSION;
//显示测试状态信息
//#define SHOW_STATUS_INFO(info) m_ListBoxStatusShow.AddString(info)
#define SHOW_STATUS_INFO_A(info) m_ListBoxStatusShow.SetTopIndex(m_ListBoxStatusShow.AddString(_T(info)));  \
	m_ListBoxStatusShow.RedrawWindow()
//#define SHOW_STATUS_INFO_S_A(info) p->m_ListBoxStatusShow.SetTopIndex(p->m_ListBoxStatusShow.AddString(_T(info)));  \
//	p->m_ListBoxStatusShow.RedrawWindow()
#define SHOW_STATUS_INFO_S_A(info) m_This->m_ListBoxStatusShow.SetTopIndex(m_This->m_ListBoxStatusShow.AddString(_T(info)));  \
	m_This->m_ListBoxStatusShow.RedrawWindow()
#define SHOW_STATUS_INFO_S_W(info) m_This->m_ListBoxStatusShow.SetTopIndex(m_This->m_ListBoxStatusShow.AddString(info));  \
	m_This->m_ListBoxStatusShow.RedrawWindow()
#define SHOW_STATUS_INFO_W(info) m_ListBoxStatusShow.SetTopIndex(m_ListBoxStatusShow.AddString(info));  \
	m_ListBoxStatusShow.RedrawWindow()

#define SHOW_CURRENT_STATUS_INFO_A(info) m_Statusbar.SetPaneText(2, _T(info))

#define TURN_SERVER_IP         _T("118.190.84.189")

//设备配置测试项
#define TEST_MTU_ITEM            _T("MTU")
#define TEST_GEATEWAY_ITEM       _T("网关")
#define TEST_DNS_ITEM            _T("DNS")
#define TEST_SIGNAL_ITEM         _T("信号强度")
#define TEST_CPU_ITEM            _T("CPU占用")
#define TEST_MEMORY_ITEM         _T("内存占用")
#define TEST_PROCESS_ITEM        _T("进程")
#define TEST_THREAD_ITEM         _T("线程")
#define TEST_DEV_SYS_TIME_ITEM   _T("设备系统时间")

//设备状态测试项
#define TEST_PING_ITEM         _T("PING检测")
#define TEST_NETWORK_ITEM      _T("网络连接状况检测")
#define TEST_ROUTE_ITEM        _T("路由表检测")
#define TEST_BANDWIDTH         _T("带宽检测")
#define TEST_LOG_ITEM          _T("日志数据获取检测")

#define TEST_RESTART_DEV       _T("重启设备")
#define TEST_RESTART_APP       _T("重启APP")
#define TEST_RESTART_IOTDAEMON _T("重启IOTDaemon")

#ifndef SAFE_DELETE 
#define SAFE_DELETE(p) { if(p){delete(p);  (p)=NULL;} }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] (p);  (p)=NULL;} }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p){ (p)->Release();  (p)=NULL;} }
#endif

inline void InitCS(CRITICAL_SECTION * cs){
	if (!::InitializeCriticalSectionAndSpinCount(cs, 4000))
		::InitializeCriticalSection(cs);
}

inline void DestCS(CRITICAL_SECTION * cs){
	::DeleteCriticalSection(cs);
}
inline void InitGlobalCS()
{
	InitCS(&g_cs_log);
}
inline void DestGlobalCS()
{
	DestCS(&g_cs_log);	
}

class CSLock
{
public:
	CSLock(
		_Inout_ CRITICAL_SECTION& cs,
		_In_ bool bInitialLock = true,
		_In_ bool bInitialcs = false);
	~CSLock() throw();
	void Lock();
	void Unlock() throw();
private:
	CRITICAL_SECTION& m_cs;
	bool m_bLocked;
	// Private to avoid accidental use
	CSLock(_In_ const CSLock&) throw();
	CSLock& operator=(_In_ const CSLock&) throw();
};

inline CSLock::CSLock(
	_Inout_ CRITICAL_SECTION& cs,
	_In_ bool bInitialLock,
	_In_ bool bInitialcs) :
	m_cs(cs), m_bLocked(false)
{
	if (bInitialcs)
		InitCS(&m_cs);
	if (bInitialLock)
		Lock();
}
inline CSLock::~CSLock() throw()
{
	if (m_bLocked)
		Unlock();
}
inline void CSLock::Lock()
{
	::EnterCriticalSection(&m_cs);
	m_bLocked = true;
}
inline void CSLock::Unlock() throw()
{
	::LeaveCriticalSection(&m_cs);
	m_bLocked = false;
}
