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

#ifndef __VIRTUALDISKASYNCSTATUS_H_
#define __VIRTUALDISKASYNCSTATUS_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Threading;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskAsyncStatus
//
// Provides status information about an asynchronous virtual disk operation
//---------------------------------------------------------------------------

public value class VirtualDiskAsyncStatus sealed
{
public:

	//-----------------------------------------------------------------------
	// Fields

	initonly int			Status;
	initonly __int64		CurrentValue;
	initonly __int64		CompletionValue;

	//-----------------------------------------------------------------------
	// Properties

	// PercentComplete
	//
	// Convenience property to expose the operation complete percentage
	property float PercentComplete
	{
		float get(void) 
		{ 
			if(CompletionValue <= 0) return 0.0f;
			else return (static_cast<float>(CurrentValue) / static_cast<float>(CompletionValue)) * 100.0f; 
		}
	}

internal:

	// CONSTRUCTOR
	VirtualDiskAsyncStatus(PVIRTUAL_DISK_PROGRESS progress) : 
		Status(progress->OperationStatus), CurrentValue(progress->CurrentValue), 
		CompletionValue(progress->CompletionValue) {}
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKASYNCSTATUS_H_
