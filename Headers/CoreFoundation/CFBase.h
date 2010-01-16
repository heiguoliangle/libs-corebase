/* CFBase.h
   
   Copyright (C) 2010 Free Software Foundation, Inc.
   
   Written by: Stefan Bidigaray
   Date: January, 2010
   
   This file is part of CoreBase.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; see the file COPYING.LIB.
   If not, see <http://www.gnu.org/licenses/> or write to the 
   Free Software Foundation, 51 Franklin Street, Fifth Floor, 
   Boston, MA 02110-1301, USA.
*/ 


#ifndef __COREFOUNDATION_CFBASE_H__
#define __COREFOUNDATION_CFBASE_H__

#include <Foundation/Foundation.h>

#include <stdint.h>

#include <GNUstepBase/GSVersionMacros.h>

/* FIXME: NSLocale is not available */
typedef void * CFLocaleRef;

//
// CoreFoundation types
//
/* These defines are in Apple's CFBase.h */
typedef uint8_t  Boolean;
typedef uint8_t  UInt8;
typedef int8_t   SInt8;
typedef uint16_t UInt16;
typedef int16_t  SInt16;
typedef uint32_t UInt32;
typedef int32_t  SInt32;
typedef uint64_t UInt64;
typedef int64_t  SInt64;
typedef SInt32   OSStatus;

typedef float            Float32;
typedef double           Float64;
typedef uint16_t         UniChar;
typedef uint8_t*         StringPtr;
typedef const StringPtr* ConstStringPtr;
typedef uint8_t          Str255[256];
typedef const Str255*    ConstStr255Param;
typedef SInt16           OSErr;
typedef SInt16           RegionCode;
typedef SInt16           LangCode;



#ifndef true
# define true	1
#endif
#ifndef false
# define false	0
#endif

//
// CFType types
//
typedef unsigned long CFHashCode;
typedef unsigned long CFTypeID;
typedef void* CFTypeRef;

//
// Base Utilities
//
typedef signed long CFIndex;
typedef UInt32 CFOptionFlags;
typedef NSRange CFRange;

/* Returned by comparison functions */
typedef CFIndex CFComparisonResult;
enum
{
    kCFCompareLessThan = -1,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1
};

/* Return when a value is not found */
enum
{
  kCFNotFound = -1
};

/* Definition for standard comparison function callback. */
typedef CFComparisonResult (*CFComparatorFunction)(const void *val1, const void *val2, void *context);

/* CoreFoundation version numbers */
GS_EXPORT double kCFCoreFoundationVersionNumber;
#define kCFCoreFoundationVersionNumber10_0    196.40
#define kCFCoreFoundationVersionNumber10_0_3  196.50
#define kCFCoreFoundationVersionNumber10_1    226.00
#define kCFCoreFoundationVersionNumber10_1_1  226.00
#define kCFCoreFoundationVersionNumber10_1_2  227.20
#define kCFCoreFoundationVersionNumber10_1_3  227.20
#define kCFCoreFoundationVersionNumber10_1_4  227.30
#define kCFCoreFoundationVersionNumber10_2    263.00
#define kCFCoreFoundationVersionNumber10_2_1	263.10
#define kCFCoreFoundationVersionNumber10_2_2  263.10
#define kCFCoreFoundationVersionNumber10_2_3  263.30
#define kCFCoreFoundationVersionNumber10_2_4  263.30
#define kCFCoreFoundationVersionNumber10_2_5  263.50
#define kCFCoreFoundationVersionNumber10_2_6  263.50
#define kCFCoreFoundationVersionNumber10_2_7  263.50
#define kCFCoreFoundationVersionNumber10_2_8  263.50
#define kCFCoreFoundationVersionNumber10_3    299.00
#define kCFCoreFoundationVersionNumber10_3_1  299.00
#define kCFCoreFoundationVersionNumber10_3_2  299.00
#define kCFCoreFoundationVersionNumber10_3_3  299.30
#define kCFCoreFoundationVersionNumber10_3_4  299.31
#define kCFCoreFoundationVersionNumber10_3_5  299.31
#define kCFCoreFoundationVersionNumber10_3_6  299.32
#define kCFCoreFoundationVersionNumber10_3_7  299.33
#define kCFCoreFoundationVersionNumber10_3_8  299.33
#define kCFCoreFoundationVersionNumber10_3_9  299.35
#define kCFCoreFoundationVersionNumber10_4    368.00
#define kCFCoreFoundationVersionNumber10_4_1  368.10
#define kCFCoreFoundationVersionNumber10_4_2  368.11
#define kCFCoreFoundationVersionNumber10_4_3  368.18
#define kCFCoreFoundationVersionNumber10_4_4_Intel   368.26
#define kCFCoreFoundationVersionNumber10_4_4_PowerPC 368.25
#define kCFCoreFoundationVersionNumber10_4_5_Intel   368.26
#define kCFCoreFoundationVersionNumber10_4_5_PowerPC 368.25
#define kCFCoreFoundationVersionNumber10_4_6_Intel   368.26
#define kCFCoreFoundationVersionNumber10_4_6_PowerPC 368.25
#define kCFCoreFoundationVersionNumber10_4_7  368.27
#define kCFCoreFoundationVersionNumber10_4_8  368.27
#define kCFCoreFoundationVersionNumber10_4_9  368.28
#define kCFCoreFoundationVersionNumber10_4_10 368.28
#define kCFCoreFoundationVersionNumber10_4_11 368.31
#define kCFCoreFoundationVersionNumber10_5    476.00
#define kCFCoreFoundationVersionNumber10_5_1  476.00
#define kCFCoreFoundationVersionNumber10_5_2  476.10
#define kCFCoreFoundationVersionNumber10_5_3  476.13
#define kCFCoreFoundationVersionNumber10_5_4  476.14
#define kCFCoreFoundationVersionNumber10_5_5  476.15
#define kCFCoreFoundationVersionNumber10_5_6  476.17

