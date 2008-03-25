/*
	FreeRTOS.org V4.8.0 - Copyright (C) 2003-2008 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS.org is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS.org; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS.org, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	***************************************************************************
	*																		  *
	* SAVE TIME AND MONEY!  Why not get us to quote to get FreeRTOS.org		  *
	* running on your hardware - or even write all or part of your application*
	* for you?  See http://www.OpenRTOS.com for details.					  *
	*																		  *
	***************************************************************************
	***************************************************************************

	Please ensure to read the configuration and relevant port sections of the
	online documentation.

	http://www.FreeRTOS.org - Documentation, latest information, license and 
	contact details.

	http://www.SafeRTOS.com - A version that is certified for use in safety 
	critical systems.

	http://www.OpenRTOS.com - Commercial support, development, porting, 
	licensing and training services.
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo program include files. */
#include "fileio.h"

void vDisplayMessage( const portCHAR * const pcMessageToPrint )
{
	#ifdef USE_STDIO
		taskENTER_CRITICAL();
			printf( "%s", pcMessageToPrint );
			fflush( stdout );
		taskEXIT_CRITICAL();
	#else
		/* Stop warnings. */
		( void ) pcMessageToPrint;
	#endif
}
/*-----------------------------------------------------------*/

void vWriteMessageToDisk( const portCHAR * const pcMessage )
{
#ifdef USE_STDIO
const portCHAR * const pcFileName = "c:\\RTOSlog.txt";
const portCHAR * const pcSeparator = "\r\n-----------------------\r\n";
FILE *pf;

	taskENTER_CRITICAL();
	{	
		pf = fopen( pcFileName, "a" );
		if( pf != NULL )
		{
			fwrite( pcMessage, strlen( pcMessage ), ( unsigned portSHORT ) 1, pf );
			fwrite( pcSeparator, strlen( pcSeparator ), ( unsigned portSHORT ) 1, pf );
			fclose( pf );
		}
	}
	taskEXIT_CRITICAL();
#else
	/* Stop warnings. */
	( void ) pcMessage;
#endif /*USE_STDIO*/
}
/*-----------------------------------------------------------*/

void vWriteBufferToDisk( const portCHAR * const pcBuffer, unsigned portLONG ulBufferLength )
{
#ifdef USE_STDIO
const portCHAR * const pcFileName = "c:\\trace.bin";
FILE *pf;

	taskENTER_CRITICAL();
	{
		pf = fopen( pcFileName, "wb" );
		if( pf )
		{
			fwrite( pcBuffer, ( size_t ) ulBufferLength, ( unsigned portSHORT ) 1, pf );
			fclose( pf );
		}
	}
	taskEXIT_CRITICAL();
#else
	/* Stop warnings. */
	( void ) pcBuffer;
    ( void ) ulBufferLength;
#endif /*USE_STDIO*/
}


