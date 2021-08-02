// ImeOffAnyDesk.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ImeOffAnyDesk.h"
#include "shellapi.h"
#include <Psapi.h>
#include "regex_with_tchar.cpp"
#include <imm.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // アイコン AddSystemTrayIcon()で使用するため
    hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IMEOFFANYDESK));

    // タスクトレイアイコン右クリックメニュー
    hTrayIconMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IMEOFFANYDESK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMEOFFANYDESK));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IMEOFFANYDESK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_IMEOFFANYDESK);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 300, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    //ShowWindow(hWnd, nCmdShow);
    ShowWindow(hWnd, SW_SHOWMINNOACTIVE);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {

        //ウィンドウ生成
        case WM_CREATE:
        {
            char buffer[200];
            sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON WM_CREATE");
            OutputDebugStringA(buffer);
            OutputDebugStringA("\n");

            // AnyDeskの監視タイマーをON
            SetTimer(hWnd, TIMER_ANYDESK_CHECK, 1000, NULL);
        }
        break;
        //ウインドウサイズ変更時の処理
        case WM_SIZE:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
                // 最小化した時
                case SIZE_MINIMIZED:
                {
                    char buffer[200];
                    sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON SIZE_MINIMIZED");
                    OutputDebugStringA(buffer);
                    OutputDebugStringA("\n");

                    // タスクトレイにアイコンを追加
                    AddSystemTrayIcon(hWnd);

                    // タスクバー内のアプリアイコンを非表示
                    ShowWindow(FindWindow(TEXT("ImeOffAnyDesk"), NULL), SW_HIDE);
                }
                break;
            }
        }
        break;
        // タスクトレイのアイコンに対する処理
        case WM_TASKTRAY:
        {
            switch (lParam)
            {
                // 左ダブルクリック
                case WM_LBUTTONDBLCLK:
                {
                    char buffer[200];
                    sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON WM_LBUTTONDBLCLK");
                    OutputDebugStringA(buffer);
                    OutputDebugStringA("\n");

                    // タスクトレイからアイコンを削除
                    DellSystemTrayIcon(hWnd);

                    // タスクバー内のアプリアイコンを表示
                    ShowWindow(FindWindow(TEXT("ImeOffAnyDesk"), NULL), SW_SHOW);

                    // アプリの表示
                    ShowWindow(hWnd, SHOW_OPENWINDOW);
                }
                break;
                // 右クリック
                case WM_RBUTTONDOWN:
                {
                    char buffer[200];
                    sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON WM_RBUTTONDOWN");
                    OutputDebugStringA(buffer);
                    OutputDebugStringA("\n");

                    if (hTrayIconMenu)
                    {

                        char buffer[200];
                        sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "hTrayIconMenu取得完了");
                        OutputDebugStringA(buffer);
                        OutputDebugStringA("\n");

                        HMENU hTrayIconSubMenu = GetSubMenu(hTrayIconMenu, 0);
                        if (hTrayIconSubMenu)
                        {
                            char buffer[200];
                            sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "hTrayIconSubMenu取得完了");
                            OutputDebugStringA(buffer);
                            OutputDebugStringA("\n");

                            // タスクトレイのアイコンを右クリックした時の座標を取得
                            POINT po;
                            GetCursorPos(&po);

                            // ウィンドウをフォアグラウンドに持ってくる
                            SetForegroundWindow(hWnd);
                            // これをしないと、メニュー外をクリックした時に、ポップアップメニューが消えない
                            SetFocus(hWnd);

                            // メニューの表示
                            TrackPopupMenu(hTrayIconSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN,
                                po.x, po.y, 0, hWnd, NULL
                            );
                        }
                    }
                }
                break;
            }
        }
        break;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
                case IDM_ABOUT:
                {
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                }
                break;
                case IDM_EXIT:
                {
                    DestroyWindow(hWnd);
                }
                break;
                case IDM_SHOW_WINDOW:
                {
                    char buffer[200];
                    sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON IDM_SHOW_WINDOW");
                    OutputDebugStringA(buffer);
                    OutputDebugStringA("\n");

                    // タスクトレイからアイコンを削除
                    DellSystemTrayIcon(hWnd);

                    // タスクバー内のアプリアイコンを表示
                    ShowWindow(FindWindow(TEXT("ImeOffAnyDesk"), NULL), SW_SHOW);

                    // アプリの表示
                    ShowWindow(hWnd, SHOW_OPENWINDOW);
                }
                break;
                default:
                {
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_TIMER:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
                case TIMER_ANYDESK_CHECK:
                {
                    if (0 == flg_timer_ime)
                    {
                        InvalidateRect(hWnd, NULL, TRUE);

                        PAINTSTRUCT ps;
                        HDC hdc = BeginPaint(hWnd, &ps);

                        TextOutCommonMessage(hdc);

                        OutputDebugStringA("AnyDeskでリモートPCを操作中かどうか監視中\n");
                        TCHAR message[] = _T("AnyDeskでリモートPCを操作中かどうか監視中");
                        TextOut(hdc, 10, 170, message, _tcslen(message));

                        EndPaint(hWnd, &ps);
                    }

                    if (ForegroundWindowIsAnyDesk())
                    {
                        // IME監視タイマーをON
                        if (0 == flg_timer_ime)
                        {
                            OutputDebugStringA("AnyDeskを操作中のため、IMEの監視を開始する\n");
                            flg_timer_ime = 1;
                            SetTimer(hWnd, TIMER_IME_CHECK, 200, NULL);
                        }
                    }
                    else
                    {
                        // IME監視タイマーをOFF
                        if (1 == flg_timer_ime)
                        {
                            OutputDebugStringA("AnyDeskを操作中ではないため、IMEの監視を終了する\n");
                            flg_timer_ime = 0;
                            KillTimer(hWnd, TIMER_IME_CHECK);
                        }
                    }
                }
                break;
                case TIMER_IME_CHECK:
                {
                    InvalidateRect(hWnd, NULL, TRUE);

                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);

                    TextOutCommonMessage(hdc);

                    OutputDebugStringA("AnyDeskでリモートPCを操作中のためIMEがONかどうか監視中\n");
                    TCHAR message[] = _T("AnyDeskでリモートPCを操作中のためIMEがONかどうか監視中");
                    TextOut(hdc, 10, 170, message, _tcslen(message));

                    HWND hActWin = GetForegroundWindow();
                    if (hActWin)
                    {
                        // フォアグラウンドアプリのIMEハンドルを取得
                        HWND hIMEWnd = ImmGetDefaultIMEWnd(hActWin);
                        if (hIMEWnd)
                        {
                            // IMEの状態取得
                            LRESULT imeStatus = SendMessageA(hIMEWnd, WM_IME_CONTROL, DFCS_SCROLLCOMBOBOX, 0);

                            TCHAR wBuffer[200];
                            wsprintf(wBuffer, L"IMEの状態は:%ld", imeStatus);
                            TextOut(hdc, 10, 190, wBuffer, _tcslen(wBuffer));

                            TCHAR wBufferDebug[200];
                            wsprintf(wBufferDebug, L"%s\n", wBuffer);
                            OutputDebugString(wBufferDebug);

                            // IMEがONだったらOFFにする
                            if (imeStatus)
                            {
                                // 0x006 は IMC_SETOPENSTATUS 
                                SendMessageA(hIMEWnd, WM_IME_CONTROL, 0x006, 0);
                                OutputDebugString(L"IMEをOFFにしました");
                            }
                        }
                        else
                        {
                            DebugLastError(__FILE__, __LINE__);
                        }
                    }

                    EndPaint(hWnd, &ps);
                }
                break;
            }
        }
        break;
        case WM_CLOSE:
        {
            char buffer[200];
            sprintf_s(buffer, sizeof(buffer), "%s:(%d) %s", __FILE__, __LINE__, "ON WM_CLOSE");
            OutputDebugStringA(buffer);
            OutputDebugStringA("\n");

            // タスクトレイにアイコンを追加
            AddSystemTrayIcon(hWnd);

            // タスクバー内のアプリアイコンを非表示
            ShowWindow(FindWindow(TEXT("ImeOffAnyDesk"), NULL), SW_HIDE);
        }
        break;
        case WM_DESTROY:
        {
            // AnyDeskの監視タイマーをOFF
            KillTimer(hWnd, TIMER_ANYDESK_CHECK);

            // タスクトレイからアイコンを削除
            DellSystemTrayIcon(hWnd);

            PostQuitMessage(0);
        }
        break;
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
        {
            return (INT_PTR)TRUE;
        }
        break;
        case WM_COMMAND:
        {
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// タスクバーにアイコンを追加
VOID AddSystemTrayIcon(HWND hWnd)
{
    NOTIFYICONDATA nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uFlags = (NIF_ICON | NIF_MESSAGE | NIF_TIP);
    nid.hWnd = hWnd;
    nid.hIcon = hIcon;
    nid.uCallbackMessage = WM_TASKTRAY;
    lstrcpy(nid.szTip, TEXT("ImeOffAnyDesk"));
    Shell_NotifyIcon(NIM_ADD, &nid);
}

// タスクバーのアイコンを削除
VOID DellSystemTrayIcon(HWND hWnd)
{
    NOTIFYICONDATA nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

// WindowsAPIエラー出力
VOID DebugLastError(const char* file, int line)
{

    DWORD errorCode = GetLastError();
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER   // テキストのメモリ割り当てを要求する
        | FORMAT_MESSAGE_FROM_SYSTEM     // エラーメッセージはWindowsが用意しているものを使用
        | FORMAT_MESSAGE_IGNORE_INSERTS, // 次の引数を無視してエラーコードに対するエラーメッセージを作成する
        NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),// 言語を指定
        (LPTSTR)&lpMsgBuf,               // メッセージテキストが保存されるバッファへのポインタ
        0,
        NULL
    );

    char cBuffer[300];
    sprintf_s(cBuffer, sizeof(cBuffer), "%s:(%d)", file, line);
    OutputDebugStringA(cBuffer);
    OutputDebugStringA("\n");

    wchar_t wBuffer[1200];
    wchar_t* plpMsgBuf = (wchar_t*)lpMsgBuf;
    wsprintf(wBuffer, L"%ld: %ls", errorCode, plpMsgBuf);
    OutputDebugString((LPCWSTR)wBuffer);
    LocalFree(lpMsgBuf);
}

