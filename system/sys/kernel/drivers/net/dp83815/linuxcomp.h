#ifndef _LINUXCOMP_H_
#define _LINUXCOMP_H_


typedef uint8 					u8;
typedef uint16					u16;
typedef uint32					u32;
typedef uint64					u64;

typedef int8					s8;
typedef int16					s16;
typedef int32					s32;
typedef int64					s64;

typedef uint32					dma_addr_t;

#define EISA_bus 0

#define MAX_ADDR_LEN	6

struct net_device
{

    /*
     * This is the first field of the "visible" part of this structure
     * (i.e. as seen by users in the "Space.c" file).  It is the name
     * the interface.
     */
    char            *name;

     /*
     *  I/O specific fields
     *  FIXME: Merge these and struct ifmap into one
     */
    unsigned long   rmem_end; /* shmem "recv" end */
    unsigned long   rmem_start; /* shmem "recv" start */
    unsigned long   mem_end;  /* shared mem end */
    unsigned long   mem_start;  /* shared mem start */
    unsigned long   base_addr;  /* device I/O address   */
    unsigned int    irq;        /* device IRQ number    */
    
    /* Low-level status flags. */
    volatile unsigned char  start;      /* start an operation   */
    /*
     * These two are just single-bit flags, but due to atomicity
     * reasons they have to be inside a "unsigned long". However,
     * they should be inside the SAME unsigned long instead of
     * this wasteful use of memory..
     */
    unsigned char   if_port;  /* Selectable AUI, TP,..*/
    unsigned char   dma;    /* DMA channel    */
                                                                                                                                                                                                        
//  unsigned long   state;
    
    unsigned long       interrupt;  /* bitops.. */
    unsigned long       tbusy;      /* transmitter busy */
    
    struct device       *next;
    
    /*
     * This marks the end of the "visible" part of the structure. All
     * fields hereafter are internal to the system, and may change at
     * will (read: may be cleaned up at will).
     */

    /* These may be needed for future network-power-down code. */
    unsigned long       trans_start;    /* Time (in jiffies) of last Tx */
    unsigned long           last_rx;        /* Time of last Rx      */
    unsigned    mtu;  /* interface MTU value    */
    unsigned short    type; /* interface hardware type  */
    unsigned short    hard_header_len;  /* hardware hdr length  */   
    unsigned short      flags;  /* interface flags (a la BSD) */
    void            *priv;  /* pointer to private data  */

    /* Interface address info. */
    unsigned char   broadcast[MAX_ADDR_LEN];  /* hw bcast add */
    unsigned char   pad;    /* make dev_addr aligned to 8 bytes */
    unsigned char   dev_addr[MAX_ADDR_LEN]; /* hw address */
    unsigned char   addr_len; /* hardware address length  */    

//	struct dev_mc_list	*mc_list;	/* Multicast mac addresses	*/
	int			mc_count;	/* Number of installed mcasts	*/
//	int			promiscuity;
//	int			allmulti;

    NetQueue_s		*packet_queue;
    int irq_handle; /* IRQ handler handle */

	int device_handle; /* device handle from probing */
    
    int node_handle;    /* handle of device node in /dev */
};

//#define net_device device

#define jiffies     (get_system_time()/1000LL)
#define HZ          1000
#define JIFF2U(a)   ((a)*1000LL)    /* Convert time in JIFFIES to micro sec. */

#define virt_to_bus 			virt_to_phys
#define bus_to_virt 			phys_to_virt

#define cpu_to_le32(x) 			((uint32)(x))
#define le32_to_cpu(x) 			((uint32)(x))
#define cpu_to_le16(x) 			((uint16)(x))
#define le16_to_cpu(x) 			((uint16)(x))

#define virt_to_le32desc(addr)  cpu_to_le32(virt_to_bus(addr))
#define le32desc_to_virt(addr)  bus_to_virt(le32_to_cpu(addr))

#define copy_to_user(x, y, z) 	memcpy_to_user(x, y, z)
#define copy_from_user(x, y, z) memcpy_from_user(x, y, z)

#define put_user(x, y) 			do { *y = x; } while(0)
#define get_user(x, y) 			do { x = *y; } while(0)

#define _IOC_NRBITS	8
#define _IOC_TYPEBITS	8
#define _IOC_SIZEBITS	14
#define _IOC_DIRBITS	2

#define _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK	((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

#define _IOC_DIR(nr)		(((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

#define FMODE_READ				1	
#define FMODE_WRITE				2

#define spin_lock(x)			spinlock(x)
#define spin_unlock(x)			spinunlock(x)

#define spin_lock_irq(x)		spinlock(x)
#define spin_unlock_irq(x)		spinunlock(x)

#define spin_lock_irqsave(x, y)	spinlock_cli(x, y)
#define spin_unlock_irqrestore(x, y) spinunlock_restore(x, y)

#define up(x)					UNLOCK(x)
#define down(x)					LOCK(x)

