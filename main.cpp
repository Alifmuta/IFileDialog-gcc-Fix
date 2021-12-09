#include <Windows.h>
#include <shobjidl.h> // IFileOpenDialog
#include <tchar.h>
#include <stdio.h>
#include "ifiledialog.h"

// Global variables
static TCHAR szWindowClass[] = _T("GroovyApp");
static TCHAR szTitle[] = _T("Yeah man, right on!!");
HRESULT hr;


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	{
	
	printf( "Select a file in the FileOpen dialog box, to see the path to the chosen file returned.\n" );
	
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	PWSTR pszFilePath;
	
	if (SUCCEEDED(hr))	{
		
		IFileOpenDialog *pFileOpen;
		
		hr = CoCreateInstance(	CLSID_FileOpenDialog,
							NULL,
							CLSCTX_ALL, 
							IID_IFileOpenDialog,
							reinterpret_cast<void**>(&pFileOpen)
						);
		
		
		// Show the Open dialog box.
		hr = pFileOpen->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))	{
			
			IShellItem *pItem;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr))	{
				
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				// Display the file name to the user.
				if (SUCCEEDED(hr))	{
					
					/*
						Note:	When using IFileSaveDialog, hr is only SUCCESS when you select an existing
								file to overwrite (which won't be overwritten - it's a read operation, not a write operation),
								otherwise it'll return the equivalent of FALSE, meaning this MsgBox will not appear.
								When using IFileOpenDialog, hr is SUCCESS upon the user selecting a file to open.
					*/
					
					MessageBoxW(NULL, pszFilePath, 	L"Selected File.", MB_OK);
					CoTaskMemFree(pszFilePath);
				}
			}
			
			pItem->Release();
		}
		
		pFileOpen->Release();
	}
		
	CoUninitialize();
	
	printf( "Path & File returned: '%S'\n", pszFilePath ); // Note, it is %S, not %s, as %S tells printf the param string is a wchar string.

	return 0;
}
