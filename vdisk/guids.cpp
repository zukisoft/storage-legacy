//---------------------------------------------------------------------------
// ZukiSoft Virtual Disk Functions
//
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.TXT at the root of this distribution.
// By using this software in any fashion, you are agreeing to be bound by
// the terms of this license. You must not remove this notice, or any other,
// from this software.
//
// Contributor(s):
//	Michael G. Brehm (original author)
//---------------------------------------------------------------------------

//
// This file specifies INITGUID so that GUIDs declared with DEFINE_GUID in a
// Windows header file will be visible to the linker.  Disable pre-compiled 
// headers in the C/C++ properties for this file
//

#define WINVER				_WIN32_WINNT_WIN8
#define	_WIN32_WINNT		_WIN32_WINNT_WIN8
#define	_WIN32_IE			_WIN32_IE_IE80

#define INITGUID

#include <windows.h>		// Base Windows GUIDs
#include <virtdisk.h>		// Virtual disk GUIDs

//---------------------------------------------------------------------------
