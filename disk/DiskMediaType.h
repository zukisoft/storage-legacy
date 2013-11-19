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

#ifndef __DISKMEDIATYPE_H_
#define __DISKMEDIATYPE_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Enum DiskMediaType
//
// Managed version of MEDIA_TYPE enumeration; defines the disk media type

public enum struct DiskMediaType
{
	Unknown         = 0x00,
	F5_1Pt2_512     = 0x01,
	F3_1Pt44_512    = 0x02,
	F3_2Pt88_512    = 0x03,
	F3_20Pt8_512    = 0x04,
	F3_720_512      = 0x05,
	F5_360_512      = 0x06,
	F5_320_512      = 0x07,
	F5_320_1024     = 0x08,
	F5_180_512      = 0x09,
	F5_160_512      = 0x0a,
	RemovableMedia  = 0x0b,
	FixedMedia      = 0x0c,
	F3_120M_512     = 0x0d,
	F3_640_512      = 0x0e,
	F5_640_512      = 0x0f,
	F5_720_512      = 0x10,
	F3_1Pt2_512     = 0x11,
	F3_1Pt23_1024   = 0x12,
	F5_1Pt23_1024   = 0x13,
	F3_128Mb_512    = 0x14,
	F3_230Mb_512    = 0x15,
	F8_256_128      = 0x16,
	F3_200Mb_512    = 0x17,
	F3_240M_512     = 0x18,
	F3_32M_512      = 0x19
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __DISKMEDIATYPE_H_
