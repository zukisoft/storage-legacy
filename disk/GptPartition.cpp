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
#include "GptPartition.h"				// Include GptPartition decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// GptPartition Constructor
//
// Arguments:
//
//	NONE

GptPartition::GptPartition() : Partition()
{
	// Set the parent partition style to GPT
	m_pInfo->PartitionStyle = PARTITION_STYLE_GPT;

	// Set a couple reasonable defaults for a GPT partition
	m_pInfo->Gpt.PartitionId = DiskUtil::SysGuidToUUID(Guid::NewGuid());
	m_pInfo->Gpt.PartitionType = DiskUtil::SysGuidToUUID(GptPartitionType::BasicData);
}

//---------------------------------------------------------------------------
// GptPartition Constructor (internal)
//
// Arguments:
//
//	type			- Partition type
//	number			- Partition number
//	length			- Partition length
//	offset			- Partition starting offset
//	partitionId		- Partition identifier

GptPartition::GptPartition(GptPartitionType type, int number, __int64 length, __int64 offset, Guid partitionId) : Partition()
{
	// Set the parent partition style to GPT
	m_pInfo->PartitionStyle = PARTITION_STYLE_GPT;

	// Set a couple reasonable defaults for a GPT partition
	m_pInfo->Gpt.PartitionId = DiskUtil::SysGuidToUUID(Guid::NewGuid());
	m_pInfo->Gpt.PartitionType = DiskUtil::SysGuidToUUID(GptPartitionType::BasicData);

	// Apply constructor arguments
	Partition::PartitionNumber = number;
	Partition::StartingOffset = offset;
	Partition::PartitionLength = length;
	GptPartition::PartitionType = type;
	GptPartition::PartitionId = partitionId;
}

//---------------------------------------------------------------------------
// GptPartition Constructor (internal)
//
// Arguments:
//
//	pInfo		- Pointer to the PPARTITION_INFORMATION_EX structure

GptPartition::GptPartition(PPARTITION_INFORMATION_EX pInfo) : Partition(pInfo)
{
	if(!pInfo) throw gcnew ArgumentNullException("pInfo");
	if(pInfo->PartitionStyle != PARTITION_STYLE_GPT) 
		throw gcnew ArgumentException("Partition data is not GPT", "pInfo");
}

//---------------------------------------------------------------------------
// GptPartition::Name::get
//
// Gets the partition name

String^ GptPartition::Name::get(void)
{
	// This is a fixed-length string without a NULL terminator; handle it
	return Marshal::PtrToStringUni(IntPtr(m_pInfo->Gpt.Name), 36)->TrimEnd(gcnew array<wchar_t> { '\0' });
}

//---------------------------------------------------------------------------
// GptPartition::Name::set
//
// Sets the partition name

void GptPartition::Name::set(String^ value)
{
	PinnedStringPtr				pinName;			// Pinned string value

	// The partition name cannot be longer than 36 characters
	if(!String::IsNullOrEmpty(value) && (value->Length > 36))
		throw gcnew ArgumentOutOfRangeException("value", "GPT partition names are limited to 36 characters");

	pinName = PtrToStringChars(value);
	ZeroMemory(m_pInfo->Gpt.Name, sizeof(WCHAR) * 36);
	StringCchCopyN(m_pInfo->Gpt.Name, 36, pinName, value->Length);
}

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
