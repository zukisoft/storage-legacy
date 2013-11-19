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


#include "stdafx.h"						// Include project pre-compiled headers
#include "VirtualDiskStorageType.h"		// Include VirtualDiskStorageType declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//-----------------------------------------------------------------------------
// VirtualDiskStorageType::FromVIRTUAL_STORAGE_TYPE (internal, static)
//
// Converts a VIRTUAL_STORAGE_TYPE into one of the valid VirtualStorageType(s)
//
// Arguments:
//
//	ptype		- Pointer to a VIRTUAL_STORAGE_TYPE structure

VirtualDiskStorageType VirtualDiskStorageType::FromVIRTUAL_STORAGE_TYPE(PVIRTUAL_STORAGE_TYPE ptype)
{
	if(!ptype) return VirtualDiskStorageType::Auto;

	// Use the DEVICEID to determine a VirtualDiskStorageType to return
	switch(ptype->DeviceId) {

		case VIRTUAL_STORAGE_TYPE_DEVICE_ISO: return VirtualDiskStorageType::ISO;
		case VIRTUAL_STORAGE_TYPE_DEVICE_VHD: return VirtualDiskStorageType::VHD;
		case VIRTUAL_STORAGE_TYPE_DEVICE_VHDX: return VirtualDiskStorageType::VHDX;
	}
	
	// Anything unrecognized --> AUTO
	return VirtualDiskStorageType::Auto;
}

//-----------------------------------------------------------------------------
// VirtualDiskStorageType::ToVIRTUAL_STORAGE_TYPE (internal)
//
// Converts the value of this class into an unmanaged VIRTUAL_STORAGE_TYPE
//
// Arguments:
//
//	ptype		- Pointer to a VIRTUAL_STORAGE_TYPE structure

void VirtualDiskStorageType::ToVIRTUAL_STORAGE_TYPE(PVIRTUAL_STORAGE_TYPE ptype)
{
	if(ptype == NULL) throw gcnew ArgumentNullException("ptype");

	ptype->DeviceId = static_cast<ULONG>(m_deviceId);
	
	// Use VENDOR_UNKNOWN along with DEVICE_UNKNOWN, otherwise VENDOR_MICROSOFT
	if(m_deviceId == VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN) ptype->VendorId = VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN;
	else ptype->VendorId = VIRTUAL_STORAGE_TYPE_VENDOR_MICROSOFT;
}

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
