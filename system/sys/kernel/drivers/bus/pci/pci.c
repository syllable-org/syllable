
/*
 *  The Syllable kernel
 *  PCI busmanager
 *  Copyright (C) 2003 Arno Klenke
 *  Copyright (C) 1999 - 2001 Kurt Skauen
 *  
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

#include <posix/errno.h>
#include <atheos/device.h>
#include <atheos/kernel.h>
#include <atheos/isa_io.h>
#include <atheos/types.h>
#include <atheos/pci.h>
#include <atheos/kernel.h>
#include <atheos/spinlock.h>
#include <atheos/pci.h>
#include <atheos/bootmodules.h>
#include <atheos/config.h>

#include <macros.h>

#define MAX_PCI_BUSSES	16
#define	MAX_PCI_DEVICES	255

typedef struct
{
	uint32 nPCIDeviceNumber;
	uint32 nPrimaryBus;
	uint32 nSecondaryBus;
} PCI_Bus_s;

enum
{
	PCI_METHOD_1 = 0x01,
	PCI_METHOD_2 = 0x02,
};

uint32 g_nPCIMethod;
int g_nPCINumBusses = 0;
int g_nPCINumDevices = 0;
PCI_Bus_s *g_apsPCIBus[MAX_PCI_BUSSES];
PCI_Entry_s *g_apsPCIDevice[MAX_PCI_DEVICES];
SpinLock_s g_sPCILock = INIT_SPIN_LOCK( "pci_lock" );

/** 
 * \par Description: Checks wether a PCI bus is present and selects the access ethod
 * \par Note:
 * \par Warning:
 * \param
 * \return
 * \sa
 * \author	Kurt Skauen (kurt@atheos.cx)
 *****************************************************************************/

static void pci_inst_check( void )
{
	g_nPCIMethod = 0;

	/* Do simple register checks to find the way how to access the pci bus */

	/* Check PCI method 2 */
	outb( 0x0, 0x0cf8 );
	outb( 0x0, 0x0cfa );
	if ( inb( 0x0cf8 ) == 0x0 && inb( 0x0cfa ) == 0x0 )
	{
		g_nPCIMethod = PCI_METHOD_2;
		printk( "PCI: Using access method 2\n" );
		return;
	}

	/* Check PCI method 1 */
	outl( 0x80000000, 0x0cf8 );
	if ( inl( 0x0cf8 ) == 0x80000000 )
	{
		outl( 0x0, 0x0cf8 );
		if ( inl( 0x0cf8 ) == 0x0 )
		{
			g_nPCIMethod = PCI_METHOD_1;
			printk( "PCI: Using access method 1\n" );
			return;
		}
	}
}

