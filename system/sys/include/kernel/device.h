/*
 *  The AtheOS kernel
 *  Copyright (C) 1999 - 2001 Kurt Skauen
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

#ifndef __F_KERNEL_DEVICE_H__
#define __F_KERNEL_DEVICE_H__

#include <kernel/types.h>
#include <kernel/filesystem.h>
#include <syllable/device.h>

typedef status_t dop_open( void* pNode, uint32 nFlags, void **pCookie );
typedef status_t dop_close( void* pNode, void* pCookie );
typedef status_t dop_ioctl( void* pNode, void* pCookie, uint32 nCommand, void* pArgs, bool bFromKernel );
typedef int	 dop_read( void* pNode, void* pCookie, off_t nPosition, void* pBuffer, size_t nSize );
typedef int	 dop_write( void* pNode, void* pCookie, off_t nPosition, const void* pBuffer, size_t nSize );
typedef int	 dop_readv( void* pNode, void* pCookie, off_t nPosition, const struct iovec* psVector, size_t nCount );
typedef int	 dop_writev( void* pNode, void* pCookie, off_t nPosition, const struct iovec* psVector, size_t nCount );
typedef int	 dop_add_select_req( void* pNode, void* pCookie, SelectRequest_s* psRequest );
typedef int	 dop_rem_select_req( void* pNode, void* pCookie, SelectRequest_s* psRequest );
typedef status_t dop_mmap( void* pNode, void* pCookie, void** ppAddress, size_t nSize, flags_t nProtection, flags_t nLockMode);

/** \struct DeviceOperations_s
 * \ingroup DriverAPI
 * \brief Functions exported from device drivers
 * \par Description:
 *	A device driver export most of it functionality through this
 *	set of functions. The device driver must fill out an instance
 *	of this structure and pass a pointer to it to the
 *	create_device_node() function to export it's functionality. If
 *	the driver have more than one node inside /dev/ it can eighter
 *	use a different set of functions for each node, or it can use
 *	the same functions and differ between the nodes through the
 *	associated cookie.
 * \sa create_device_node()
 * \author	Kurt Skauen (kurt@atheos.cx)
 *****************************************************************************/

typedef struct
{
    dop_open*		open;
    dop_close*		close;
    dop_ioctl*		ioctl;
    dop_read*		read;
    dop_write*		write;
    dop_readv*		readv;
    dop_writev*		writev;
    dop_add_select_req*	add_select_req;
    dop_rem_select_req*	rem_select_req;
    dop_mmap*		mmap;
} DeviceOperations_s;

#define BUILTIN_DEVICE_ID 1	// Device ID for devices built in to the kernel.

void init_boot_device( const char* pzPath );

int create_device_node( int nDeviceID, int nDeviceHandle, const char* pzPath, const DeviceOperations_s* psOps, void* pCookie );
int delete_device_node( int nHandle );
int rename_device_node( int nHandle, const char* pzNewPath );

#endif /* __F_KERNEL_DEVICE_H__ */
