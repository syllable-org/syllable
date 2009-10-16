/*
 *  The AtheOS kernel
 *  Copyright (C) 1999 - 2000 Kurt Skauen
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of version 2 of the GNU Library
 *  General Public License as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __ATHEOS_KERNEL_H__
#define __ATHEOS_KERNEL_H__

#include <kernel/v86.h>
#include <kernel/kdebug.h>
#include <kernel/areas.h>
#include <kernel/stdlib.h>
#include <kernel/schedule.h>
#include <kernel/isa_io.h>

#ifdef __cplusplus
extern "C" {
#endif

/* this struct defines the way the registers are stored on the
   stack during a system call. */

typedef struct
{
    long 	ebx;
    long 	ecx;
    long 	edx;
    long 	esi;
    long	edi;
    long 	ebp;
    long 	eax;
    uint16	ds, __dsu;
    uint16	es, __esu;
    uint16	fs, __fsu;
    uint16	gs, __gsu;
    long 	orig_eax;
    long 	eip;
    uint16	cs, __csu;
    long 	eflags;
    long 	oldesp;
    uint16	oldss, __ssu;
} SysCallRegs_s;

void print_registers( SysCallRegs_s* psRegs );

// Sendt to the app server when a thread dies

typedef	struct
{
    thread_id	hThread;
} DR_ThreadDied_s;


static inline int   isa_readb( int nPort )		{ return inb( nPort ); }
static inline int   isa_readw( int nPort )		{ return inw( nPort ); }
static inline int   isa_readl( int nPort )		{ return inl( nPort ); }
static inline void  isa_writeb( int nPort, int nValue )	{ outb( nValue, nPort ); }
static inline void  isa_writew( int nPort, int nValue )	{ outw( nValue, nPort ); }
static inline void  isa_writel( int nPort, int nValue )	{ outl( nValue, nPort ); }


void	SwitchCont( int nDesc );

status_t snooze( bigtime_t nTimeout );

int	exit_from_sys_call( void );

int	realint( int num, struct RMREGS *rm );

#ifdef __KERNEL__
status_t get_system_info( system_info* psInfo, int nVersion );
#endif

int	 set_app_server_port( port_id hPort );
port_id	 get_app_server_port( void );
port_id	 sys_get_app_server_port( void );

int	sys_get_system_path( char* pzBuffer, int nBufLen );
int	get_system_path( char* pzBuffer, int nBufLen );

/* XXXKV: This is too big a change to make straight away so include the definitions for now */
#include <kernel/malloc.h>

int	reboot( void );
void    hard_reset( void );
int apm_poweroff( void );

int	sys_exit( int nCode );
int	exit_thread( int nCode );
int	do_exit( int nCode );

thread_id	create_init_proc( const char* pzName );
void	init_kmalloc( void );
void	make_kernel_image( void );

int	sys_killpg( const pid_t nGrp, const int nSigNum );
int	sys_kill_proc( proc_id hProcess, int nSigNum );

int	killpg( pid_t nGrp, int nSigNum );
int	kill_proc( proc_id hProcess, int nSigNum );

int 	initialize_fs( const char* pzDevPath, const char* pzFsType, const char* pzVolName, void* pArgs, int nArgLen 
);
#ifdef __KERNEL__
int 	mount( const char* pzDevName, const char* pzDirName,
	   const char* pzFSName, int nFlags, const void* pData );
int	sys_unmount( const char* pzPath, bool bForce );
#endif

int	sys_initialize_fs( const char* pzDevPath, const char* pzFsType, const char* pzVolName, void* pArgs, int 
nArgLen );

int	sys_mount( const char* pzDevName, const char* pzDirName,
		   const char* pzFSName, int nFlags, const void* pData );
int	unmount( const char* pzPath, bool bForce );


#ifdef __KERNEL__

bool get_str_arg( char* pzValue, const char* pzName, const char* pzArg, int nArgLen );
bool get_num_arg( uint32* pnValue, const char* pzName, const char* pzArg, int nArgLen );
bool get_bool_arg( bool* pnValue, const char* pzName, const char* pzArg, int nArgLen );

#endif /* __KERNEL__ */


#ifdef __cplusplus
}
#endif

#endif	/* __ATHEOS_KERNEL_H__	*/


