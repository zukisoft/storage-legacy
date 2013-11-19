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

#ifndef __DISKAPI_H_
#define __DISKAPI_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class DiskApi (internal)
//
// Helper class that wraps the underlying disk IOCTL calls to keep some
// clutter out of the main class library
//---------------------------------------------------------------------------

ref class DiskApi
{
public:

	// FreeDiskGeometryEx
	//
	// Releases the pointer allocated by GetDiskGeometryEx()
	static PDISK_GEOMETRY_EX FreeDiskGeometryEx(PDISK_GEOMETRY_EX pGeometry);

	// FreeDriveLayoutInformationEx
	//
	// Releases the pointer allocated by GetDriveLayoutInformationEx()
	static PDRIVE_LAYOUT_INFORMATION_EX FreeDriveLayoutInformationEx(PDRIVE_LAYOUT_INFORMATION_EX pLayout);

	// FreeGetDiskAttributes
	//
	// Releases the pointer allocated by GetDiskAttributes()
	static PGET_DISK_ATTRIBUTES FreeGetDiskAttributes(PGET_DISK_ATTRIBUTES pAttributes);

	// GetDiskAttributes
	//
	// Retrieves the GET_DISK_ATTRIBUTES data for the disk object
	static void GetDiskAttributes(HANDLE handle, PGET_DISK_ATTRIBUTES* ppAttributes);

	// GetDiskGeometryEx
	//
	// Retrieves the DISK_GEOMETRY_EX data for the disk object
	static void GetDiskGeometryEx(HANDLE handle, PDISK_GEOMETRY_EX* ppGeometry);
	static void GetDiskGeometryEx(HANDLE handle, DWORD* pcbGeometry, PDISK_GEOMETRY_EX* ppGeometry);

	// GetDriveLayoutInformationEx
	//
	// Retrieves the DRIVE_LAYOUT_INFORMATION_EX data for the disk object
	static void GetDriveLayoutInformationEx(HANDLE handle, PDRIVE_LAYOUT_INFORMATION_EX* ppLayout);
	static void GetDriveLayoutInformationEx(HANDLE handle, DWORD* pcbLayout, PDRIVE_LAYOUT_INFORMATION_EX* ppLayout);

	// IsWritable
	//
	// Determines if the disk object is writable
	static bool IsWritable(HANDLE handle);

	// SetDiskAttributes
	//
	// Applies SET_DISK_ATTRIBUTES information for the disk
	static void SetDiskAttributes(HANDLE handle, PSET_DISK_ATTRIBUTES pAttributes);

	// SetDriveLayoutInformationEx
	//
	// Applies the DRIVE_LAYOUT_INFORMATION_EX data for the disk object
	static void SetDriveLayoutInformationEx(HANDLE handle, DWORD cbLayout, PDRIVE_LAYOUT_INFORMATION_EX pLayout);

	// SetDriveLayoutInformationGpt
	//
	// Sets the DRIVE_LAYOUT_INFORMATION_GPT for a disk object
	static void SetDriveLayoutInformationGpt(HANDLE handle, PDRIVE_LAYOUT_INFORMATION_GPT pInfo);
	
	// SetDriveLayoutInformationMbr
	//
	// Sets the DRIVE_LAYOUT_INFORMATION_MBR for a disk object
	static void SetDriveLayoutInformationMbr(HANDLE handle, PDRIVE_LAYOUT_INFORMATION_MBR pInfo);

	// UpdateProperties
	//
	// Synchronizes the system view of the disk with it's updated information
	static void UpdateProperties(HANDLE handle);

	// TryUpdateProperties
	//
	// Invokes UpdateProperties without throwing an exception on failure
	static bool TryUpdateProperties(HANDLE handle);
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __DISKAPI_H_
