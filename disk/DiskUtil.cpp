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

#include "stdafx.h"					// Include project pre-compiled headers
#include "DiskUtil.h"				// Include DiskUtil declarations

using namespace System;

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// DiskUtil::AlignDown
//
// Aligns an offset down to the specified alignment
//
// Arguments:
//
//	offset		- Value to be aligned
//	alignment	- Alignment

__int64 DiskUtil::AlignDown(__int64 offset, __int64 alignment)
{
	if(offset < 0) throw gcnew ArgumentOutOfRangeException("offset");
	if(alignment < 1) throw gcnew ArgumentOutOfRangeException("alignment");

	if(offset < alignment) return 0;
	else return AlignUp(offset - (alignment - 1), alignment);
}

//---------------------------------------------------------------------------
// DiskUtil::AlignUp
//
// Aligns an offset up to the specified alignment
//
// Arguments:
//
//	offset		- Value to be aligned
//	alignment	- Alignment

__int64 DiskUtil::AlignUp(__int64 offset, __int64 alignment)
{
	if(offset < 0) throw gcnew ArgumentOutOfRangeException("offset");
	if(alignment < 1) throw gcnew ArgumentOutOfRangeException("alignment");

	if(offset == 0) return 0;
	else return offset + ((alignment - (offset % alignment)) % alignment);
}

//---------------------------------------------------------------------------
// DiskUtil::FreePWSTR
//
// Releases a C-style string allocated by StringToPWSTR
//
// Arguments:
//
//	pwstr		- Unmanaged string pointer

PWSTR DiskUtil::FreePWSTR(PWSTR pwstr)
{
	if(!pwstr) return NULL;

	Marshal::FreeHGlobal(IntPtr(reinterpret_cast<void*>(pwstr)));
	return NULL;
}

//---------------------------------------------------------------------------
// DiskUtil::StringToPWSTR
//
// Converts a System::String into a unicode C-style string.  Release the 
// memory allocated for the string with Marshal::FreeHGlobal
//
// Arguments:
//
//	string		- String to be converted

PWSTR DiskUtil::StringToPWSTR(String^ string)
{
	if(string == nullptr) return NULL;
	return reinterpret_cast<PWSTR>(Marshal::StringToHGlobalUni(string).ToPointer());
}

//---------------------------------------------------------------------------
// DiskUtil::SysGuidToUUID
//
// Converts a managed System::Guid structure into a standard UUID structure
//
// Arguments:
//
//	guid		- The managed System::Guid to be converted

UUID DiskUtil::SysGuidToUUID(Guid guid)
{
	array<Byte>^ guidData = guid.ToByteArray();
	PinnedBytePtr data = &(guidData[0]);
	return *reinterpret_cast<UUID*>(data);
}

//---------------------------------------------------------------------------
// DiskUtil::UUIDToSysGuid
//
// Converts an unmanaged UUID structure into a managed System::Guid structure
//
// Arguments:
//
//	guid		- The unmanaged UUID structure to be converted

Guid DiskUtil::UUIDToSysGuid(const UUID& guid)
{
   return Guid(guid.Data1, guid.Data2, guid.Data3, guid.Data4[0],
	   guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5],
	   guid.Data4[6], guid.Data4[7]);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