/** 
 * \par Description: Reads 1/2/4 byte values from a device.
 * \par Note:
 * \par Warning:
 * \param nBusNum - Number of the bus.
 * \param nDevNum - Number of the device.
 * \param nFncNum - Number of the function.
 * \param nOffset - Offset in the PCI configuration space.
 * \param nSize   - 1, 2 or 4.
 * \return The value.
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/

uint32 read_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize )
{
	uint32 nFlags;
	uint32 nValue = 0;

	if ( 2 == nSize || 4 == nSize || 1 == nSize )
	{
		if ( g_nPCIMethod & PCI_METHOD_1 )
		{
			spinlock_cli( &g_sPCILock, nFlags );
			outl( 0x80000000 | ( nBusNum << 16 ) | ( nDevNum << 11 ) | ( nFncNum << 8 ) | ( nOffset & ~3 ), 0x0cf8 );
			switch ( nSize )
			{
			case 1:
				nValue = inb( 0x0cfc + ( nOffset & 3 ) );
				break;
			case 2:
				nValue = inw( 0x0cfc + ( nOffset & 2 ) );
				break;
			case 4:
				nValue = inl( 0x0cfc );
				break;
			default:
			}
			spinunlock_restore( &g_sPCILock, nFlags );
			return ( nValue );
		}
		else if ( g_nPCIMethod & PCI_METHOD_2 )
		{
			if ( nDevNum >= 16 )
			{
				printk( "PCI: read_pci_config() with an invalid device number\n" );
			}
			spinlock_cli( &g_sPCILock, nFlags );
			outb( ( 0xf0 | ( nFncNum << 1 ) ), 0x0cf8 );
			outb( nBusNum, 0x0cfa );
			switch ( nSize )
			{
			case 1:
				nValue = inb( ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			case 2:
				nValue = inw( ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			case 4:
				nValue = inl( ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			default:
			}
			outb( 0x0, 0x0cf8 );
			spinunlock_restore( &g_sPCILock, nFlags );

			return ( nValue );
		}
		else
		{
			printk( "PCI: read_pci_config() called without PCI present\n" );
		}
	}
	else
	{
		printk( "PCI: Invalid size %d passed to read_pci_config()\n", nSize );
	}
	return ( 0 );
}


/** 
 * \par Description: Writes 1/2/4 byte values to a device.
 * \par Note:
 * \par Warning:
 * \param nBusNum - Number of the bus.
 * \param nDevNum - Number of the device.
 * \param nFncNum - Number of the function.
 * \param nOffset - Offset in the PCI configuration space.
 * \param nSize   - 1, 2 or 4.
 * \param nValue  - Value which is written.
 * \return 0 if successful.
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/

status_t write_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize, uint32 nValue )
{
	uint32 nFlags;

	if ( 2 == nSize || 4 == nSize || 1 == nSize )
	{
		if ( g_nPCIMethod & PCI_METHOD_1 )
		{
			spinlock_cli( &g_sPCILock, nFlags );
			outl( 0x80000000 | ( nBusNum << 16 ) | ( nDevNum << 11 ) | ( nFncNum << 8 ) | ( nOffset & ~3 ), 0x0cf8 );
			switch ( nSize )
			{
			case 1:
				outb( nValue, 0x0cfc + ( nOffset & 3 ) );
				break;
			case 2:
				outw( nValue, 0x0cfc + ( nOffset & 2 ) );
				break;
			case 4:
				outl( nValue, 0x0cfc );
				break;
			default:
				spinunlock_restore( &g_sPCILock, nFlags );
				return ( -1 );
			}
			spinunlock_restore( &g_sPCILock, nFlags );
			return ( 0 );
		}
		else if ( g_nPCIMethod & PCI_METHOD_2 )
		{
			if ( nDevNum >= 16 )
			{
				printk( "PCI: write_pci_config() with an invalid device number\n" );
			}
			spinlock_cli( &g_sPCILock, nFlags );
			outb( ( 0xf0 | ( nFncNum << 1 ) ), 0x0cf8 );
			outb( nBusNum, 0x0cfa );
			switch ( nSize )
			{
			case 1:
				outb( nValue, ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			case 2:
				outw( nValue, ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			case 4:
				outl( nValue, ( 0xc000 | ( nDevNum << 8 ) | nOffset ) );
				break;
			default:
				spinunlock_restore( &g_sPCILock, nFlags );
				return ( -1 );
			}
			outb( 0x0, 0x0cf8 );
			spinunlock_restore( &g_sPCILock, nFlags );
			return ( 0 );
		}
		else
		{
			printk( "PCI: write_pci_config() called without PCI present\n" );
		}
	}
	else
	{
		printk( "PCI: Invalid size %d passed to write_pci_config()\n", nSize );
	}
	return ( -1 );
}


inline uint32 pci_size( uint32 base, uint32 mask )
{
	uint32 size = base & mask;

	return size & ~( size - 1 );
}


uint32 get_pci_memory_size( int nBusNum, int nDevNum, int nFncNum, int nResource )
{
	uint32 nSize, nBase;
	int nOffset = PCI_BASE_REGISTERS + nResource * 4;

	nBase = read_pci_config( nBusNum, nDevNum, nFncNum, nOffset, 4 );
	write_pci_config( nBusNum, nDevNum, nFncNum, nOffset, 4, ~0 );
	nSize = read_pci_config( nBusNum, nDevNum, nFncNum, nOffset, 4 );
	write_pci_config( nBusNum, nDevNum, nFncNum, nOffset, 4, nBase );
	if ( !nSize || nSize == 0xffffffff )
		return 0;
	if ( nBase == 0xffffffff )
		nBase = 0;
	if ( !( nSize & PCI_ADDRESS_SPACE ) )
	{
		return pci_size( nSize, PCI_ADDRESS_MEMORY_32_MASK );
	}
	else
	{
		return pci_size( nSize, PCI_ADDRESS_IO_MASK & 0xffff );
	}
}

/** 
 * \par Description: Called to read the information about one device.
 * \par Note:
 * \par Warning:
 * \param psInfo - Pointer to a PCI_Entry_s structure, which is filled.
 * \param nBusNum - Number of the bus.
 * \param nDevNum - Number of the device.
 * \param nFncNum - Number of the function.
 * \return Always 0
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/

static int read_pci_header( PCI_Entry_s * psInfo, int nBusNum, int nDevNum, int nFncNum )
{
	int i;

	psInfo->nBus = nBusNum;
	psInfo->nDevice = nDevNum;
	psInfo->nFunction = nFncNum;

	psInfo->nVendorID = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_VENDOR_ID, 2 );
	psInfo->nDeviceID = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_DEVICE_ID, 2 );
	psInfo->nCommand = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_COMMAND, 2 );
	psInfo->nStatus = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_STATUS, 2 );
	psInfo->nRevisionID = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_REVISION, 1 );

	psInfo->nClassApi = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_CLASS_API, 1 );
	psInfo->nClassBase = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_CLASS_BASE, 1 );
	psInfo->nClassSub = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_CLASS_SUB, 1 );

	psInfo->nCacheLineSize = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_LINE_SIZE, 1 );
	psInfo->nLatencyTimer = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_LATENCY, 1 );
	psInfo->nHeaderType = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_HEADER_TYPE, 1 );


	psInfo->u.h0.nBase0 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 0, 4 );
	psInfo->u.h0.nBase1 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 4, 4 );
	psInfo->u.h0.nBase2 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 8, 4 );
	psInfo->u.h0.nBase3 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 12, 4 );
	psInfo->u.h0.nBase4 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 16, 4 );
	psInfo->u.h0.nBase5 = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_BASE_REGISTERS + 20, 4 );

	psInfo->u.h0.nCISPointer = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_CARDBUS_CIS, 4 );
	psInfo->u.h0.nSubSysVendorID = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_SUBSYSTEM_VENDOR_ID, 2 );
	psInfo->u.h0.nSubSysID = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_SUBSYSTEM_ID, 2 );
	psInfo->u.h0.nExpROMAddr = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_ROM_BASE, 4 );
	psInfo->u.h0.nCapabilityList = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_CAPABILITY_LIST, 1 );
	psInfo->u.h0.nInterruptLine = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_INTERRUPT_LINE, 1 );
	psInfo->u.h0.nInterruptPin = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_INTERRUPT_PIN, 1 );
	psInfo->u.h0.nMinDMATime = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_MIN_GRANT, 1 );
	psInfo->u.h0.nMaxDMALatency = read_pci_config( nBusNum, nDevNum, nFncNum, PCI_MAX_LATENCY, 1 );


	/* Reserve memory */
	for ( i = 0; i < 6; i++ )
	{
		uint32 nAddr = *( &psInfo->u.h0.nBase0 + i );

		if ( ( nAddr & PCI_ADDRESS_SPACE ) || ( nAddr == 0x00000000 ) || ( nAddr == 0xffffffff ) )
			continue;
			
		nAddr = nAddr & PCI_ADDRESS_MEMORY_32_MASK;
		
		alloc_physical( &nAddr, true, get_pci_memory_size( nBusNum, nDevNum, nFncNum, i ) );
	}

	return( 0 );
}

