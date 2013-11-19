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

#ifndef __PARTITIONLIST_H_
#define __PARTITIONLIST_H_
#pragma once

#include "Disk.h"						// Include Disk declarations
#include "DiskApi.h"					// Include DiskApi declarations
#include "Partition.h"					// Include Partition declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class PartitionList
//
// Partition management collection
//---------------------------------------------------------------------------

generic <class T>
where T : Partition
public ref class PartitionList : public List<T>
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Persist
	//
	// Persists the contents of the collection to the disk
	void Persist(void);

	// Refresh
	//
	// Refreshes the contents of the collection
	void Refresh(void);

	//-----------------------------------------------------------------------
	// Properties

	// Alignment
	//
	// Gets/sets the partition alignment value for the disk
	property __int64 DefaultAlignment
	{
		__int64 get(void) { return m_alignment; }
		void set(__int64 value) { m_alignment = value; }
	}

internal:

	// INTERNAL CONSTRUCTORS
	PartitionList(Disk^ disk);

protected:
	
	//-----------------------------------------------------------------------
	// Protected Member Variables

	__int64				m_alignment;		// Partition alignment

private:

	//-----------------------------------------------------------------------
	// Private Member Functions

	// CreatePartitionClass
	//
	// Workaround for C++/CLI generic limitation
	static T CreatePartitionClass(PPARTITION_INFORMATION_EX pInfo);

	// GetDefaultAlignment
	//
	// Gets the default partition alignment for the parent disk
	static __int64 GetDefaultAlignment(__int64 length);

	//-----------------------------------------------------------------------
	// Member Variables

	initonly Disk^			m_disk;			// Parent disk object
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __PARTITIONLIST_H_
