#include <Windows.h>
#include <stdio.h>
#include <shobjidl.h> // IFile([Open|Save]?)Dialog
#include "ifiledialog.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	{
	
	printf( "Select a file in the FileOpen/FileSave dialog box, to see the path to the chosen file returned.\n" );
	
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	PWSTR pszFilePath;
	
	if (SUCCEEDED(hr))	{
		
		IFileOpenDialog *pFileOpen; // Change IFileOpenDialog to IFileSaveDialog for a "Save File" Box. 
		
		hr = CoCreateInstance(	CLSID_FileOpenDialog, // Likewise, change to CLSID_FileSaveDialog.
							NULL,
							CLSCTX_ALL, 
							IID_IFileOpenDialog, // Likewise, change to IID_IFileSaveDialog.
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
				if (SUCCEEDED(hr))
					MessageBoxW(NULL, pszFilePath, 	L"Selected File.", MB_OK);
					/*
						Note:	When using IFileSaveDialog, hr is only SUCCESS when you select an existing
								file to overwrite (which won't be overwritten - it's a read operation, not a write operation),
								otherwise it'll return the equivalent of FALSE, meaning this MsgBox will not appear.
								When using IFileOpenDialog, hr is SUCCESS upon the user selecting a file to open.
					*/
			}
			
			pItem->Release();
		}
		
		pFileOpen->Release();
	}
		
	CoUninitialize();
	
	printf( "Path & File returned: '%S'\n", pszFilePath ); // Note, it is %S, not %s, as %S tells printf the param string is a widechar string.

	return 0;
}
