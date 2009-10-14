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

#ifndef __F_ATHEOS_PCI_H_
#define __F_ATHEOS_PCI_H_

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#include <atheos/pci_vendors.h>
#include <atheos/device.h>

status_t get_pci_info( PCI_Info_s* psInfo, int nIndex );

uint32 	 read_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize );
status_t write_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize, uint32 nValue );

status_t raw_read_pci_config( int nBusNum, int nDevFnc, int nOffset, int nSize, uint32 *pnRes );
status_t raw_write_pci_config( int nBusNum, int nDevFnc, int nOffset, int nSize, uint32 nValue );

int read_pci_header( PCI_Entry_s * psInfo, int nBusNum, int nDevNum, int nFncNum );

#ifdef __cplusplus
}
#endif

#endif	/* __F_ATHEOS_PCI_H_ */
