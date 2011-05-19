/*
** SCCS ID:	@(#)ulib.h	1.1	03/31/11
**
** File:	ulib.h
**
** Author:	4003-506 class of 20103
**
** Contributor:
**
** Description:	User library routine definitions
*/

#ifndef _ULIB_H
#define _ULIB_H

/*
** General (C and/or assembly) definitions
*/

// termination status values

#define	X_SUCCESS	0
#define	X_FAILURE	1

#ifndef __ASM__20103__

#include <types.h>
#include "process.h"

/*
** Types
*/

typedef struct info {
	pid_t pid;		// PID of desired/located process
	status_t status;	// term status of located process
} info_t;

/*
** Prototypes
*/

/*
** exit - terminate the current process and clean up after it
**
** usage:       exit( status );
*/

void exit( int status );

/*
** sleep - put the current process to sleep for the specified number
**	   of clock ticks
**
** usage:       n = sleep( ticks );
**
** returns the actual number of ticks the process slept for
*/

uint_t sleep( uint_t ticks );

/*
** fork - create a new process at a specific priority
**
** usage:       fork( &pid );
**
** returns:
**      -1 if the creation failed
**      0 in the child
**      else, the PID of the new child
*/

int fork( pid_t* pid );

/*
** exec - replace a process with a different program running at a
**	  specific priority level
**
** usage:       exec( prio, address );
*/

void exec( int prio, void (*entry)(void) );

/*
** wait - block until a child process exits
**
** usage:       wait( status_structure )
**
** returns the exit status and PID of any (or a specified) child
** in the parameter
*/

void wait( info_t *ptr );

/*
** SIO system calls are based on a simple interrupt-driven SIO
** model taken from SP1
*/

/*
** readc - read one character from the SIO
**
** usage:       ch = readc();
**
** returns the next input character
*/

int readc( void );

/*
** writec - write one character to the SIO
**
** usage:       status = writec( ch );
**
** returns the status of the write
*/

int writec( char ch );

/*
** reads - read a string from the SIO
**
** usage:       n = reads( buffer, size );
**
** returns a count of the number of bytes read into the buffer
*/

int reads( char *buf, int length );

/*
** writes - write a string to the SIO
**
** usage:       status = writes( buffer, size );
**
** returns the status of the write
*/

int writes( char *buf, int num );

/*
** kill - terminate the specified process
**
** usage:	status = kill( pid );
**
** returns the status of the kill operation
*/

int kill( int pid );

/*
** getpid - retrieve pid of the current process
**
** usage:       getpid(&pid);
**
** returns the current process' id field of the pid stuct
*/

int getpid(pid_t* p);

/*
** getppid - retrieve parent pid of the current process
**
** usage:       pid_t pid;
**              getppid(&pid);
**              
**
** returns id field of the pid struct of the parent of the current process
*/

int getppid(pid_t* p);

/*
** getprio - retrieve priority of the current process
**
** usage:       prio = getprio();
**
** returns priority of the current process
*/

int getprio( void );

/*
** gettime - retrieve the current system time
**
** usage:       n = gettime();
**
** returns the current system time
*/

time_t gettime( void );

/*
** setprio - change priority of the current process
**
** usage:       prio = setprio( prio );
**
** returns old priority of the current process
*/

int setprio( int prio );

/*
** settime - set the system time
**
** usage:       time = settime( time );
**
** returns old system time
*/

time_t settime( time_t time );


/*
** yield - Gives up the CPU and dispatches a different process
**
**	usage:	yield();
**
**	returns nothing at all
**/
void yield( void );

/*
** getscreen - get the process' screen handle
**
** usage:       handle_t h = getscreen();
**
** returns current screen handle of the process
*/

handle_t getscreen( void );

/*
** setscreen - get the process' screen handle
**
** usage:       handle_t old = setscreen(new);
**
** returns old screen handle of the process
*/

handle_t setscreen( handle_t sh );

/*
** switchscreen - switch the active screen to the given screen handle
**
** usage:       handle_t old = switchscreen(new);
**
** returns screen handle of the old screen
*/

handle_t switchscreen( handle_t sh );

/*
** openscreen - opens a new screen handle
** usage:       handle_t new = openscreen();
**
** returns a newly allocated screen handle or an error status
*/

handle_t openscreen( void );

/*
** closescreen - closes an open screen handle
** usage:       status_t s = closescreen( handle );
**
** returns an error if the given screen was not open
*/

status_t closescreen( handle_t sh );

/*
** bogus - a bogus system call, for testing our syscall ISR
**
** usage:	bogus();
*/

void bogus( void );

/*
** prt_status - print a status value to the console
**
** the 'msg' argument should contain a %s where
** the desired status value should be printed
**
** this is identical to _kprt_status(), but is here so that user
** routines which invoke it won't use the same version as the
** kernel uses, which will simplify life for people implementing
** full VM.
*/

void prt_status( char *msg, status_t stat );

/*
** _get_ebp - return current contents of EBP at the time of the call
**
** Primarily used only by _kpanic
*/

uint32_t get_ebp( void );

#endif

#endif
