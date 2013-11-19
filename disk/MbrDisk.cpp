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
#include "MbrDisk.h"					// Include MbrDisk declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//-----------------------------------------------------------------------------
// MbrDisk Constructor (internal)
//
// Arguments:
//
//	handle			- Handle to the open disk object
//	pGeometry		- DISK_GEOMETRY_EX information for the disk
//	pLayout			- DRIVE_LAYOUT_INFORMATION_EX data for the disk

MbrDisk::MbrDisk(HANDLE handle, PDISK_GEOMETRY_EX pGeometry, PDRIVE_LAYOUT_INFORMATION_EX pLayout) 
	: m_pLayoutMbr(NULL), Disk(handle, pGeometry)
{
	if(handle == INVALID_HANDLE_VALUE) throw gcnew ArgumentNullException("handle");
	if(!pGeometry) throw gcnew ArgumentNullException("pGeometry");
	if(!pLayout) throw gcnew ArgumentNullException("pLayout");

	// MBR LAYOUT
	m_pLayoutMbr = new DRIVE_LAYOUT_INFORMATION_MBR();
	if(!m_pLayoutMbr) throw gcnew OutOfMemoryException();
	memcpy(m_pLayoutMbr, &pLayout->Mbr, sizeof(DRIVE_LAYOUT_INFORMATION_GPT));

	// PARTITION COLLECTION
	m_partitions = gcnew PartitionList<MbrPartition^>(this);
}

//---------------------------------------------------------------------------
// MbrDisk Finalizer

MbrDisk::!MbrDisk()
{
	if(m_pLayoutMbr) delete m_pLayoutMbr;
	m_pLayoutMbr = NULL;
}

//---------------------------------------------------------------------------
// MbrDisk::Signature::set
//
// Sets the MBR disk signature

void MbrDisk::Signature::set(int value)
{
	m_pLayoutMbr->Signature = static_cast<DWORD>(value);
	DiskApi::SetDriveLayoutInformationMbr(this, m_pLayoutMbr);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
