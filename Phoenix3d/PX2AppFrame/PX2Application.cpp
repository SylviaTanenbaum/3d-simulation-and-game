/*
*
* �ļ�����	��	PX2Application.cpp
*
*/

#include "PX2Application.hpp"
#include "PX2IMEDispatcher.hpp"
#ifdef __MARMALADE__
#include "s3e.h"
#endif
using namespace PX2;

//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)

static std::queue<int> s_isUniChar;
static BYTE s_lobyte;
static BYTE s_hibyte;

LRESULT CALLBACK MsWindowEventHandler (HWND handle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	int sizeX = 0;
	int sizeY = 0;
	static bool firsttime = true;

	switch (message) 
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		sizeX = LOWORD(lParam);
		sizeY = HIWORD(lParam);

		ApplicationBase::msApplication->OnSize(sizeX, sizeY);

		switch (wParam)
		{
		case SIZE_RESTORED:
			if (ApplicationBase::msApplication->IsInitlized())
				ApplicationBase::msApplication->WillEnterForeground(firsttime);
			firsttime = false;
			break;
		case SIZE_MINIMIZED:
			if (ApplicationBase::msApplication->IsInitlized())
				ApplicationBase::msApplication->DidEnterBackground();
			break;
		}
		break;
	case WM_IME_CHAR:	
		if (wParam > 0x7f) 
		{
			s_isUniChar.push(2);
		}
		else 
		{
			s_isUniChar.push(0);
		}
		break;
	case WM_CHAR:
		if (s_isUniChar.empty())
		{
			if (wParam < 0x20)
			{
				if (VK_BACK == wParam)
				{
					IMEDispatcher::GetSingleton().DispathDeleteBackward();
				}
				else if (VK_RETURN == wParam)
				{
					IMEDispatcher::GetSingleton().DispathInsertText("\n", 1);
				}
				else if (VK_TAB == wParam)
				{
					// tab input
				}
				else if (VK_ESCAPE == wParam)
				{
					// ESC input
				}
			}
			else if (wParam < 128)
			{
				IMEDispatcher::GetSingleton().DispathInsertText((const char*)&wParam, 1);
			}
		}
		else
		{
			int& rate = s_isUniChar.front();
			if (rate == 2) 
			{
				--rate;
				s_lobyte = (BYTE)wParam;
				break;
			}
			else if (rate == 1)
			{
				s_isUniChar.pop();
				s_hibyte = (BYTE)wParam;
				DWORD wideChar = MAKEWORD(s_lobyte, s_hibyte);

				wchar_t s_ch[3] = {0};
				int nUTF16Size = ::MultiByteToWideChar(
					CP_ACP,
					0,
					(LPCSTR)&wideChar,
					4,
					s_ch,
					3);
				if (nUTF16Size == 0) 
				{
					return -1;
				}

				int u8Len = ::WideCharToMultiByte(CP_UTF8, 0, s_ch, nUTF16Size, 0, 0, 0, 0);

				char szUtf8[8] = {0};
				int length = WideCharToMultiByte(CP_UTF8, 0, s_ch, nUTF16Size, szUtf8, u8Len, 0, 0);
				IMEDispatcher::GetSingleton().DispathInsertText(szUtf8, 3);
			}
			else 
			{
				s_isUniChar.pop();
			}
		}
		break;
	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
#endif
//----------------------------------------------------------------------------
Application::Application ()
{
#if defined(_WIN32) || defined(WIN32)
	mhWnd = 0;
#endif
}
//----------------------------------------------------------------------------
Application::~Application ()
{
}
//----------------------------------------------------------------------------
int Application::Entry (int numArguments, char** arguments)
{
	Application* theApp = (Application*)msApplication;
	return theApp->Main(numArguments, arguments);
}
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
int Application::Main (int numArguments, char** arguments)
{
	PX2_UNUSED(numArguments);
	PX2_UNUSED(arguments);

	Initlize ();

	// Ԥ�������ɫ
	mRenderer->ClearBuffers();

	// ��ʾ����
	ShowWindow(mhWnd, SW_SHOWNORMAL);
	UpdateWindow(mhWnd);

	// ��Ϣѭ��
	bool applicationRunning = true;
	while (applicationRunning)
	{
		MSG msg;
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				applicationRunning = false;
				continue;
			}

			HACCEL accel = 0;
			if (!TranslateAccelerator(mhWnd, accel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			OnIdle();
		}
	}

	Ternamate ();

	return 0;
}
#endif
//----------------------------------------------------------------------------
bool Application::OnIdle ()
{
	if (mInputEventAdapter)
	{
		mInputEventAdapter->Update();
	}

	return ApplicationBase::OnIdle();
}
//----------------------------------------------------------------------------
#if defined __ANDROID__
int Application::Main (int numArguments, char** arguments)
{
	return 0;
}
#endif
//----------------------------------------------------------------------------
#ifdef __MARMALADE__
static void SwitchToForeground()
{
	if (ApplicationBase::msApplication->IsInitlized())
		ApplicationBase::msApplication->WillEnterForeground(false);
}
static void SwitchToBackground()
{
	if (ApplicationBase::msApplication->IsInitlized())
		ApplicationBase::msApplication->DidEnterBackground();
}
static int32 PauseCallback(void *systemData, void *userData)
{
	if (ApplicationBase::msApplication->IsInitlized())
		ApplicationBase::msApplication->OnPause();

	return 0;
}
static int32 UnPauseCallback(void *systemData, void *userData)
{
//	if (ApplicationBase::msApplication->IsInitlized())
//		ApplicationBase::msApplication->OnResume();

	return 0;
}

int g_FrameYieldMS = 10;
int Application::Main (int numArguments, char** arguments)
{
	Initlize ();

	s3eDeviceRegister(S3E_DEVICE_PAUSE, PauseCallback, NULL);
	s3eDeviceRegister(S3E_DEVICE_UNPAUSE , UnPauseCallback, NULL);

    if (s3eGLGetInt(S3E_GL_MUST_SUSPEND))
    {
        // when a suspend is requested, terminate EGL
        s3eGLRegister(S3E_GL_SUSPEND, (s3eCallback)SwitchToBackground, NULL);

        // when a resume is requested, re-initialise EGL...
        s3eGLRegister(S3E_GL_RESUME, (s3eCallback)SwitchToForeground, NULL);
        // ...and restore the shaders
        //s3eGLRegister(S3E_GL_RESUME, (s3eCallback)loadShader, NULL);
    }

	if (ApplicationBase::msApplication->IsInitlized()) 
		ApplicationBase::msApplication->WillEnterForeground(true);

	// Ԥ�������ɫ
	mRenderer->ClearBuffers();

	bool quit = false;
	while(!quit)
	{
		s3eDeviceYield(g_FrameYieldMS);

		if(s3eDeviceCheckQuitRequest())
		{
			quit = true;
		}
        if((s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_PRESSED) != 0)
		{
			if(IsPause()) OnResume();
			else OnPause();
		}
		if(s3eDeviceCheckPauseRequest())
		{
			OnPause();
		}

		s3eKeyboardUpdate();
		OnIdle();
	}

	Ternamate ();
	return 0;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnInitlizeApp ()
{
	// === ������Ⱦ���� ===

	// ע�ᴰ����
	static char sWindowClass[] = "Phoenix2 ApplicationBase";
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = MsWindowEventHandler;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = 0;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = sWindowClass;
	wc.lpszMenuName  = 0;
	RegisterClass(&wc);

	DWORD dwStyle;
	if (mAllowResize)
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	}

	// �����ض��ͻ�����С�Ĵ��ڴ�С
	RECT rect = { 0, 0, mWidth-1, mHeight-1 };
	AdjustWindowRect(&rect, dwStyle, FALSE);

	// ��������
	mhWnd = CreateWindow(sWindowClass, mWindowTitle.c_str(),
		dwStyle, mXPosition, mYPosition,
		rect.right - rect.left + 1, rect.bottom - rect.top + 1, 0, 0, 0, 0);

	// ����
	RECT rcDesktop, rcWindow;
	GetWindowRect(GetDesktopWindow(), &rcDesktop);

	HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), NULL);
	if (hTaskBar != NULL)
	{
		APPBARDATA abd;

		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = hTaskBar;

		SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
		SubtractRect(&rcDesktop, &rcDesktop, &abd.rc);
	}
	GetWindowRect(mhWnd, &rcWindow);
	int offsetX = (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
	offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
	int offsetY = (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
	offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;
	SetWindowPos(mhWnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	mXPosition = offsetX;
	mYPosition = offsetY;

	// === Input ===
	mInputEventAdapter->AddParam((int)mhWnd);

	// === ��Ⱦ�� ===

#ifdef PX2_USE_DX9
	// ������Ⱦ��
	mInput.mWindowHandle = mhWnd;
	mInput.mDriver = Direct3DCreate9(D3D_SDK_VERSION);
	assertion(mInput.mDriver != 0, "Failed to create Direct3D9\n");
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

#ifdef PX2_USE_OPENGLES2
	mInput.mWindowHandle = mhWnd;
	mInput.mRendererDC = GetDC(mhWnd);
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);

#endif

	Renderer::SetDefaultRenderer(mRenderer);
	mRenderer->SetClearColor(mClearColor);

	UIManager::GetSingleton().GetDefaultView()->SetRenderer(mRenderer);

	return true;
}
#endif
//----------------------------------------------------------------------------
#if defined(__ANDROID__) || defined(__MARMALADE__)
bool Application::OnInitlizeApp ()
{
#ifdef __MARMALADE__
	mInput.mWindowHandle = s3eGLGetNativeWindow();
#else
	mInput.mWindowHandle = 0;
#endif
	mInput.mRendererDC = EGL_DEFAULT_DISPLAY;

#ifdef PX2_USE_OPENGLES2
	mRenderer = new0 Renderer(mInput, mWidth, mHeight,
		mColorFormat, mDepthStencilFormat, mNumMultisamples);
#endif

	Renderer::SetDefaultRenderer(mRenderer);
	mRenderer->SetClearColor(mClearColor);
	UIManager::GetSingleton().GetDefaultView()->SetRenderer(mRenderer);

	return true;
}
#endif
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
bool Application::OnTernamateApp()
{
	if (mRenderer)
	{
		delete0(mRenderer);
#ifdef PX2_USE_DX9
		mInput.mDriver->Release();
#endif
	}
	return true;
}
#endif
//----------------------------------------------------------------------------
#if defined(__ANDROID__)||defined(__MARMALADE__)
bool Application::OnTernamateApp()
{
	ApplicationBase::OnTernamate();

	if (mRenderer)
	{
		delete0(mRenderer);
	}

	return true;
}
#endif
//----------------------------------------------------------------------------