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


#include "stdafx.h"						// Include project pre-compiled headers
#include "VirtualDiskAsyncResult.h"		// Include VirtualDiskAsyncResult decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// VirtualDiskAsyncResult Constructor (internal)
//
// Arguments:
//
//	handle		- Open VirtualDiskSafeHandle instance
//	state		- IAsyncResult state object

VirtualDiskAsyncResult::VirtualDiskAsyncResult(VirtualDiskSafeHandle^ handle, Object^ state) : 
	m_handle(handle), m_state(state), m_completed(false)
{
	// Can't check this
	// if(handle == nullptr) throw gcnew ArgumentNullException("handle");

	m_event = gcnew ManualResetEvent(false);
	m_overlapped = gcnew Overlapped(0, 0, m_event->SafeWaitHandle->DangerousGetHandle(), this);
	m_pNativeOverlapped = m_overlapped->Pack(nullptr, nullptr);
}

//---------------------------------------------------------------------------
// VirtualDiskAsyncResult Finalizer

VirtualDiskAsyncResult::!VirtualDiskAsyncResult()
{
	if(m_pNativeOverlapped) Overlapped::Free(m_pNativeOverlapped);
	m_pNativeOverlapped = NULL;
}

//---------------------------------------------------------------------------
// VirtualDiskAsyncResult::EndOperation (internal, static)
//
// Completes the asynchronous I/O operation
//
// Arguments:
//
//	asyncResult		- IAsyncResult object instance

VirtualDiskAsyncStatus VirtualDiskAsyncResult::EndOperation(IAsyncResult^ asyncResult)
{
	VirtualDiskAsyncResult^ instance = safe_cast<VirtualDiskAsyncResult^>(asyncResult);
	return instance->EndOperation();
}

//---------------------------------------------------------------------------
// VirtualDiskAsyncResult::EndOperation (private)
//
// Completes the asynchronous I/O operation
//
// Arguments:
//
//	NONE

VirtualDiskAsyncStatus VirtualDiskAsyncResult::EndOperation(void)
{
	VIRTUAL_DISK_PROGRESS			progress;			// Operation progress information
	DWORD							dwResult;			// Result from function call

	m_event->WaitOne();									// Wait for the I/O operation to complete

	// Get the final operation progress so that it can be returned by this function
	dwResult = GetVirtualDiskOperationProgress(m_handle, reinterpret_cast<LPOVERLAPPED>(m_pNativeOverlapped), &progress);
	if(dwResult != ERROR_SUCCESS) throw gcnew Win32Exception(dwResult);

	Interlocked::Exchange(m_completed, 1);				// Set the completion flag
	Overlapped::Free(m_pNativeOverlapped);				// Release native OVERLAPPED structure
	m_pNativeOverlapped = NULL;							// Reset pointer to NULL

	return VirtualDiskAsyncStatus(&progress);
}

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
