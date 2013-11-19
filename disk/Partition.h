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

#ifndef __PARTITION_H_
#define __PARTITION_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings
#pragma warning(disable:4461)			// Finalizer without destructor

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class Partition
//
// Information about a RAW disk partition
//---------------------------------------------------------------------------

public ref class Partition
{
public:

	// Instance Constructor
	Partition();

	//-------------------------------------------------------------------------
	// Properties

	// Length
	//
	// The length of the partition
	property __int64 PartitionLength
	{
		__int64 get(void) { return static_cast<__int64>(m_pInfo->PartitionLength.QuadPart); }
		void set(__int64 value);
	}

	// Number
	//
	// Gets/Sets the partition number
	property int PartitionNumber
	{
		int get(void) { return static_cast<int>(m_pInfo->PartitionNumber); }
		void set(int value);
	}

	// StartingOffset
	//
	// The starting offset of the partition on the disk
	property __int64 StartingOffset
	{
		__int64 get(void) { return static_cast<__int64>(m_pInfo->StartingOffset.QuadPart); }
		void set(__int64 value);
	}

internal:

	// INTERNAL CONSTRUCTORS
	Partition(PPARTITION_INFORMATION_EX pInfo);

	//-----------------------------------------------------------------------
	// Internal Operators

	// operator PPARTITION_INFORMATION_EX
	//
	// Exposes the contained PARTITION_INFORMATION_EX pointer
	static operator PPARTITION_INFORMATION_EX(Partition^ rhs);

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// CompareByPartitionNumber
	//
	// Comparison<T> function for sorting partitions by number
	static int CompareByPartitionNumber(Partition^ lhs, Partition^ rhs);

	// CompareByStartingOffset
	//
	// Comparison<T> function for sorting partitions by offset
	static int CompareByStartingOffset(Partition^ lhs, Partition^ rhs);

protected:

	//-----------------------------------------------------------------------
	// Protected Member Variables

	PPARTITION_INFORMATION_EX		m_pInfo;		// Partition information

private:

	// FINALIZER
	!Partition();
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __PARTITION_H_