// AnyDeskでリモートコンピューターを操作中かどうか判定する
BOOL ForegroundWindowIsAnyDesk()
{
    // フォアグラウンドのウインドウのハンドルを取得
    HWND hActWin = GetForegroundWindow();
    if (hActWin)
    {
        // ウインドウのハンドルからプロセスID取得
        DWORD dwPID;
        GetWindowThreadProcessId(hActWin, &dwPID);

        // プロセスのハンドルを取得
        HANDLE Handle = OpenProcess(
            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE,
            dwPID
        );

        if (Handle)
        {
            // .exeのフルパス
            TCHAR exePath[MAX_PATH];
            if (GetModuleFileNameEx(Handle, 0, exePath, MAX_PATH))
            {
                CloseHandle(Handle);
                //TextOut(hdc, 10, 30, exePath, lstrlen(exePath));

                // ウインドウテキスト
                int iActWinTextLength = GetWindowTextLength(hActWin);
                LPTSTR lActWinText = NULL;
                if (iActWinTextLength)
                {
                    lActWinText = new TCHAR[iActWinTextLength + 1];
                    GetWindowText(hActWin, lActWinText, iActWinTextLength + 1);
                    //TextOut(hdc, 10, 70, lActWinText, lstrlen(lActWinText));

                    if (lActWinText)
                    {
                        // exe名とウインドウテキストタイトルからAnyDeskで操作中か判定

                        std::tregex re1(L".*\\AnyDesk.exe");
                        std::tsmatch wm1;
                        std::tstring wtest1(exePath);

                        std::tregex re2(L".* - AnyDesk");
                        std::tsmatch wm2;
                        std::tstring wtest2(lActWinText);

                        if (std::regex_match(wtest1, wm1, re1) && std::regex_match(wtest2, wm2, re2))
                        {
                            return TRUE;
                        }
                    }
                    else
                    {
                        CloseHandle(Handle);
                        DebugLastError(__FILE__, __LINE__);
                    }
                }
            }
        }
    }

    return FALSE;
}

// 共通メッセージ出力
VOID TextOutCommonMessage(HDC hdc)
{
    TCHAR message1[] = _T("## 説明 ##");
    TextOut(hdc, 10, 10, message1, _tcslen(message1));

    TCHAR message2[] = _T("AnyDesk.exeを操作中且つ、リモートパソコンを操作中に、");
    TextOut(hdc, 10, 30, message2, _tcslen(message2));

    TCHAR message3[] = _T("IMEがONになったらOFFにするだけのアプリケーションです。");
    TextOut(hdc, 10, 50, message3, _tcslen(message3));

    TCHAR message4[] = _T("最小化もしくは閉じるでタスクトレイに入ります。");
    TextOut(hdc, 10, 70, message4, _tcslen(message4));

    TCHAR message5[] = _T("終了させるにはメニューのファイルから終了を選択もしくは、");
    TextOut(hdc, 10, 90, message5, _tcslen(message5));

    TCHAR message6[] = _T("タスクトレイのアイコンを右クリックして終了を選択してください。");
    TextOut(hdc, 10, 110, message6, _tcslen(message6));

    TCHAR message7[] = _T("## 現在の状態（随時更新）##");
    TextOut(hdc, 10, 150, message7, _tcslen(message7));
}
