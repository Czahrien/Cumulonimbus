/*
** SCCS ID:	@(#)syscall.h	1.1	03/31/11
**
** File:	syscall.h
**
** Author:	4003-506 class of 20103
**
** Contributor:
**
** Description:	System call information
*/

#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include "headers.h"
#include <types.h>
#include <status.h>

/*
** General (C and/or assembly) definitions
*/

#include <x86arch.h>

// system call codes

#define	SYS_exit	0
#define	SYS_fork	1
#define	SYS_exec	2
#define	SYS_wait	3
#define	SYS_kill	4
#define	SYS_sleep	5
#define	SYS_readc	6
#define	SYS_reads	7
#define	SYS_writec	8
#define	SYS_writes	9
#define	SYS_getpid	10
#define	SYS_getppid	11
#define	SYS_getprio	12
#define	SYS_gettime	13
#define	SYS_setprio	14
#define	SYS_settime	15

// screen system calls
#define SYS_setscreen       16
#define SYS_getscreen       17
#define SYS_switchscreen    18
#define SYS_openscreen      19
#define SYS_closescreen      20

// number of "real" system calls

#define	N_SYSCALLS	256

// dummy system call code to test the syscall ISR

#define	SYS_bogus	0xbadc0de

// syscall interrupt vector number

#define	INT_VEC_SYSCALL	0x80

// default contents of the EFLAGS register

#define	DEFAULT_EFLAGS	(EFLAGS_MB1 | EFLAGS_IF)

#ifndef __ASM__20103__

// system call prototype

typedef void(*syscall_t)(context_t *);

/*
** Start of C-only definitions
*/

/*
** Globals
*/

/*
** Prototypes
*/

/*
** _isr_syscall()
**
** system call ISR
*/

void _isr_syscall( int vector, int code );

/*
** _syscall_init()
**
** initializes all syscall-related data structures
*/

status_t _syscall_init( void );

status_t _syscall_install(syscall_t func, uint8_t num);

status_t _syscall_clear(uint8_t num);

#endif

#endif
