# IFileDialog-gcc-Fix
#
# gcc fix/solution for compiling COM Object IFileDialog (IFileOpenDialog and IFileSaveDialog).
#

I invested many minutes of research & dedicated time analyzing & testing the compilation process of gcc (g++, specifically) and it's use of the include file *shobjidl.h*, and I have returned from the battle arena with an elixer: a solution not yet easily-findable in google, at least.

I have a fix/solution for the problems people on the internet have had compiling a win32 app with the GCC (esp. MingW) 'g++' compiler, that uses the COM Object "IFileDialog", and thus "IFileOpenDialog" and "IFileSaveDialog". All they need do is

	#include "ifiledialog.h"

, which will allow them to create IFileOpenDialog and IFileSaveDialog dialog boxes and open them on the screen.
Also defines the IID_ and CLSID_ objects needed.

My fix (which is simple, and gives clues as to what the problem is), can be used by some plucky programmer whose been tearing their hair out trying to do something that by rights should be easy & simple. (Hint:) They could also do the harder work of tracking down what the compile-time flags/constants/etc are that need to be defined/undefined/changed so that the conditional guards in 'shobjidl.h' will let the preprocessor get to the definitions (NOT declerations, *definitions*) of IFileDialog, IFIleOpenDialog and IFileSaveDialog. To help, the guards do allow the compiler to process "IModalWindow", the interface IFileDialog inherits from (and is also defined in "shobjidl.h"). IFileOpenDialog & IFileSaveDialog inherit from IFileDialog.

Presumably, my observation would result in many existing failures to get mingw32 'g++' to compile IFileDialog code, or even COM interfaces generally, fixed.

To see it working, I have included a sample program in source code.

The sample project, made up of files *main.cpp* and *Makefile*, and utilising *ifiledialog.h*, demonstrates the fix. Type:
> make

Then run test.exe:
> test

Voila!

I forgot to mention, there are some library files that ship with gcc that need to be on the command line invoking g++. Some people on the internet had problems getting linkage references to resolve, because they weren't linking to the necessary static libraries that ship with gcc/win32_64 - see 'Makefile' for the necessary -l switches.

Please email me at mailto:digital.artist@hotmail.co.uk just to let me know if my solution helped you. My name is David. My mom calls me Scoochy-Moochy-McMuffin-Face, but you can call me Dave.
