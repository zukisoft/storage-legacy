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
#include "VirtualDiskOpenParameters.h"	// Include VirtualDiskOpenParameters declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// VirtualDiskOpenParameters::Construct (private)
//
// Class pseudo-constructor; initializes all member variables to default values

void VirtualDiskOpenParameters::Construct(String^ path, VirtualDiskStorageType type)
{
	m_path = path;
	m_storageType = type;
	m_getInfoOnly = false;
	m_readOnly = false;
	m_noParents = false;
	m_customDiffChain = false;
	m_resiliencyGuid = Guid::Empty;
}

//---------------------------------------------------------------------------
// VirtualDiskOpenParameters::FreeOPEN_VIRTUAL_DISK_PARAMETERS (static)
//
// Releases structure created by ToOPEN_VIRTUAL_DISK_PARAMETERS
//
// Arguments:
//
//	pParams			- Parameter structure with embedded pointers

void VirtualDiskOpenParameters::FreeOPEN_VIRTUAL_DISK_PARAMETERS(POPEN_VIRTUAL_DISK_PARAMETERS pParams)
{
	// There are currently no embedded pointers to chase in this structure
	delete pParams;
}

//---------------------------------------------------------------------------
// VirtualDiskOpenParameters::ToOPEN_VIRTUAL_DISK_FLAG
//
// Converts the state of this object into an unmanaged OPEN_VIRTUAL_DISK_FLAG
//
// Arguments:
//
//	NONE

OPEN_VIRTUAL_DISK_FLAG VirtualDiskOpenParameters::ToOPEN_VIRTUAL_DISK_FLAG(void)
{
	OPEN_VIRTUAL_DISK_FLAG result = OPEN_VIRTUAL_DISK_FLAG_NONE;

	if(m_noParents) result |= OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS;
	if(m_cachedIO) result |= OPEN_VIRTUAL_DISK_FLAG_CACHED_IO;
	if(m_customDiffChain) result |= OPEN_VIRTUAL_DISK_FLAG_CUSTOM_DIFF_CHAIN;

	return result;
}

//---------------------------------------------------------------------------
// VirtualDiskOpenParameters::ToOPEN_VIRTUAL_DISK_PARAMETERS (internal)
//
// Converts the state of this object into an unmanaged OPEN_VIRTUAL_DISK_PARAMETERS
//
// Arguments:
//
//	ppParams		- Pointer to receive an unmanaged OPEN_VIRTUAL_DISK_PARAMETERS structure

OPEN_VIRTUAL_DISK_VERSION VirtualDiskOpenParameters::ToOPEN_VIRTUAL_DISK_PARAMETERS(POPEN_VIRTUAL_DISK_PARAMETERS* ppParams)
{
	POPEN_VIRTUAL_DISK_PARAMETERS		pParams;					// Structure pointer
	PinnedBytePtr						pinResiliencyGuid;			// Pinned GUID

	if(!ppParams) throw gcnew ArgumentNullException("pParams");

	*ppParams = new OPEN_VIRTUAL_DISK_PARAMETERS;
	if(!(*ppParams)) throw gcnew OutOfMemoryException();
	pParams = (*ppParams);

	// Pin the resiliency GUID structure
	array<Byte>^ resiliencyGuid = m_resiliencyGuid.ToByteArray();
	pinResiliencyGuid = &(resiliencyGuid[0]);

	// Initialize the OPEN_VIRTUAL_DISK_PARAMETERS
	ZeroMemory(pParams, sizeof(OPEN_VIRTUAL_DISK_PARAMETERS));
	pParams->Version = OPEN_VIRTUAL_DISK_VERSION_2;
	pParams->Version2.GetInfoOnly = (m_getInfoOnly) ? TRUE : FALSE;
	pParams->Version2.ReadOnly = (m_readOnly) ? TRUE : FALSE;
	memcpy(&pParams->Version2.ResiliencyGuid, pinResiliencyGuid, sizeof(_GUID));

	return pParams->Version;
}

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)
