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
#include "Partition.h"					// Include Partition decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Partition Constructor
//
// Arguments:
//
//	NONE

Partition::Partition()
{
	// Allocate and intialize the contained PARTITION_INFORMATION_EX
	m_pInfo = new PARTITION_INFORMATION_EX();
	if(!m_pInfo) throw gcnew OutOfMemoryException();
	ZeroMemory(m_pInfo, sizeof(PARTITION_INFORMATION_EX));

	// Default the partition style to RAW; derived classes can override this
	m_pInfo->PartitionStyle = PARTITION_STYLE_RAW;

	// .RewritePartition should always be set to TRUE
	m_pInfo->RewritePartition = TRUE;
}

//---------------------------------------------------------------------------
// Partition Constructor (internal)
//
// Arguments:
//
//	pInfo		- Existing PARTITION_INFORMATION_EX with which to initialize

Partition::Partition(PPARTITION_INFORMATION_EX pInfo)
{
	if(!pInfo) throw gcnew ArgumentNullException("pInfo");

	// BASIC PARTITION INFORMATION
	m_pInfo = new PARTITION_INFORMATION_EX();
	if(!m_pInfo) throw gcnew OutOfMemoryException();
	memcpy(m_pInfo, pInfo, sizeof(PARTITION_INFORMATION_EX));
}

//---------------------------------------------------------------------------
// Partition Finalizer

Partition::!Partition()
{
	if(m_pInfo) delete m_pInfo;
	m_pInfo = NULL;
}

//---------------------------------------------------------------------------
// Partition::operator PPARTITION_INFORMATION_EX (static)

Partition::operator PPARTITION_INFORMATION_EX(Partition^ rhs) 
{ 
	return rhs->m_pInfo;
}

//-----------------------------------------------------------------------------
// Partition::CompareByPartitionNumber (static, internal)
//
// Compares two Partition objects by the partition number

int Partition::CompareByPartitionNumber(Partition^ lhs, Partition^ rhs)
{
	return (lhs->PartitionNumber - rhs->PartitionNumber);
}

//-----------------------------------------------------------------------------
// Partition::CompareByStartingOffset (static, internal)
//
// Compares two Partition objects by the starting offset value

int Partition::CompareByStartingOffset(Partition^ lhs, Partition^ rhs)
{
	__int64 delta = lhs->StartingOffset - rhs->StartingOffset;

	if(delta > 0) return 1;					// LHS is larger
	else if(delta < 0) return -1;			// RHS is larger

	return 0;								// LHS == RHS
}

//-----------------------------------------------------------------------------
// Partition::PartitionLength::set
//
// Sets the partition length

void Partition::PartitionLength::set(__int64 value)
{
	if(value < 0) throw gcnew ArgumentOutOfRangeException("value");
	m_pInfo->PartitionLength.QuadPart = static_cast<LONGLONG>(value);
}

//-----------------------------------------------------------------------------
// Partition::PartitionNumber::set
//
// Sets the partition number

void Partition::PartitionNumber::set(int value)
{
	if(value < 0) throw gcnew ArgumentOutOfRangeException("value");
	m_pInfo->PartitionNumber = static_cast<DWORD>(value);
}

//-----------------------------------------------------------------------------
// Partition::StartingOffset::set
//
// Sets the partition offset

void Partition::StartingOffset::set(__int64 value)
{
	if(value < 0) throw gcnew ArgumentOutOfRangeException("value");
	m_pInfo->StartingOffset.QuadPart = static_cast<LONGLONG>(value);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
