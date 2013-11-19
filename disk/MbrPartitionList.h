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

#ifndef __MBRPARTITIONLIST_H_
#define __MBRPARTITIONLIST_H_
#pragma once

#include "MbrPartition.h"				// Include MbrPartition declartions
#include "PartitionList.h"				// Include PartitionList declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class MbrPartitionList
//
// MBR partition management collection
//---------------------------------------------------------------------------

public ref class MbrPartitionList : public PartitionList<MbrPartition^>
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Add
	//
	// Adds a new partition to the disk
	//GptPartition^ Add(void);
	//GptPartition^ Add(__int64 length);
	//GptPartition^ Add(__int64 length, __int64 offset);
	//GptPartition^ Add(__int64 length, __int64 offset, GptPartitionType type);
	//GptPartition^ Add(__int64 length, __int64 offset, GptPartitionType type, Guid partitionId);

internal:

	// INTERNAL CONSTRUCTORS
	MbrPartitionList(Disk^ disk) : PartitionList(disk) {}

private:
	
	//-----------------------------------------------------------------------
	// Member Variables
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __MBRPARTITIONLIST_H_
