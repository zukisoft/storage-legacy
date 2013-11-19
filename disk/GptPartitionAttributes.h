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

#ifndef __GPTPARTITIONATTRIBUTES_H_
#define __GPTPARTITIONATTRIBUTES_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Enum GptPartitionAttributes
//
// Defines GPT partition EFI attributes

[FlagsAttribute]
public enum struct GptPartitionAttributes : unsigned __int64
{
	None					= 0,
	PlatformRequired		= GPT_ATTRIBUTE_PLATFORM_REQUIRED,
	NoDriveLetter			= GPT_BASIC_DATA_ATTRIBUTE_NO_DRIVE_LETTER,
	Hidden					= GPT_BASIC_DATA_ATTRIBUTE_HIDDEN,
	ShadowCopy				= GPT_BASIC_DATA_ATTRIBUTE_SHADOW_COPY,
	ReadOnly				= GPT_BASIC_DATA_ATTRIBUTE_READ_ONLY
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __GPTPARTITIONATTRIBUTES_H_