/* Creates new range. */
#define CFRangeMake(loc, len) NSMakeRange(loc, len)



//
// CFString
//
typedef NSString * CFStringRef;
typedef NSMutableString * CFMutableStringRef;

//
// CFAllocator
//
typedef struct _NSZone *CFAllocatorRef;

typedef void*       (*CFAllocatorAllocateCallBack)(CFIndex allocSize, CFOptionFlags hint, void *info);
typedef void        (*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef void*       (*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize, CFOptionFlags hint, void *info);
typedef CFIndex     (*CFAllocatorPreferredSizeCallBack)(CFIndex size, CFOptionFlags hint, void *info);

typedef const void* (*CFAllocatorRetainCallBack)(const void *info);
typedef void        (*CFAllocatorReleaseCallBack)(const void *info);

typedef CFStringRef	(*CFAllocatorCopyDescriptionCallBack)(const void *info);



typedef struct _CFAllocatorContext CFAllocatorContext;
struct _CFAllocatorContext
{
  CFIndex version;
  void    *info;
  CFAllocatorRetainCallBack          retain;
  CFAllocatorReleaseCallBack         release;        
  CFAllocatorCopyDescriptionCallBack copyDescription;
  CFAllocatorAllocateCallBack        allocate;
  CFAllocatorReallocateCallBack      reallocate;
  CFAllocatorDeallocateCallBack	     deallocate;
  CFAllocatorPreferredSizeCallBack   preferredSize;
};

GS_EXPORT const CFAllocatorRef kCFAllocatorDefault;
GS_EXPORT const CFAllocatorRef kCFAllocatorSystemDefault;
GS_EXPORT const CFAllocatorRef kCFAllocatorMalloc;
#if 0 // FIXME: OS_API_VERSION(MAC_OS_X_VERSION_10_4, GS_API_LATEST)
const CFAllocatorRef kCFAllocatorMallocZone
#endif
GS_EXPORT const CFAllocatorRef kCFAllocatorNull;
GS_EXPORT const CFAllocatorRef kCFAllocatorUseContext;

CFAllocatorRef
CFAllocatorCreate (CFAllocatorRef allocator, CFAllocatorContext *context);

void *
CFAllocatorAllocate (CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

void
CFAllocatorDeallocate (CFAllocatorRef allocator, void *ptr);

CFIndex
CFAllocatorGetPreferredSizeForSize (CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

void *
CFAllocatorReallocate (CFAllocatorRef allocator, void *ptr, CFIndex newsize, CFOptionFlags hint);

CFAllocatorRef
CFAllocatorGetDefault (void);

void
CFAllocatorSetDefault (CFAllocatorRef allocator);

void
CFAllocatorGetContext (CFAllocatorRef allocator, CFAllocatorContext *context);

CFTypeID
CFAllocatorGetTypeID (void);



//
// CFType Functions
//
/* These function will be implemented in CFRuntime.c since they 
   require runtime support. */
GS_EXPORT CFStringRef
CFCopyDescription (CFTypeRef cf);

GS_EXPORT CFStringRef
CFCopyTypeIDDescription (CFTypeID typeID);

GS_EXPORT Boolean
CFEqual (CFTypeRef cf1, CFTypeRef cf2);

GS_EXPORT CFAllocatorRef
CFGetAllocator (CFTypeRef cf);

GS_EXPORT CFIndex
CFGetRetainCount (CFTypeRef cf);

GS_EXPORT CFTypeID
CFGetTypeID (CFTypeRef cf);

GS_EXPORT CFHashCode
CFHash (CFTypeRef cf);

#if 0 // FIXME: OS_API_VERSION(MAC_OS_X_VERSION_10_4, GS_API_LATEST)
GS_EXPORT CFTypeRef
CFMakeCollectable (CFTypeRef cf);
#endif

GS_EXPORT void
CFRelease (CFTypeRef cf);

GS_EXPORT CFTypeRef
CFRetain (CFTypeRef cf);



//
// CFNull
//
#if OS_API_VERSION(MAC_OS_X_VERSION_10_2, GS_API_LATEST)
typedef NSNull *CFNullRef;

GS_EXPORT CFNullRef kCFNull;

GS_EXPORT CFTypeID
CFNullGetTypeID (void);
#endif

#endif /* __COREFOUNDATION_CFBASE_H__ */