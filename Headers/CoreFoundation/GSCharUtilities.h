/* GSCharUtilities.h
   
   Copyright (C) 2014 Free Software Foundation, Inc.
   
   Written by: Stefan Bidigaray
   Date: November, 2014
   
   This file is part of the GNUstep CoreBase Library.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

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

#ifndef __GSCHAR_H__
#define __GSCHAR_H__ 1

#include "CoreFoundation/CFBase.h"

/** \defgroup CharUtils Character Utilities
    \{
 */

/** \name Unicode Code Point Functions
    \{
 */

/** \brief Determine if character is in one of the supplementary planes.
    \param[in] c Character to test.
    \return Returns true if character is in one of the supplementary planes
	    and false if in the Basic Multilingual plane.
 */
CF_INLINE Boolean
GSCharIsInSupplementaryPlane (UTF32Char c)
{
  return c > 0xFFFF;
}

/** \brief Determine true if character is a surrogate code point.
    \param[in] c Character to test.
    \return Returns true if character is a surrogate and false, otherwise.
 */
CF_INLINE Boolean
GSCharIsSurrogate (UTF32Char c)
{
  return (c & 0xFFFFF800) == 0xD800;
}

/** \brief Determine if character is a leading surrogate code point.
    \param[in] c Character to test.
    \return Returns true if character is leading and false, otherwise.
 */
CF_INLINE Boolean
GSCharIsLeadSurrogate (UTF32Char c)
{
  return (c & 0xFFFFFC00) == 0xD800;
}

/** \brief Determine if character is a trailing surrogate code point.
    \param[in] c Character to test.
    \return Returns true if character is trailing and false, otherwise.
 */
CF_INLINE Boolean
GSCharIsTrailSurrogate (UTF32Char c)
{
  return (c & 0xFFFFFC00) == 0xDC00;
}

/** \}
 */

/** \name UTF-8 Utilities
    \{
 */

/** \brief The maximum number of UTF-8 code units required to represent
	   the highest Unicode code point.
 */
#define kGSUTF8CharMaximumLength 4

/** \brief Determine the number of code units for a UTF-8 character based on
	   the leading code unit.
    \param[in] c Leading code unit to test.
    \return The number of UTF-8 code units in this character.
 */
CF_INLINE CFIndex
GSUTF8CharCodeUnitCount (UTF8Char c)
{
  return (c < 0xF8) ? (c < 128 || c >= 0xC0) + (c >= 0xC0) + (c >= 0xE0)
    + (c >= 0xF0) : 0;
}

/** \brief Determines if the specified UTF-8 code unit is a trailing code unit.
    \param[in] c The code unit to test.
    \return Returns true if this UTF-8 code unit is a trailing code unit.
 */
CF_INLINE Boolean
GSUTF8CharIsTrailing (UTF8Char c)
{
  return (c & 0xC0) == 0x80;
}

/** \brief Determine the number of UTF-8 code units required to represent
	   the specified Unicode code point.
    \param[in] c The Unicode code point to test.
    \return The number of UTF-8 code units required.
 */
CF_INLINE CFIndex
GSUTF8CharLength (UTF32Char c)
{
  return (c <= 0x10FFFF) ? 1 + (c >= 0x80) + (c >= 0x800) + (c >= 0x10000) : 0;
}

/** \brief Append the UTF-8 Byte Order Mark to the string buffer.
    \param[in,out] d A pointer to the current position of the string buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.  The caller
		   must ensure this parameter is beyond the string buffer
		   pointed to by \b d.
    \return True if the function was successful and false, otherwise.
 */
CF_INLINE Boolean
GSUTF8CharAppendByteOrderMark (UTF8Char ** d, UTF8Char *end)
{
  UTF8Char *p;

  p = *d;
  if ((end - p) > 3)
    {
      *p++ = 0xEF;
      *p++ = 0xBB;
      *p++ = 0xBF;
      *d = p;

      return true;
    }

  return false;
}

/** \brief Determine if a UTF-8 string buffer has a Byte Order Mark.
    \param[in,out] s A pointer to the current position of the string buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.  The caller
		   must ensure this parameter is beyond the string buffer
		   pointed to by \b d.
    \return True if a Byte Order Mark is found and false, otherwise.
 */
CF_INLINE Boolean
GSUTF8CharSkipByteOrderMark (UTF8Char ** s, UTF8Char *end)
{
  UTF8Char *p;

  p = *s;
  if ((end - p) > 3)
    {
      if (*p++ == 0xEF && *p++ == 0xBB && *p++ == 0xBF)
	{
	  *s = p;
	  return true;
	}
    }

  return false;
}

/** \brief Append a character to a UTF-8 string buffer.
    \param[in,out] d A pointer to the current position of the string buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.  The caller
		   must ensure this parameter is beyond the string buffer
		   pointed to by \b d.
    \param[in] c The Unicode code point to write.
    \return True if the functions was successful, and false if there is not
	    enough space left in the string buffer or the code point is
	    invalid.
 */
