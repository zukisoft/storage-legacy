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


#include "stdafx.h"						// Include project pre-compiled headers
#include "DiskAsyncResult.h"			// Include DiskAsyncResult decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// DiskAsyncResult Constructor (internal)
//
// Arguments:
//
//	handle		- Open DiskSafeHandle instance
//	state		- IAsyncResult state object

DiskAsyncResult::DiskAsyncResult(DiskSafeHandle^ handle, Object^ state) : 
	m_handle(handle), m_state(state), m_completed(false)
{
	// Can't check this
	// if(handle == nullptr) throw gcnew ArgumentNullException("handle");

	m_event = gcnew ManualResetEvent(false);
	m_overlapped = gcnew Overlapped(0, 0, m_event->SafeWaitHandle->DangerousGetHandle(), this);
	m_pNativeOverlapped = m_overlapped->Pack(nullptr, nullptr);
}

//---------------------------------------------------------------------------
// DiskAsyncResult Finalizer

DiskAsyncResult::!DiskAsyncResult()
{
	if(m_pNativeOverlapped) Overlapped::Free(m_pNativeOverlapped);
	m_pNativeOverlapped = NULL;
}

//---------------------------------------------------------------------------
// DiskAsyncResult::EndOperation (internal, static)
//
// Completes the asynchronous I/O operation
//
// Arguments:
//
//	asyncResult		- IAsyncResult object instance

void DiskAsyncResult::EndOperation(IAsyncResult^ asyncResult)
{
	DiskAsyncResult^ instance = safe_cast<DiskAsyncResult^>(asyncResult);
	instance->EndOperation();
}

//---------------------------------------------------------------------------
// DiskAsyncResult::EndOperation (private)
//
// Completes the asynchronous I/O operation
//
// Arguments:
//
//	NONE

void DiskAsyncResult::EndOperation(void)
{
	DWORD					cbTransferred;				// Bytes transferred

	m_event->WaitOne();									// Wait for the I/O operation to complete

	// Complete the asynchronous operation
	if(!GetOverlappedResult(m_handle, reinterpret_cast<LPOVERLAPPED>(m_pNativeOverlapped), &cbTransferred, FALSE))
		throw gcnew Win32Exception(GetLastError());

	Interlocked::Exchange(m_completed, 1);				// Set the completion flag
	Overlapped::Free(m_pNativeOverlapped);				// Release native OVERLAPPED structure
	m_pNativeOverlapped = NULL;							// Reset pointer to NULL
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
