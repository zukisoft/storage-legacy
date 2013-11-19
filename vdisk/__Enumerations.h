//---------------------------------------------------------------------------
// ZukiSoft Virtual Disk Functions
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

#ifndef __ENUMERATIONS_H_
#define __ENUMERATIONS_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Enum AttachFlags
//
// Virtual Disk Attach Request Flags

public enum struct AttachFlags
{
	None						= ATTACH_VIRTUAL_DISK_FLAG_NONE,
	ReadOnly					= ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY,
	NoDriveLetter				= ATTACH_VIRTUAL_DISK_FLAG_NO_DRIVE_LETTER,
	PermanentLifetime			= ATTACH_VIRTUAL_DISK_FLAG_PERMANENT_LIFETIME,
	NoLocalHost					= ATTACH_VIRTUAL_DISK_FLAG_NO_LOCAL_HOST
};

//---------------------------------------------------------------------------
// Enum DependentDiskFlags
//
// Contains virtual hard disk (VHD) dependency information flags

public enum struct DependentDiskFlags
{
	None						= DEPENDENT_DISK_FLAG_NONE,
	MultipleBackingFiles		= DEPENDENT_DISK_FLAG_MULT_BACKING_FILES,
	FullyAllocated				= DEPENDENT_DISK_FLAG_FULLY_ALLOCATED,
	ReadOnly					= DEPENDENT_DISK_FLAG_READ_ONLY,
	Remote						= DEPENDENT_DISK_FLAG_REMOTE,
	SystemVolume				= DEPENDENT_DISK_FLAG_SYSTEM_VOLUME,
	SystemVolumeParent			= DEPENDENT_DISK_FLAG_SYSTEM_VOLUME_PARENT,
	Removable					= DEPENDENT_DISK_FLAG_REMOVABLE,
	NoDriveLetter				= DEPENDENT_DISK_FLAG_NO_DRIVE_LETTER,
	Parent						= DEPENDENT_DISK_FLAG_PARENT,
	NoHostDisk					= DEPENDENT_DISK_FLAG_NO_HOST_DISK,
	PermanentLifetime			= DEPENDENT_DISK_FLAG_PERMANENT_LIFETIME
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __ENUMERATIONS_H_
