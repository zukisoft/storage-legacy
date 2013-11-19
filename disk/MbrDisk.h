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

#ifndef __MBRDISK_H_
#define __MBRDISK_H_
#pragma once

#include "Disk.h"						// Include Disk declarations
#include "DiskApi.h"					// Include DiskApi declarations
#include "MbrPartition.h"				// Include MbrPartition declarations
#include "PartitionList.h"				// Include PartitionList declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings
#pragma warning(disable:4461)			// Finalizer without destructor

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class MbrDisk
//
// MBR Disk Management Class
//---------------------------------------------------------------------------

public ref class MbrDisk : public Disk
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// Partitions
	//
	// Gets a reference to the contained Partition collection
	property PartitionList<MbrPartition^>^ Partitions
	{
		PartitionList<MbrPartition^>^ get(void) { return m_partitions; }
	}

	// Signature
	//
	// Gets/sets the disk signature
	property int Signature
	{
		int get(void) { return static_cast<int>(m_pLayoutMbr->Signature); }
		void set(int value);
	}

internal:

	// INTERNAL CONSTRUCTORS
	MbrDisk(HANDLE handle, PDISK_GEOMETRY_EX pGeometry, PDRIVE_LAYOUT_INFORMATION_EX pLayout);

private:

	// FINALIZER
	!MbrDisk();

	//-----------------------------------------------------------------------
	// Member Variables

	PDRIVE_LAYOUT_INFORMATION_MBR	m_pLayoutMbr;	// MBR specific layout
	PartitionList<MbrPartition^>^	m_partitions;	// Partition collection
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __GPTDISK_H_