/** 
 * \par Description: Returns information about one PCI device.
 * \par Note:
 * \par Warning:
 * \param psInfo - Pointer to a PCI_Info_s structure, which is filled with
 *                 the information.
 * \param nIndex - Index of the device.
 * \return 0 if successful.
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/

status_t get_pci_info( PCI_Info_s * psInfo, int nIndex )
{
	if ( NULL == psInfo )
	{
		return ( -EFAULT );
	}
	if ( nIndex >= 0 && nIndex < g_nPCINumDevices )
	{
		PCI_Entry_s *psEntry = g_apsPCIDevice[nIndex];

		kassertw( NULL != psEntry );

		psInfo->nBus = psEntry->nBus;
		psInfo->nDevice = psEntry->nDevice;
		psInfo->nFunction = psEntry->nFunction;

		psInfo->nVendorID = psEntry->nVendorID;
		psInfo->nDeviceID = psEntry->nDeviceID;
		psInfo->nRevisionID = psEntry->nRevisionID;

		psInfo->nCacheLineSize = psEntry->nCacheLineSize;
		psInfo->nHeaderType = psEntry->nHeaderType;

		psInfo->nClassApi = psEntry->nClassApi;
		psInfo->nClassBase = psEntry->nClassBase;
		psInfo->nClassSub = psEntry->nClassSub;

		psInfo->u.h0.nBase0 = psEntry->u.h0.nBase0;
		psInfo->u.h0.nBase1 = psEntry->u.h0.nBase1;
		psInfo->u.h0.nBase2 = psEntry->u.h0.nBase2;
		psInfo->u.h0.nBase3 = psEntry->u.h0.nBase3;
		psInfo->u.h0.nBase4 = psEntry->u.h0.nBase4;
		psInfo->u.h0.nBase5 = psEntry->u.h0.nBase5;

		psInfo->u.h0.nInterruptLine = psEntry->u.h0.nInterruptLine;
		psInfo->u.h0.nInterruptPin = psEntry->u.h0.nInterruptPin;
		psInfo->u.h0.nMinDMATime = psEntry->u.h0.nMinDMATime;
		psInfo->u.h0.nMaxDMALatency = psEntry->u.h0.nMaxDMALatency;


		psInfo->nHandle = psEntry->nHandle;
		return ( 0 );
	}
	else
	{
		return ( -EINVAL );
	}
}


/** 
 * \par Description: Enables PCI busmaster access
 * \par Warning:
 * \param nBusNum - Number of the bus.
 * \param nDevNum - Number of the device.
 * \param nFncNum - Number of the function.
 * \return
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/
void enable_pci_master( int nBusNum, int nDevNum, int nFncNum )
{
  write_pci_config( nBusNum, nDevNum, nFncNum, PCI_COMMAND, 2,
                    read_pci_config( nBusNum, nDevNum, nFncNum, PCI_COMMAND, 2 )
                    | PCI_COMMAND_MASTER);
}

void set_pci_latency( int nBusNum, int nDevNum, int nFncNum, uint8 nLatency )
{
	write_pci_config( nBusNum, nDevNum, nFncNum, PCI_LATENCY, 1, nLatency );
}

/** 
 * \par Description: Scans one bus for PCI devices.
 * \par Note: It is used recursive when PCI bridges are detected.
 * \par Warning:
 * \param
 * \return
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/
void pci_scan_bus( int nBusNum, int nBridgeFrom, int nBusDev )
{
	PCI_Bus_s *psBus;
	PCI_Entry_s *psInfo;
	int nDeviceNumberPerBus = ( g_nPCIMethod & PCI_METHOD_1 ) ? 32 : 16;
	int nDev, nFnc;
	uint32 nVendorID;
	uint8 nHeaderType = 0;

	/* Allocate Resources for the bus */
	psBus = kmalloc( sizeof( PCI_Bus_s ), MEMF_KERNEL | MEMF_CLEAR );
	g_apsPCIBus[nBusNum] = psBus;
	g_nPCINumBusses++;

	psBus->nPCIDeviceNumber = nBusDev;
	psBus->nPrimaryBus = nBridgeFrom;
	psBus->nSecondaryBus = nBusNum;

	printk( "PCI: Scanning Bus %i\n", nBusNum );

	/* Look for devices on this bus */
	for ( nDev = 0; nDev < nDeviceNumberPerBus; nDev++ )
	{
		for ( nFnc = 0; nFnc < 8; nFnc++ )
		{
			nVendorID = read_pci_config( nBusNum, nDev, nFnc, PCI_VENDOR_ID, 2 );
			/* One device has been found */
			if ( nVendorID != 0xffff && nVendorID != 0x0000 )
			{
				/* If it is not a multifunction device than we do not have to continue scanning */
				if ( nFnc == 0 )
				{
					nHeaderType = read_pci_config( nBusNum, nDev, nFnc, PCI_HEADER_TYPE, 1 );
				}
				else
				{
					if ( ( nHeaderType & PCI_MULTIFUNCTION ) == 0 )
						continue;
				}

				/* Allocate resources for the new device */
				psInfo = kmalloc( sizeof( PCI_Entry_s ), MEMF_KERNEL | MEMF_CLEAR );

				if ( psInfo != NULL )
				{
					read_pci_header( psInfo, nBusNum, nDev, nFnc );

					if ( g_nPCINumDevices < MAX_PCI_DEVICES )
					{
						g_apsPCIDevice[g_nPCINumDevices++] = psInfo;

						printk( "PCI: Device %i VendorID: %04x DeviceID: %04x at %i:%i:%i\n", g_nPCINumDevices - 1, psInfo->nVendorID, psInfo->nDeviceID, nBusNum, nDev, nFnc );
					}
					else
					{
						printk( "WARNING : To many PCI devices!\n" );
					}
				}

				/* Register device */


				/* Look if the device is a bridge */
				if ( nHeaderType & PCI_HEADER_BRIDGE )
				{
					psInfo->nHandle = register_device( "", PCI_BUS_NAME );
					claim_device( -1, psInfo->nHandle, "PCI->PCI/AGP Bridge", DEVICE_SYSTEM );
					/* Disable bridge */
					write_pci_config( nBusNum, nDev, nFnc, PCI_COMMAND, 2, read_pci_config( nBusNum, nDev, nFnc, PCI_COMMAND, 2 ) & ~( PCI_COMMAND_IO | PCI_COMMAND_MEMORY ) );

					/* Write new values */
					write_pci_config( nBusNum, nDev, nFnc, PCI_BUS_PRIMARY, 1, nBusNum );
					write_pci_config( nBusNum, nDev, nFnc, PCI_BUS_SECONDARY, 1, g_nPCINumBusses );
					write_pci_config( nBusNum, nDev, nFnc, PCI_BUS_SUBORDINATE, 1, 0xff );
					pci_scan_bus( g_nPCINumBusses, nBusNum, g_nPCINumDevices - 1 );
					/* Note : g_nPCINumBusses - 1 because the number of busses will be increased by 
					   pci_scan_bus() */
					write_pci_config( nBusNum, nDev, nFnc, PCI_BUS_SUBORDINATE, 1, g_nPCINumBusses - 1 );
					/* Enable bridge */
					write_pci_config( nBusNum, nDev, nFnc, PCI_COMMAND, 2, read_pci_config( nBusNum, nDev, nFnc, PCI_COMMAND, 2 ) | ( PCI_COMMAND_IO | PCI_COMMAND_MEMORY ) );
				}
				else
				{
					char zTemp[255];

					sprintf( zTemp, "PCI 0x%x 0x%x", ( uint )psInfo->nVendorID, ( uint )psInfo->nDeviceID );
					psInfo->nHandle = register_device( zTemp, PCI_BUS_NAME );

					/* Special devices */
					if ( psInfo->nClassBase == PCI_BRIDGE && psInfo->nClassSub == PCI_HOST )
						claim_device( -1, psInfo->nHandle, "PCI Host Bridge", DEVICE_SYSTEM );
					else if ( psInfo->nClassBase == PCI_BRIDGE && psInfo->nClassSub == PCI_ISA )
						claim_device( -1, psInfo->nHandle, "PCI->ISA Bridge", DEVICE_SYSTEM );
					else if ( psInfo->nClassBase == PCI_BRIDGE )
						claim_device( -1, psInfo->nHandle, "PCI Bridge", DEVICE_SYSTEM );


				}
			}
		}
	}
	printk( "PCI: Scan of bus finished\n" );
}

