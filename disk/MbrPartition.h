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

#ifndef __MBRPARTITION_H_
#define __MBRPARTITION_H_
#pragma once

#include "MbrPartitionType.h"
#include "Partition.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class MbrPartition
//
// Specializes Partition for MBR-specific information
//---------------------------------------------------------------------------

public ref class MbrPartition sealed : public Partition
{
public:

	// Instance Constructor
	MbrPartition();

	//-------------------------------------------------------------------------
	// Properties

	// BootIndicator
	//
	// Indicates if this is the bootable partition
	property bool BootIndicator
	{
		bool get(void) { return (m_pInfo->Mbr.BootIndicator) ? true : false; }
		void set(bool value) { m_pInfo->Mbr.BootIndicator = (value) ? TRUE : FALSE; }
	}

	// HiddenSectors
	//
	// Gets/Sets the number of hidden sectors allocated
	property int HiddenSectors
	{
		int get(void) { return static_cast<int>(m_pInfo->Mbr.HiddenSectors); }
		void set(int value);
	}

	// PartitionType
	//
	// Gets/Sets the MBR partition type flag
	property MbrPartitionType PartitionType
	{
		MbrPartitionType get(void) { return static_cast<MbrPartitionType>(m_pInfo->Mbr.PartitionType); }
		void set(MbrPartitionType value) { m_pInfo->Mbr.PartitionType = static_cast<BYTE>(value); }
	}

	// RecognizedPartition
	//
	// Indicates if the partition type is recognized by Windows
	property bool RecognizedPartition
	{
		bool get(void) { return (m_pInfo->Mbr.RecognizedPartition) ? true : false; }
	}

internal:

	// INTERNAL CONSTRUCTORS
	MbrPartition(PPARTITION_INFORMATION_EX pInfo);
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __MBRPARTITION_H_
