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

#ifndef __VIRTUALDISKATTACHPARAMETERS_H_
#define __VIRTUALDISKATTACHPARAMETERS_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskAttachParameters
//
// Contains virtual hard disk (VHD) attach parameters
//---------------------------------------------------------------------------

public ref class VirtualDiskAttachParameters sealed
{
public:

	// Instance Constructor
	VirtualDiskAttachParameters() { Construct(); }

	//-----------------------------------------------------------------------
	// Properties

	// AutoDetach
	//
	// Flag indicating that the disk should be automatically detached when closed
	property bool AutoDetach
	{
		bool get(void) { return m_autoDetach; }
		void set(bool value) { m_autoDetach = value; }
	}

	// DoNotAssignDriveLetter
	//
	// Flag indicating that a drive letter should not be assigned during attach
	property bool DoNotAssignDriveLetter
	{
		bool get(void) { return m_noDriveLetter; }
		void set(bool value) { m_noDriveLetter = value; }
	}

	// ReadOnly
	//
	// Flag indicating if the backing store will be opened in read-only mode
	property bool ReadOnly
	{
		bool get(void) { return m_readOnly; }
		void set(bool value) { m_readOnly = value; }
	}

internal:

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// Releases strcuture allocated by ToATTACH_VIRTUAL_DISK_PARAMETERS()
	static void FreeATTACH_VIRTUAL_DISK_PARAMETERS(PATTACH_VIRTUAL_DISK_PARAMETERS pParams);

	// Gets the ATTACH_VIRTUAL_DISK_FLAG bitmask
	ATTACH_VIRTUAL_DISK_FLAG ToATTACH_VIRTUAL_DISK_FLAG(void);

	// Converts the state of this object into an unmanaged ATTACH_VIRTUAL_DISK_PARAMETERS
	ATTACH_VIRTUAL_DISK_VERSION ToATTACH_VIRTUAL_DISK_PARAMETERS(PATTACH_VIRTUAL_DISK_PARAMETERS* ppParams);

private:

	//-----------------------------------------------------------------------
	// Private Member Functions

	// Pseudo-constructor
	void Construct(void);

	//-----------------------------------------------------------------------
	// Member Variables

	bool					m_readOnly;
	bool					m_noDriveLetter;
	bool					m_autoDetach;
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKATTACHPARAMETERS_H_
