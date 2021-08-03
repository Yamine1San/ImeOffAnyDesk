#pragma once

#include "resource.h"
#include <atlstr.h>

#define MAX_LOADSTRING 100
#define WM_TASKTRAY (WM_APP + 1)                // �^�X�N�g���C�̃}�E�X�E���b�Z�[�W�萔

#define TIMER_ANYDESK_CHECK 1
#define TIMER_IME_CHECK 2

// �O���[�o���ϐ�:
HINSTANCE hInst;                                // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��
INT flg_timer_ime = 0;
HICON hIcon;
HMENU hTrayIconMenu;
HWND hWnd_existed;

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
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
