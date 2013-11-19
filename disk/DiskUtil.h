//---------------------------------------------------------------------------
// ZukiSoft Disk Management
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

#ifndef __DISKUTIL_H_
#define __DISKUTIL_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class DiskUtil (internal)
//
// Collection of useful static functions
//---------------------------------------------------------------------------

ref class DiskUtil
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	static __int64			AlignDown(__int64 offset, __int64 alignment);
	static __int64			AlignUp(__int64 offset, __int64 alignment);
	static PWSTR			FreePWSTR(PWSTR pwstr);
	static PWSTR			FreePWSTR(PCWSTR pwstr) { return FreePWSTR(const_cast<PWSTR>(pwstr)); }
	static PWSTR			StringToPWSTR(String^ string);
	static UUID				SysGuidToUUID(Guid guid);
	static Guid				UUIDToSysGuid(const UUID& guid);
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __DISKUTIL_H_
