/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * @OSF_FREE_COPYRIGHT@
 * 
 */

#include <mach/mach.h>
#include <mach/mach_init.h>
#include <stdio.h>
#include <stdarg.h>

int (*vprintf_stderr_func)(const char *format, va_list ap);


/* This function allows the writing of a mach error message to an
 * application-controllable output method, the default being to
 * use printf if no other method is specified by the application.
 *
 * To override, set the global (static) function pointer vprintf_stderr to
 * a function which takes the same parameters as vprintf.
 */

int fprintf_stderr(const char *format, ...)
{
        va_list args;
	int retval;

	va_start(args, format);
	if (vprintf_stderr_func == NULL)
		retval = vprintf(format, args);
	else
		retval = (*vprintf_stderr_func)(format, args);
	va_end(args);

	return retval;
}
