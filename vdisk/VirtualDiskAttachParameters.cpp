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

#include "stdafx.h"							// Include project pre-compiled headers
#include "VirtualDiskAttachParameters.h"	// Include VirtualDiskAttachParameters

#pragma warning(push, 4)					// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// VirtualDiskAttachParameters::Construct (private)
//
// Class pseudo-constructor; initializes all member variables to default values

void VirtualDiskAttachParameters::Construct(void)
{
	m_readOnly = false;
	m_noDriveLetter = false;
	m_autoDetach = true;
}

//---------------------------------------------------------------------------
// VirtualDiskAttachParameters::FreeATTACH_VIRTUAL_DISK_PARAMETERS (static)
//
// Releases structure created by ToOPEN_VIRTUAL_DISK_PARAMETERS
//
// Arguments:
//
//	pParams			- Parameter structure with embedded pointers

void VirtualDiskAttachParameters::FreeATTACH_VIRTUAL_DISK_PARAMETERS(PATTACH_VIRTUAL_DISK_PARAMETERS pParams)
{
	// There are currently no embedded pointers to chase in this structure
	delete pParams;
}

//---------------------------------------------------------------------------
// VirtualDiskAttachParameters::ToATTACH_VIRTUAL_DISK_FLAG
//
// Converts the state of this object into an unmanaged ATTACH_VIRTUAL_DISK_FLAG
//
// Arguments:
//
//	NONE

ATTACH_VIRTUAL_DISK_FLAG VirtualDiskAttachParameters::ToATTACH_VIRTUAL_DISK_FLAG(void)
{
	ATTACH_VIRTUAL_DISK_FLAG result = ATTACH_VIRTUAL_DISK_FLAG_NONE;

	if(m_readOnly) result |= ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY;
	if(m_noDriveLetter) result |= ATTACH_VIRTUAL_DISK_FLAG_NO_DRIVE_LETTER;
	if(!m_autoDetach) result |= ATTACH_VIRTUAL_DISK_FLAG_PERMANENT_LIFETIME;

	return result;
}

//---------------------------------------------------------------------------
// VirtualDiskAttachParameters::ToATTACH_VIRTUAL_DISK_PARAMETERS (internal)
//
// Converts the state of this object into an unmanaged ATTACH_VIRTUAL_DISK_PARAMETERS
//
// Arguments:
//
//	ppParams		- Pointer to receive an unmanaged OPEN_VIRTUAL_DISK_PARAMETERS structure

ATTACH_VIRTUAL_DISK_VERSION VirtualDiskAttachParameters::ToATTACH_VIRTUAL_DISK_PARAMETERS(PATTACH_VIRTUAL_DISK_PARAMETERS* ppParams)
{
	PATTACH_VIRTUAL_DISK_PARAMETERS		pParams;					// Structure pointer

	if(!ppParams) throw gcnew ArgumentNullException("pParams");

	*ppParams = new ATTACH_VIRTUAL_DISK_PARAMETERS;
	if(!(*ppParams)) throw gcnew OutOfMemoryException();
	pParams = (*ppParams);

	// Initialize the ATTACH_VIRTUAL_DISK_PARAMETERS
	ZeroMemory(pParams, sizeof(ATTACH_VIRTUAL_DISK_PARAMETERS));
	pParams->Version = ATTACH_VIRTUAL_DISK_VERSION_1;

	// There are currently no fields to set in ATTACH_VIRTUAL_DISK_PARAMETERS

	return pParams->Version;
}

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