/** 
 * \par Description: Called to scan for pci devices.
 * \par Note:
 * \par Warning:
 * \param
 * \return
 * \sa
 * \author	Arno Klenke (arno_klenke@yahoo.de)
 *****************************************************************************/
void pci_scan_all()
{
	uint8 *pBuffer;
	size_t nSize;
	char *pPtr;
	bool bDeviceID;
	char zTemp[255];
	int nTempPtr = 0;
	uint32 nVendorID = 0;
	uint32 nDeviceID = 0;
	int nDevice = 0;

	if ( g_nPCIMethod == 0 )
		return;
	/* Scan first bus */
	pci_scan_bus( 0, -1, -1 );
	printk( "PCI: %i devices detected\n", g_nPCINumDevices );


	/* Now load configuration */
	if ( read_kernel_config_entry( "<PCI>", &pBuffer, &nSize ) != 0 )
	{
		enable_all_devices();	/* Maybe configuration has changed */
		return;
	}

	/* Parse config and check for configuration changes */
	pPtr = pBuffer;
	bDeviceID = false;
	while ( nSize > 0 )
	{
		if ( *pPtr == '-' )
		{
			if ( bDeviceID )
			{
				/* Something went wrong */
				printk( "PCI: Configuration corrupted!\n" );
				enable_all_devices();	/* Maybe configuration has changed */
				return;
			}
			zTemp[nTempPtr] = 0;
			bDeviceID = true;
			nTempPtr = 0;

			/* Save VendorID */
			nVendorID = atol( zTemp );
		}
		else if ( *pPtr == '\n' )
		{
			if ( !bDeviceID )
			{
				/* Something went wrong */
				printk( "PCI: Configuration corrupted!\n" );
				enable_all_devices();	/* Maybe configuration has changed */
				return;
			}
			zTemp[nTempPtr] = 0;
			bDeviceID = false;
			nTempPtr = 0;

			/* Save DeviceID */
			nDeviceID = atol( zTemp );

			if ( nDevice >= g_nPCINumDevices )
			{
				printk( "PCI: Configuration change\n" );
				enable_all_devices();
				nSize = 0;
				break;
			}

			/* Compare with the current config */
			if ( g_apsPCIDevice[nDevice]->nVendorID != nVendorID || g_apsPCIDevice[nDevice]->nDeviceID != nDeviceID )
			{
				printk( "PCI: Configuration change\n" );
				enable_all_devices();
			}

			nDevice++;

		}
		else
		{
			/* Save character */
			zTemp[nTempPtr++] = *pPtr;
		}

		pPtr++;
		nSize--;
	}
	if ( nDevice < g_nPCINumDevices )
	{
		printk( "PCI: Configuration change\n" );
		enable_all_devices();
	}

	/* Delete buffer */
	kfree( pBuffer );
}


