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

#ifndef __GPTPARTITIONLIST_H_
#define __GPTPARTITIONLIST_H_
#pragma once

#include "DiskUtil.h"					// Include DiskUtil declarations
#include "GptDisk.h"					// Include GptDisk declarations
#include "GptPartition.h"				// Include GptPartition declarations
#include "PartitionList.h"				// Include PartitionList declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class GptPartitionList
//
// GPT partition management collection
//---------------------------------------------------------------------------

public ref class GptPartitionList : public PartitionList<GptPartition^>
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Add
	//
	// Automatically adds a new partition to the disk
	GptPartition^ Add(GptPartitionType type);
	GptPartition^ Add(GptPartitionType type, __int64 length);
	GptPartition^ Add(GptPartitionType type, __int64 length, Guid partitionId);

internal:

	// INTERNAL CONSTRUCTORS
	GptPartitionList(Disk^ disk);

private:
	
	//-----------------------------------------------------------------------
	// Private Member Functions

	// FindAlignedLargestFreeSpace
	//
	// Locates the largest available block of free space on the disk
	__int64 FindAlignedLargestFreeSpace([Out] __int64% length);

	// FindAlignedStartingOffsetForLength
	//
	// Locates an available starting offset for a specific partition length
	__int64 FindAlignedStartingOffsetForLength(__int64 length);

	// FindAvailablePartitionNumber
	//
	// Locates an available partition number
	int FindAvailablePartitionNumber(void);

	//-----------------------------------------------------------------------
	// Member Variables

	GptDisk^					m_disk;				// GPT disk instance
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __GPTPARTITIONLIST_H_
