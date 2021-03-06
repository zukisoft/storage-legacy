//-----------------------------------------------------------------------------
// Copyright (c) 2014 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef __MBRPARTITIONLIST_H_
#define __MBRPARTITIONLIST_H_
#pragma once

#include "MbrPartition.h"				// Include MbrPartition declartions
#include "PartitionList.h"				// Include PartitionList declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(storage)
BEGIN_NAMESPACE(disk)

//---------------------------------------------------------------------------
// Class MbrPartitionList
//
// MBR partition management collection
//---------------------------------------------------------------------------

public ref class MbrPartitionList : public PartitionList<MbrPartition^>
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Add
	//
	// Adds a new partition to the disk
	//GptPartition^ Add(void);
	//GptPartition^ Add(__int64 length);
	//GptPartition^ Add(__int64 length, __int64 offset);
	//GptPartition^ Add(__int64 length, __int64 offset, GptPartitionType type);
	//GptPartition^ Add(__int64 length, __int64 offset, GptPartitionType type, Guid partitionId);

internal:

	// INTERNAL CONSTRUCTORS
	MbrPartitionList(Disk^ disk) : PartitionList(disk) {}

private:
	
	//-----------------------------------------------------------------------
	// Member Variables
};

//---------------------------------------------------------------------------

END_NAMESPACE(disk)
END_NAMESPACE(storage)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __MBRPARTITIONLIST_H_
