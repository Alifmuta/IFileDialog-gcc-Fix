#include <windows.h>
#include <shobjidl.h> // IFileOpenDialog
#include <tchar.h>
#include "main.h"

// Global variables
static TCHAR szWindowClass[] = _T("GroovyApp");
static TCHAR szTitle[] = _T("Yeah man, right on!!");
HRESULT hr;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	{
	
	IFileOpenDialog* pFileOpen;
	
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// Create the FileOpenDialog object.
	hr = CoCreateInstance(	CLSID_FileOpenDialog,
							NULL,
							CLSCTX_ALL, 
							IID_IFileOpenDialog,
							reinterpret_cast<void**>(&pFileOpen)
						);

	if (SUCCEEDED(hr))	{
		
		// Show the Open dialog box.
		hr = pFileOpen->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))	{
			
			IShellItem *pItem;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr))	{
				
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				// Display the file name to the user.
				if (SUCCEEDED(hr))	{
					
					/*
						Note: When using IFileSaveDialog, hr is only SUCCESS when you select an existing
								file to overwrite, otherwise it'll return the equivalent of FALSE, meaning
								this MsgBox will not appear.
							  When using IFileOpenDialog, hr is SUCCESS upon the user selecting a file to open.
					*/
					
					MessageBoxW(NULL, pszFilePath, L"Selected File.", MB_OK);
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}
		
	CoUninitialize();
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
   PAINTSTRUCT ps;
   HDC hdc;
   TCHAR greeting[] = _T("Hello, Manchester!! No, wait...");

	switch (message)	{
	   
		case WM_PAINT:
	   
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
			EndPaint(hWnd, &ps);
			break;
			
		case WM_DESTROY:
	   
			PostQuitMessage(0);
			break;
		  
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

   return 0;
}