#define IFF_RUNNING 0x40
#define netif_wake_queue(dev)   do { clear_bit(0, (void*)&dev->tbusy); } while(0)
#define netif_start_queue(dev)  clear_bit(0, (void*)&dev->tbusy)
#define netif_start_tx_queue(dev)  do { (dev)->tbusy = 0; dev->start = 1; } while(0)
#define netif_stop_tx_queue(dev)  do { (dev)->tbusy = 1; dev->start = 0; } while(0)
#define netif_stop_queue(dev)   set_bit(0, (void*)&dev->tbusy)
#define netif_queue_paused(dev)	((dev)->tbusy != 0)
#define netif_pause_tx_queue(dev)	(test_and_set_bit(0, (void*)&dev->tbusy))
#define netif_unpause_tx_queue(dev)	do { clear_bit(0, (void*)&dev->tbusy); } while(0)
#define netif_resume_tx_queue(dev)	do { clear_bit(0, (void*)&dev->tbusy); } while(0)
#define netif_running(dev)	((dev)->start != 0)
#define netif_mark_up(dev)	do { (dev)->start = 1; } while (0)
#define netif_mark_down(dev)	do { (dev)->start = 0; } while (0)
#define netif_queue_stopped(dev)	((dev)->tbusy)
#define netif_link_down(dev)	(dev)->flags &= ~ IFF_RUNNING
#define netif_link_up(dev)	(dev)->flags |= IFF_RUNNING
#define netif_carrier_on(dev) netif_link_up(dev)
#define netif_carrier_off(dev) netif_link_down(dev)
#define netif_carrier_ok(dev) ((dev)->flags & IFF_RUNNING)

#define assert(expr) \
        if(!(expr)) {					\
        printk( "Assertion failed! %s,%s,%s,line=%d\n",	\
        #expr,__FILE__,__FUNCTION__,__LINE__);		\
        }

#define PCI_CLASS_REVISION	0x08

extern inline unsigned long virt_to_phys(volatile void * address)
{
	return (unsigned long) address;
}

extern inline void * phys_to_virt(unsigned long address)
{
	return (void *) address;
}

static inline void *pci_alloc_consistent(PCI_Info_s *hwdev, size_t size,
					 dma_addr_t *dma_handle)
{
	void *virt_ptr;

	virt_ptr = kmalloc(size, MEMF_KERNEL);
	*dma_handle = virt_to_bus(virt_ptr);
	return virt_ptr;
}

static inline PCI_Info_s * pci_find_device(int vendor_id, int device_id, PCI_Info_s * pci_dev)
{
	int i;
	static PCI_Info_s  sInfo;
	PCI_bus_s *psBus = get_busmanager( PCI_BUS_NAME, PCI_BUS_VERSION );
	if( psBus == NULL )
		return NULL;

	for ( i = 0 ; psBus->get_pci_info( &sInfo, i ) == 0 ; ++i )
	{
		if ( sInfo.nVendorID == vendor_id && sInfo.nDeviceID == device_id)
		{
			return &sInfo;
		}
	}
	return NULL;
}

#define pci_read_config_byte(dev, address, val) \
	val = g_psBus->read_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val))
#define pci_read_config_word(dev, address, val) \
	val = g_psBus->read_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val))
#define pci_read_config_dword(dev, address, val) \
	val = g_psBus->read_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val))
#define pci_write_config_byte(dev, address, val) \
	g_psBus->write_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val), (uint32)val)
#define pci_write_config_word(dev, address, val) \
	g_psBus->write_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val), (uint32)val)
#define pci_write_config_dword(dev, address, val) \
	g_psBus->write_pci_config(dev->nBus, dev->nDevice, dev->nFunction,\
	address, sizeof(val), (uint32)val)

#define pci_free_consistent(cookie, size, ptr, dma_ptr)	kfree(ptr)
#define pci_map_single(cookie, address, size, dir)	virt_to_bus(address)
#define pci_unmap_single(cookie, address, size, dir)

#define ALIGN( p, m)  (  (typeof(p)) (((uint32)(p)+m)&~m)  )
#define ALIGN8( p )   ALIGN(p,7)
#define ALIGN16( p )  ALIGN(p,15)
#define ALIGN32( p )  ALIGN(p,31)

/* To align packets. */
PacketBuf_s *alloc_pkt_buffer_aligned(int nSize) {
    PacketBuf_s *skb;
        
    skb = alloc_pkt_buffer( nSize+15 );
    if (skb)
        skb->pb_pData = ALIGN16( skb->pb_pData );
    
    return skb;
}

/* Needed because Athe does not have skb, guess atheos never will get it either */
void* skb_put( PacketBuf_s* psBuffer, int nSize )
{
    void* pOldEnd = psBuffer->pb_pHead + psBuffer->pb_nSize;
    
    psBuffer->pb_nSize += nSize;
    return( pOldEnd );
}

/* FIXME: I'm not sure if this is correct */
static inline void *ioremap(unsigned long phys_addr, unsigned long size) {
    return (void *)phys_addr;
}

#define PCI_ANY_ID (~0)

struct pci_device_id {
    unsigned int vendor_id, device_id;      /* Vendor and device ID or PCI_ANY_ID */
    unsigned int subvendor, subdevice;  /* Subsystem ID's or PCI_ANY_ID */
    unsigned int class, class_mask;     /* (class,subclass,prog-if) triplet */
    unsigned long driver_data;      /* Data private to the driver */
};

static inline void *request_region(unsigned long start, unsigned long len, char *name) {
    return (void *)1;    // not-NULL value
}

static inline void release_region(unsigned long start, unsigned long len) {
}

#define PCIBIOS_MAX_LATENCY 255

#endif
