//-----------------------------------------------------------------------------
// Copyright (c) 2014 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef __DISKASYNCRESULT_H_
#define __DISKASYNCRESULT_H_
#pragma once

#include "DiskSafeHandle.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Threading;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class DiskAsyncResult (internal)
//
// IAsyncResult-based object used to manage the asynchronous OVERLAPPED calls
// to the disk IOCTL functions
//---------------------------------------------------------------------------

ref class DiskAsyncResult sealed : IAsyncResult
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
	DiskAsyncResult(DiskSafeHandle^ handle, Object^ state);

	//-----------------------------------------------------------------------
	// Internal Overloaded Operators

	operator LPOVERLAPPED() { return reinterpret_cast<LPOVERLAPPED>(m_pNativeOverlapped); }

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// EndOperation
	//
	// Completes the asynchronous I/O operation
	static void EndOperation(IAsyncResult^ asyncResult);

private:

	// DESTRUCTOR / FINALIZER
	~DiskAsyncResult() { this->!DiskAsyncResult(); GC::SuppressFinalize(this); }
	!DiskAsyncResult();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// EndOperation
	//
	// Completes the asynchronous I/O operation
	void EndOperation(void);

	//-----------------------------------------------------------------------
	// Member Variables

	initonly DiskSafeHandle^			m_handle;
	initonly Object^					m_state;
	int									m_completed;
	ManualResetEvent^					m_event;
	Overlapped^							m_overlapped;
	NativeOverlapped*					m_pNativeOverlapped;
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __DISKASYNCRESULT_H_
