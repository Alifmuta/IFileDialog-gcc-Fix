# IFileDialog-gcc-Fix
#
# gcc fix/solution for compiling COM Object IFileDialog (IFileOpenDialog and IFileSaveDialog).
#

I invested many minutes of research & dedicated time analyzing & testing the compilation process of gcc and it's use of the include file *shobjidl.h*, and I have returned from the battle arena with an elixer: a solution not yet easily-findable in google, at least.

I have a fix/solution for the problems people on the internet have had compiling a win32 app with (esp. MingW) gcc, that uses the COM Object "IFileDialog", and thus "IFileOpenDialog" and "IFileSaveDialog". All they need do is #include "ifiledialog.h" , which will allow them to create IFileOpenDialog and IFileSaveDialog dialog boxes and open them on the screen.
Also defines the IID_ and CLSID_ objects needed.

My fix can be used by some plucky programmer whose been tearing their hair out trying to do something that by rights should be easy & simple. They could also do the harder work of tracking down what the compile-time flags are that need to be added/undefined/changed so that the guards in 'shobjidl.h' will let the preprocessor get to the definitions of IFileDialog, IFIleOpenDialog and IFileSaveDialog.

Presumably, that would result in many existing failures to get mingw32 gcc to compile IFileDialog code, or even COM interfaces generally, fixed.

To see it working, I have included a sample program in source code.

The sample project, made up of files "main.cpp", "main.h", and "Makefile", demonstrates the fix. Type:
> make test

Then run test.exe:
> test

Voila!

Please email me at mailto:digital.artist@hotmail.co.uk just to let me know my solution helped you. My name is Dave.
