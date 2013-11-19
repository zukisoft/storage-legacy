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

#ifndef __VIRTUALDISKASYNCRESULT_H_
#define __VIRTUALDISKASYNCRESULT_H_
#pragma once

#include "VirtualDiskAsyncStatus.h"
#include "VirtualDiskSafeHandle.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Threading;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskAsyncResult (internal)
//
// IAsyncResult-based object used to manage the asynchronous OVERLAPPED calls
// to the virtual disk functions
//---------------------------------------------------------------------------

ref class VirtualDiskAsyncResult sealed : IAsyncResult
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// AsyncState (IAsyncResult)
	//
	// Gets a user-defined object that qualifies or contains information about 
	// the asynchronous operation
	property Object^ AsyncState
	{
		virtual Object^ get(void) { return m_state; }
	}

	// AsyncWaitHandle (IAsyncResult)
	//
	// Gets a WaitHandle that is used to wait for an asynchronous operation to complete
	property WaitHandle^ AsyncWaitHandle
	{
		virtual WaitHandle^ get(void) { return m_event; }
	}

	// CompletedSynchronously (IAsyncResult)
	//
	// Gets a value that indicates whether the asynchronous operation completed 
	// synchronously
	property bool CompletedSynchronously
	{
		virtual bool get(void) { return false; }
	}

	// IsCompleted (IAsyncResult)
	//
	// Gets a value that indicates whether the asynchronous operation has completed
	property bool IsCompleted
	{
		virtual bool get(void) { return (m_completed != 0); }
	}

internal:

	// INTERNAL CONSTRUCTORS
	VirtualDiskAsyncResult(VirtualDiskSafeHandle^ handle, Object^ state);

	//-----------------------------------------------------------------------
	// Internal Overloaded Operators

	operator LPOVERLAPPED() { return reinterpret_cast<LPOVERLAPPED>(m_pNativeOverlapped); }

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// EndOperation
	//
	// Completes the asynchronous I/O operation
	static VirtualDiskAsyncStatus EndOperation(IAsyncResult^ asyncResult);

private:

	// DESTRUCTOR / FINALIZER
	~VirtualDiskAsyncResult() { this->!VirtualDiskAsyncResult(); GC::SuppressFinalize(this); }
	!VirtualDiskAsyncResult();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// EndOperation
	//
	// Completes the asynchronous I/O operation
	VirtualDiskAsyncStatus EndOperation(void);

	//-----------------------------------------------------------------------
	// Member Variables

	initonly VirtualDiskSafeHandle^		m_handle;
	initonly Object^					m_state;
	int									m_completed;
	ManualResetEvent^					m_event;
	Overlapped^							m_overlapped;
	NativeOverlapped*					m_pNativeOverlapped;
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKASYNCRESULT_H_
