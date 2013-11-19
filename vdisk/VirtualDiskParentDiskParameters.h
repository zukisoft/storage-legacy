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

#ifndef __VIRTUALDISKPARENTDISKPARAMETERS_H_
#define __VIRTUALDISKPARENTDISKPARAMETERS_H_
#pragma once

#include "VirtualDiskStorageType.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::IO;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(vdisk)

//---------------------------------------------------------------------------
// Class VirtualDiskParentDiskParameters
//
// Contains information about a parent disk when creating a new differencing
// virtual disk object
//---------------------------------------------------------------------------

public ref class VirtualDiskParentDiskParameters sealed
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// CopyMetadata
	//
	// Flag that indicates the metadata from the parent disk should be copied
	// when creating the new differencing disk
	property bool CopyMetadata
	{
		bool get(void) { return m_copyMetadata; }
		void set(bool value) { m_copyMetadata = value; }
	}

	// Path
	//
	// Gets/sets the fully qualified path to the parent disk object
	property String^ Path
	{
		String^ get(void) { return m_path; }
		void set(String^ value) 
		{ 
			if(!String::IsNullOrEmpty(value) && !System::IO::Path::IsPathRooted(value)) 
				throw gcnew ArgumentException("path must be fully qualified", "value");
			m_path = value; 
		}
	}

	// Type
	//
	// Gets/sets the virtual disk type of the parent disk object
	property VirtualDiskStorageType Type
	{
		VirtualDiskStorageType get(void) { return m_storageType; }
		void set(VirtualDiskStorageType value) { m_storageType = value; }
	}

internal:

	// INTERNAL CONSTRUCTOR
	VirtualDiskParentDiskParameters() 
	{
		m_path = String::Empty;
		m_storageType = VirtualDiskStorageType::Auto;
		m_copyMetadata = true;
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	String^						m_path;
	VirtualDiskStorageType		m_storageType;
	bool						m_copyMetadata;
};

//---------------------------------------------------------------------------

END_NAMESPACE(vdisk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __VIRTUALDISKPARENTDISKPARAMETERS_H_
