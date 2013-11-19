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

#ifndef __VIRTUALDISKSTORAGETYPE_H_
#define __VIRTUALDISKSTORAGETYPE_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskStorageType
//
// Defines the type of a virtual storage device
//---------------------------------------------------------------------------

public value class VirtualDiskStorageType sealed
{
public:

	//-----------------------------------------------------------------------
	// Overloaded Operators

	bool operator ==(VirtualDiskStorageType rhs) { return rhs.m_deviceId == this->m_deviceId; }
	bool operator !=(VirtualDiskStorageType rhs) { return rhs.m_deviceId != this->m_deviceId; }

	//-----------------------------------------------------------------------
	// Fields

	static initonly VirtualDiskStorageType Auto		= VirtualDiskStorageType(VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN);
	static initonly VirtualDiskStorageType ISO		= VirtualDiskStorageType(VIRTUAL_STORAGE_TYPE_DEVICE_ISO);
	static initonly VirtualDiskStorageType VHD		= VirtualDiskStorageType(VIRTUAL_STORAGE_TYPE_DEVICE_VHD);
	static initonly VirtualDiskStorageType VHDX		= VirtualDiskStorageType(VIRTUAL_STORAGE_TYPE_DEVICE_VHDX);

internal:

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// Converts from an unmanaged VIRTUAL_STORAGE_TYPE structure
	static VirtualDiskStorageType FromVIRTUAL_STORAGE_TYPE(PVIRTUAL_STORAGE_TYPE ptype);

	// Converts into an unmanaged VIRTUAL_STORAGE_TYPE structure
	void ToVIRTUAL_STORAGE_TYPE(PVIRTUAL_STORAGE_TYPE ptype);

private:

	// PRIVATE CONSTRUCTOR
	VirtualDiskStorageType(int deviceId) : m_deviceId(deviceId) {}

	//-----------------------------------------------------------------------
	// Member Variables
	
	initonly int		m_deviceId;
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKSTORAGETYPE_H_