CF_INLINE Boolean
GSUTF8CharAppend (UTF8Char ** d, UTF8Char * end, UTF32Char c)
{
  UTF8Char *p;

  p = *d;
  if (c < 0x80)
    {
      *p++ = c;
    }
  else if (c < 0x800 && (end - p) > 2)
    {
      *p++ = (c >> 6) | 0xC0;
      *p++ = (c & 0x3F) | 0x80;
    }
  else if (GSUCharIsSurrogate (c) || c > 0x10FFFF)
    {
      return false;
    }
  else if (c < 0x10000 && (end - p) > 3)
    {
      *p++ = (c >> 12) | 0xE0;
      *p++ = ((c >> 6) & 0x3F) | 0x80;
      *p++ = (c & 0x3F) | 0x80;
    }
  else if (c >= 0x20000 && (end - p) > 4)
    {
      *p++ = (c >> 18) | 0xF0;
      *p++ = ((c >> 12) & 0x3F) | 0x80;
      *p++ = ((c >> 6) & 0x3F) | 0x80;
      *p++ = (c & 0x3F) | 0x80;
    }

  return true;
}

/** \brief Get a Unicode code point from a UTF-8 string buffer.
    \param[in,out] s A pointer to the current position of the buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.
    \return A valid Unicode code point or a UTF-16 surrogate.
	    Will return 0 in a few cases:
	    1. The UTF-8 code unit is also a 0.
	    2. The UTF-8 code unit pointed to by \b s is not a leading code
	    unit.
	    3. The leading UTF-8 code unit does not have the correct number
	    of trailing code units.
	    4. The resulting code point is a above 0x10FFFF.
 */
CF_INLINE UTF32Char
GSUTF8CharGet (UTF8Char ** s, UTF8Char * end)
{
  return 0;
}

/** \}
 */

/** \name UTF-16 Utilities
    \{
 */

/** \brief The maximum number of UTF-16 code units required to represent the
	   highest Unicode code point.
 */
#define kGSUTF16CharMaximumLength 2

/** \brief The Byte Order Mark for UTF-16 strings.
 */
#define kGSUTF16CharByteOrderMark 0xFEFF

/** \brief The swapped Byte Order Mark for UTF-16 strings.
 */
#define kGSUTF16CharSwappedByteOrderMark 0xFFFE

/** \brief Append a character to a UTF-16 string buffer.
    \param[in,out] d A pointer to the current position of the buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.
    \param[in] c The Unicode code point to write.
    \return True if the functions was successful, and false if there is not
	    enough space left in the string buffer or the code point is
	    invalid.
 */
CF_INLINE Boolean
GSUTF16CharAppend (UTF16Char ** d, UTF16Char * end, UTF32Char c)
{
  UTF16Char *p;

  p = *d;
  if (c <= 0xFFFF && (end - p) > 1)
    {
      if (GSUCharIsSurrogate (c))
        return false;
      *p++ = c;
    }
  else if (c <= 0x10FFFF && (end - p) > 2)
    {
      *p++ = (c >> 10) + 0xD7C0;
      *p++ = (c & 0x3FF) + 0xDC00;
    }
  else
    {
      return false;
    }
  *d = p;

  return true;
}


/** \brief Get a Unicode code point from a UTF-16 string buffer.
    \param[in,out] s A pointer to the current position of the buffer.
		     This value is updated after a call to the function.
    \param[in] end The position just after the end of the buffer.
    \return A valid Unicode code point.  Will return 0 in a few cases:
	    1. The UTF-16 code unit is also a 0.
	    2. The UTF-16 code unit pointed to by \b s is not a leading code
	    unit.
	    3. The leading UTF-16 code unit does not have a trailing pair.
 */
CF_INLINE UTF32Char
GSUTF16CharGet (UTF16Char ** s, UTF16Char * end)
{
  UTF32Char c;
  UTF16Char *p;

  p = *s;
  c = *p++;
  if (GSUCharIsSurrogate (c))
    {
      if (GSUCharIsLeadSurrogate (c) && p < end && GSUCharIsTrailSurrogate (*p))
        c = (c << 10) + (*p++) - ((0xD7C0 << 10) + 0xDC00);
      else
        return 0;
    }

  *s = p;
  return c;
}

/** \}
 */

/** \name UTF-32 Utilities
    \{
 */

/** \brief The Byte Order Mark for UTF-32 strings.
 */
#define kGSUTF32CharByteOrderMark 0x0000FEFF

/** \brief The swapped Byte Order Mark for UTF-32 strings.
 */
#define kGSUTF32CharSwappedByteOrderMark 0xFFFE0000

/** \}
 */

/** \}
 */

#endif /* __GSCHAR_H__ */