bool get_bool_arg( bool *pbValue, const char *pzName, const char *pzArg, int nArgLen )
{
	char zBuffer[256];

	if ( get_str_arg( zBuffer, pzName, pzArg, nArgLen ) == false )
	{
		return ( false );
	}
	if ( stricmp( zBuffer, "false" ) == 0 )
	{
		*pbValue = false;
		return ( true );
	}
	else if ( stricmp( zBuffer, "true" ) == 0 )
	{
		*pbValue = true;
		return ( true );
	}
	return ( false );
}

/** 
 * \par Description: Initialize the pci busmanager.
 * \par Note:
 * \par Warning:
 * \param
 * \return
 * \sa
 * \author	Kurt Skauen (kurt@atheos.cx)
 *****************************************************************************/

status_t bus_init()
{
	/* Check if the use of the bus is disabled */
	int i;
	int argc;
	const char *const *argv;
	bool bDisablePCI = false;

	get_kernel_arguments( &argc, &argv );

	for ( i = 0; i < argc; ++i )
	{
		if ( get_bool_arg( &bDisablePCI, "disable_pci=", argv[i], strlen( argv[i] ) ) )
			if ( bDisablePCI )
			{
				printk( "PCI bus disabled by user\n" );
				return ( -1 );
			}
	}

	/* Check if we can access the pci bus */
	pci_inst_check();
	if ( g_nPCIMethod == 0 )
	{
		printk( "No PCI bus found\n" );
		return ( -1 );
	}
	else
	{
		pci_scan_all();
	}
	return ( 0 );
}


