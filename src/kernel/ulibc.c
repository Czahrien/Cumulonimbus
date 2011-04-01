/*
** SCCS ID:	@(#)ulibc.c	1.1	03/31/11
**
** File:	ulibc.c
**
** Author:	4003-506 class of 20103
**
** Contributor:
**
** Description:	C implementations of some user-level library routines
*/

#define	__KERNEL__20103__

#include "headers.h"

/*
** prt_status - print a status value to the console
**
** the 'msg' argument should contain a %s where
** the desired status value should be printed
**
** this is identical to prt_status(), but is here so that user
** routines which invoke it won't use the same version as the 
** kernel uses, which will simplify life for people implementing
** full VM.
*/

void prt_status( char *msg, status_t stat ) {
	char *str;

	if( msg == NULL ) {
		return;
	}

	switch( stat ) {

		case E_SUCCESS:
			str = "E_SUCCESS";
			break;

		case E_BAD_PARAM:
			str = "E_BAD_PARAM";
			break;

		case E_NO_QNODES:
			str = "E_NO_QNODES";
			break;

		case E_EMPTY:
			str = "E_EMPTY";
			break;

		case E_NOT_FOUND:
			str = "E_NOT_FOUND";
			break;

		default:
			c_printf( msg, "E_????" );
			c_printf( "Status code %d\n", stat );
			return;
	
	}

	c_printf( msg, str );

}
