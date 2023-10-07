Microsoft Visual C++ v4.x Comaptable IDAPI32 Import Library
-----------------------------------------------------------

Borland International is not responsible for the use of 
these files.  Use at your own risk.  Borland does not 
support these files.


Files contained in ZIP
----------------------
README.TXT   --  This file
IDAPI32M.LIB --  VC4 compatible import library
MS-IDAPI.H   --  Header file for use with VC4


Instructions
------------
1) include ms-idapi.h into your C / CPP file(s) containing 
   the Dbi functions.  Do not use idapi.h directly; only
   ms-idapi.h.

2) add idapi32m.lib to your project


Differences between VC4 and BC++ BDE32 compiled EXEs
----------------------------------------------------
The only difference between the two compiled EXEs is
that the BC++ EXE will look in the registry to find 
the path to the IDAPI32 core DLLs;  The VC4 EXE will
need to have the IDAPI32 core DLLs in the path 
statement to find the DLLs.

There are no other differences

No need to call GetProcAddress, LoadLibrary, etc.
