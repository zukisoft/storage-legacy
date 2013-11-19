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

#ifndef __VIRTUALDISKSAFEHANDLE_H_
#define __VIRTUALDISKSAFEHANDLE_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace Microsoft::Win32::SafeHandles;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskSafeHandle (internal)
//
// A SafeHandle-dervied class for unmanaged virtual disk handles
//---------------------------------------------------------------------------

ref class VirtualDiskSafeHandle sealed : public SafeHandleZeroOrMinusOneIsInvalid
{
public:

	// CONSTRUCTORS
	VirtualDiskSafeHandle() : SafeHandleZeroOrMinusOneIsInvalid(true) {}
	
	VirtualDiskSafeHandle(HANDLE handle) : SafeHandleZeroOrMinusOneIsInvalid(true) {
		SafeHandleZeroOrMinusOneIsInvalid::SetHandle(IntPtr(reinterpret_cast<void*>(handle))); 
	}

	VirtualDiskSafeHandle(IntPtr handle, bool ownsHandle) : SafeHandleZeroOrMinusOneIsInvalid(ownsHandle) {
		SafeHandleZeroOrMinusOneIsInvalid::SetHandle(handle);
	}

	VirtualDiskSafeHandle(HANDLE handle, bool ownsHandle) : SafeHandleZeroOrMinusOneIsInvalid(ownsHandle) {
		SafeHandleZeroOrMinusOneIsInvalid::SetHandle(IntPtr(reinterpret_cast<void*>(handle)));
	}

	//-----------------------------------------------------------------------
	// Overloaded Operators

	// HANDLE() --> Use this class as type HANDLE for Win32 API calls
	operator HANDLE() { return reinterpret_cast<HANDLE>(SafeHandleZeroOrMinusOneIsInvalid::handle.ToPointer()); }

	//-----------------------------------------------------------------------
	// Member Functions

	// ReleaseHandle (SafeHandleZeroOrMinusOneIsInvalid)
	//
	// Frees the unmanaged handle object
	virtual bool ReleaseHandle(void) override
	{
		return (CloseHandle(SafeHandleZeroOrMinusOneIsInvalid::handle.ToPointer()) != 0);
	}

	// SetHandle
	//
	// Sets the contained handle.  Only use this when it can't be set during construction
	void SetHandle(HANDLE handle) { SafeHandleZeroOrMinusOneIsInvalid::SetHandle(IntPtr(reinterpret_cast<void*>(handle))); }
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKSAFEHANDLE_H_