void bus_uninit()
{
	int i;
	char zTemp[255];
	int nSize = 0;

	/* Save configuration */
	for ( i = 0; i < g_nPCINumDevices; i++ )
	{
		sprintf( zTemp, "%i-%i\n", g_apsPCIDevice[i]->nVendorID, g_apsPCIDevice[i]->nDeviceID );
		nSize += strlen( zTemp );
	}
	write_kernel_config_entry_header( "<PCI>", nSize );

	for ( i = 0; i < g_nPCINumDevices; i++ )
	{
		sprintf( zTemp, "%i-%i\n", g_apsPCIDevice[i]->nVendorID, g_apsPCIDevice[i]->nDeviceID );
		write_kernel_config_entry_data( &zTemp[0], strlen( zTemp ) );
	}

	/* Free resources */

	for ( i = 0; i < g_nPCINumDevices; i++ )
	{
		kfree( g_apsPCIDevice[i] );
	}
	for ( i = 0; i < g_nPCINumBusses; i++ )
	{
		kfree( g_apsPCIBus[i] );
	}
}

PCI_bus_s sBus = {
	get_pci_info,
	read_pci_config,
	write_pci_config,
	enable_pci_master,
	set_pci_latency
};

void *bus_get_hooks( int nVersion )
{
	if ( nVersion != PCI_BUS_VERSION )
		return ( NULL );
	return ( ( void * )&sBus );
}









