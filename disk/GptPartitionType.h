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

#ifndef __GPTPARTITIONTYPE_H_
#define __GPTPARTITIONTYPE_H_
#pragma once

#include "DiskUtil.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class GptPartitionType
//
// Defines GPT partition EFI types
//---------------------------------------------------------------------------

public value class GptPartitionType sealed
{
public:

	// Constructor
	//
	// Necessary since Microsoft doesn't define all the possible type uuids
	GptPartitionType(Guid type) : m_type(type) {}

	//-----------------------------------------------------------------------
	// Overloaded Operators

	bool operator ==(GptPartitionType rhs) { return rhs.m_type == this->m_type; }
	bool operator !=(GptPartitionType rhs) { return rhs.m_type != this->m_type; }

	static operator Guid (GptPartitionType rhs) { return rhs.m_type; }

	//-----------------------------------------------------------------------
	// Fields

	static initonly GptPartitionType Unused						= GptPartitionType(PARTITION_ENTRY_UNUSED_GUID);
	static initonly GptPartitionType BasicData					= GptPartitionType(PARTITION_BASIC_DATA_GUID);
	static initonly GptPartitionType LogicalDiskManagerData		= GptPartitionType(PARTITION_LDM_DATA_GUID);
	static initonly GptPartitionType LogicalDiskManagerMetadata	= GptPartitionType(PARTITION_LDM_METADATA_GUID);
	static initonly GptPartitionType MicrosoftRecovery			= GptPartitionType(PARTITION_MSFT_RECOVERY_GUID);
	static initonly GptPartitionType MicrosoftReserved			= GptPartitionType(PARTITION_MSFT_RESERVED_GUID);
	static initonly GptPartitionType System						= GptPartitionType(PARTITION_SYSTEM_GUID);

internal:

	// INTERNAL CONSTRUCTORS
	GptPartitionType(const UUID& type) : m_type(DiskUtil::UUIDToSysGuid(type)) {}

	//-----------------------------------------------------------------------
	// Member Variables

	initonly	Guid				m_type;			// Type GUID
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __GPTPARTITIONTYPE_H_
