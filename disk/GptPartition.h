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

#ifndef __GPTPARTITION_H_
#define __GPTPARTITION_H_
#pragma once

#include "DiskUtil.h"
#include "GptPartitionAttributes.h"
#include "GptPartitionType.h"
#include "Partition.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class GptPartition
//
// Specializes Partition for GPT-specific information
//---------------------------------------------------------------------------

public ref class GptPartition sealed : public Partition
{
public:

	// Instance Constructors
	GptPartition();

	//-------------------------------------------------------------------------
	// Properties

	// Attributes
	//
	// Gets/Sets the EFI attribute flags
	property GptPartitionAttributes Attributes
	{
		GptPartitionAttributes get(void) { return static_cast<GptPartitionAttributes>(m_pInfo->Gpt.Attributes); }
		void set(GptPartitionAttributes value) { m_pInfo->Gpt.Attributes = static_cast<DWORD64>(value); }
	}

	// Name
	//
	// Gets/Sets the partition name (36 character maximum)
	property String^ Name
	{
		String^ get(void);
		void set(String^ value);
	}

	// PartitionId
	//
	// Gets/Sets the partition ID GUID
	property Guid PartitionId
	{
		Guid get(void) { return DiskUtil::UUIDToSysGuid(m_pInfo->Gpt.PartitionId); }
		void set(Guid value) { m_pInfo->Gpt.PartitionId = DiskUtil::SysGuidToUUID(value); }
	}

	// PartitionType
	//
	// Gets/Sets the partition type GUID
	property GptPartitionType PartitionType
	{
		GptPartitionType get(void) { return GptPartitionType(m_pInfo->Gpt.PartitionType); }
		void set(GptPartitionType value) { m_pInfo->Gpt.PartitionType = DiskUtil::SysGuidToUUID(value); }
	}

internal:

	// INTERNAL CONSTRUCTORS
	GptPartition(PPARTITION_INFORMATION_EX pInfo);
	GptPartition(GptPartitionType type, int number, __int64 length, __int64 offset, Guid partitionId);
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __GPTPARTITION_H_
