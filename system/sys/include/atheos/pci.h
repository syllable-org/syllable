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

#include <atheos/types.h>

typedef struct
{
	int		nBus;
	int		nDevice;
	int		nFunction;
	
	uint16	nVendorID;
	uint16	nDeviceID;
	uint8	nRevisionID;
	uint8 	nClassApi;
	uint8	nClassBase;
	uint8	nClassSub;
	uint8	nCacheLineSize;
	uint8	nHeaderType;

	union
	{
		struct
		{
			uint32	nBase0;
			uint32	nBase1;
			uint32	nBase2;
			uint32	nBase3;
			uint32	nBase4;
			uint32	nBase5;
			uint8	nInterruptLine;
			uint8	nInterruptPin;
			uint8	nMinDMATime;
			uint8	nMaxDMALatency;
		} h0;
	} u;
	int		nHandle;
} PCI_Info_s;

status_t get_pci_info( PCI_Info_s* psInfo, int nIndex );

uint32 read_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize );
status_t write_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize, uint32 nValue );

#ifdef __cplusplus
}
#endif

#endif	/* __F_ATHEOS_PCI_H_ */
