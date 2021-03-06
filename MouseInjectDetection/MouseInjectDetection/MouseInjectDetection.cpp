#include "stdafx.h"
#include <Windows.h>
#include <iostream>

void unhookMouse(HHOOK mouseHook)
{
	UnhookWindowsHookEx(mouseHook);
	exit(0);
}

LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {
		switch (wParam) {
		case WM_MOUSEMOVE:
			MSLLHOOKSTRUCT * info = (MSLLHOOKSTRUCT *)lParam;
			bool injectedKey = (info->flags & LLMHF_INJECTED);
			if (injectedKey)
				std::cout << "[+] Injected key detected " << std::endl;
			break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int main()
{
	HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, HookProcedure, GetModuleHandle(NULL), NULL);
	std::cout << "[+] Hook ready" << std::endl;
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	unhookMouse(mouseHook);
	return 0;
}

