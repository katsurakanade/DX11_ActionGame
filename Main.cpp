#include "main.h"
#include "Application.h"
#include "Renderer.h"
#include "Time.h"
#include "Debug.h"

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "Blessing";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND g_Window;
HINSTANCE g_hinstance;

std::chrono::system_clock::time_point Time::mPreviousTime;
std::chrono::duration<double> Time::mDelta;

HWND GetWindow()
{
	return g_Window;
}

HINSTANCE GetHinstance() {
	return g_hinstance;
}

#ifdef _DEBUG
int main(){

#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#endif 
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		GetModuleHandle(nullptr),
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		wcex.hInstance,
		NULL);

	g_hinstance = wcex.hInstance;

	// ����������(�E�B���h�E���쐬���Ă���s��)
	Application::Init();

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(g_Window, SW_SHOW);
	UpdateWindow(g_Window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Japanese Font
	io.Fonts->AddFontFromFileTTF("asset\\font\\ipam.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(g_Window);
	ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());

	// ���b�Z�[�W���[�v
	MSG msg;
	while (1)
	{
  		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
			
				Time::Tick();
				Application::Update();
				Application::Render();
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Application::Uninit();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return (int)msg.wParam;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void DebugOutputString(const char* str, ...) {

#ifdef _DEBUG
	va_list valist;
	va_start(valist, str);
	std::cout << str << std::endl;
	va_end(valist);
#endif

}

