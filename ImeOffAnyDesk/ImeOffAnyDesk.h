#pragma once

#include "resource.h"
#include <atlstr.h>

#define MAX_LOADSTRING 100
#define WM_TASKTRAY (WM_APP + 1)                // タスクトレイのマウス・メッセージ定数

#define TIMER_ANYDESK_CHECK 1
#define TIMER_IME_CHECK 2

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
INT flg_timer_ime = 0;
HICON hIcon;
HMENU hTrayIconMenu;
HWND hWnd_existed;

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

VOID AddSystemTrayIcon(HWND hWnd);
VOID DellSystemTrayIcon(HWND hWnd);
VOID DebugLastError(const char* file, int line);
BOOL ForegroundWindowIsAnyDesk();
VOID TextOutCommonMessage(HDC hdc);
VOID GetExeOtherProcessIds(CString sTargetExeName, DWORD* dwExeProcessIds, DWORD dwCurrentProcessId);
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam);
