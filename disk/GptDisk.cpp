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
#include "GptDisk.h"					// Include GptDisk declarations
#include "GptPartitionList.h"			// Include GptPartitionList declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//-----------------------------------------------------------------------------
// GptDisk Constructor (internal)
//
// Arguments:
//
//	handle			- Handle to the open disk object
//	pGeometry		- DISK_GEOMETRY_EX information for the disk
//	pLayout			- DRIVE_LAYOUT_INFORMATION_EX for the disk

GptDisk::GptDisk(HANDLE handle, PDISK_GEOMETRY_EX pGeometry, PDRIVE_LAYOUT_INFORMATION_EX pLayout) 
	: m_pLayoutGpt(NULL), Disk(handle, pGeometry)
{
	if(handle == INVALID_HANDLE_VALUE) throw gcnew ArgumentNullException("handle");
	if(!pGeometry) throw gcnew ArgumentNullException("pGeometry");
	if(!pLayout) throw gcnew ArgumentNullException("pLayout");

	// GPT LAYOUT
	m_pLayoutGpt = new DRIVE_LAYOUT_INFORMATION_GPT();
	if(!m_pLayoutGpt) throw gcnew OutOfMemoryException();
	memcpy(m_pLayoutGpt, &pLayout->Gpt, sizeof(DRIVE_LAYOUT_INFORMATION_GPT));

	// PARTITION COLLECTION
	m_partitions = gcnew GptPartitionList(this);
}

//---------------------------------------------------------------------------
// GptDisk Finalizer

GptDisk::!GptDisk()
{
	if(m_pLayoutGpt) delete m_pLayoutGpt;
	m_pLayoutGpt = NULL;
}

//---------------------------------------------------------------------------
// GptDisk::DiskID::set
//
// Sets the GPT disk identifier

void GptDisk::DiskId::set(Guid value)
{
	m_pLayoutGpt->DiskId = DiskUtil::SysGuidToUUID(value);
	DiskApi::SetDriveLayoutInformationGpt(this, m_pLayoutGpt);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
