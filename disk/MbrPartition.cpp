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
#include "MbrPartition.h"				// Include MbrPartition decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// MbrPartition Constructor
//
// Arguments:
//
//	NONE

MbrPartition::MbrPartition() : Partition()
{
	// Set the parent partition style to MBR
	m_pInfo->PartitionStyle = PARTITION_STYLE_MBR;
}

//---------------------------------------------------------------------------
// MbrPartition Constructor (internal)
//
// Arguments:
//
//	pInfo	- Pointer to the PPARTITION_INFORMATION_EX structure

MbrPartition::MbrPartition(PPARTITION_INFORMATION_EX pInfo) : Partition(pInfo)
{
	if(!pInfo) throw gcnew ArgumentNullException("pInfo");
	if(pInfo->PartitionStyle != PARTITION_STYLE_MBR) 
		throw gcnew ArgumentException("Partition data is not MBR", "pInfo");
}

//---------------------------------------------------------------------------
// MbrPartition::HiddenSectors::set
//
// Sets the number of hidden sectors to allocate with the partition table

void MbrPartition::HiddenSectors::set(int value)
{
	if(value < 0) throw gcnew ArgumentOutOfRangeException("value");
	m_pInfo->Mbr.HiddenSectors = static_cast<DWORD>(value);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
