/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Handling of the emulated machines.
 *
 *
 *
 * Authors:	Sarah Walker, <http://pcem-emulator.co.uk/>
 *		Miran Grca, <mgrca8@gmail.com>
 *		Fred N. van Kempen, <decwiz@yahoo.com>
 *
 *		Copyright 2008-2020 Sarah Walker.
 *		Copyright 2016-2020 Miran Grca.
 *		Copyright 2017-2020 Fred N. van Kempen.
 */
#ifndef EMU_MACHINE_H
# define EMU_MACHINE_H


/* Machine feature flags. */
#ifdef NEW_FLAGS
#define MACHINE_PC		0x000000	/* PC architecture */
#define MACHINE_AT		0x000001	/* PC/AT architecture */
#define MACHINE_PS2		0x000002	/* PS/2 architecture */
#define MACHINE_ISA		0x000010	/* sys has ISA bus */
#define MACHINE_CBUS		0x000020	/* sys has C-BUS bus */
#define MACHINE_EISA		0x000040	/* sys has EISA bus */
#define MACHINE_VLB		0x000080	/* sys has VL bus */
#define MACHINE_MCA		0x000100	/* sys has MCA bus */
#define MACHINE_PCI		0x000200	/* sys has PCI bus */
#define MACHINE_AGP		0x000400	/* sys has AGP bus */
#define MACHINE_HDC		0x001000	/* sys has int HDC */
#define MACHINE_VIDEO		0x002000	/* sys has int video */
#define MACHINE_VIDEO_FIXED	0x004000	/* sys has ONLY int video */
#define MACHINE_MOUSE		0x008000	/* sys has int mouse */
#define MACHINE_SOUND		0x010000	/* sys has int sound */
#define MACHINE_NONMI		0x020000	/* sys does not have NMI's */
#define MACHINE_FDC		0x040000	/* sys has int FDC */
#else
#define MACHINE_PC		0x000000	/* PC architecture */
#define MACHINE_AT		0x000001	/* PC/AT architecture */
#define MACHINE_PS2		0x000002	/* PS/2 architecture */
#define MACHINE_ISA		0x000010	/* sys has ISA bus */
#define MACHINE_CBUS		0x000020	/* sys has C-BUS bus */
#define MACHINE_EISA		0x000040	/* sys has EISA bus */
#define MACHINE_VLB		0x000080	/* sys has VL bus */
#define MACHINE_MCA		0x000100	/* sys has MCA bus */
#define MACHINE_PCI		0x000200	/* sys has PCI bus */
#define MACHINE_AGP		0x000400	/* sys has AGP bus */
#define MACHINE_HDC		0x001000	/* sys has int HDC */
#define MACHINE_VIDEO		0x002000	/* sys has int video */
#define MACHINE_VIDEO_FIXED	0x004000	/* sys has ONLY int video */
#define MACHINE_MOUSE		0x008000	/* sys has int mouse */
#define MACHINE_SOUND		0x010000	/* sys has int sound */
#define MACHINE_NONMI		0x020000	/* sys does not have NMI's */
#define MACHINE_FDC		0x040000	/* sys has int FDC */
#endif

#define IS_ARCH(m, a)		(machines[(m)].flags & (a)) ? 1 : 0;


enum {
    MACHINE_TYPE_NONE = 0,
    MACHINE_TYPE_8088,
    MACHINE_TYPE_8086,
    MACHINE_TYPE_286,
    MACHINE_TYPE_386SX,
    MACHINE_TYPE_386DX,
    MACHINE_TYPE_486,
    MACHINE_TYPE_SOCKET4,
    MACHINE_TYPE_SOCKET5,
    MACHINE_TYPE_SOCKET7_3V,
    MACHINE_TYPE_SOCKET7,
    MACHINE_TYPE_SOCKETS7,
    MACHINE_TYPE_SOCKET8,
    MACHINE_TYPE_SLOT1,
    MACHINE_TYPE_SLOT2,
    MACHINE_TYPE_SOCKET370,
    MACHINE_TYPE_MAX
};


typedef struct _machine_type_ {
    const char	*name;
    const char  id;
} machine_type_t;


#ifdef NEW_STRUCT
typedef struct _machine_ {
    const char	*name;
    const char	*internal_name;
    const char  type;
#ifdef EMU_DEVICE_H
    const device_t	*device;
#else
    void	*device;
#endif
    struct {
	const char *name;
#ifdef EMU_CPU_H
	CPU *cpus;
#else
	void *cpus;
#endif
    }		cpu[5];
    int		flags;
    uint32_t	min_ram, max_ram;
    int		ram_granularity;
    int		nvrmask;
} machine_t;
#else
typedef struct _machine_ {
    const char	*name;
    const char	*internal_name;
    const char  type;
    struct {
	const char *name;
#ifdef EMU_CPU_H
	CPU *cpus;
#else
	void *cpus;
#endif
    }		cpu[5];
    int		flags;
    uint32_t	min_ram, max_ram;
    int		ram_granularity;
    int		nvrmask;
    int		(*init)(const struct _machine_ *);
#ifdef EMU_DEVICE_H
    const device_t	*(*get_device)(void);
#else
    void	*get_device;
#endif
} machine_t;
#endif


/* Global variables. */
extern const machine_type_t	machine_types[];
extern const machine_t		machines[];
extern int			bios_only;
extern int			machine;
extern int			AT, PCI;


/* Core functions. */
extern int	machine_count(void);
extern int	machine_available(int m);
extern char	*machine_getname(void);
extern char	*machine_get_internal_name(void);
extern int	machine_get_machine_from_internal_name(char *s);
extern void	machine_init(void);
#ifdef EMU_DEVICE_H
extern const device_t	*machine_getdevice(int m);
#endif
extern char	*machine_get_internal_name_ex(int m);
extern int	machine_get_nvrmask(int m);
extern void	machine_close(void);


/* Initialization functions for boards and systems. */
extern void	machine_common_init(const machine_t *);

/* m_amstrad.c */
extern int	machine_pc1512_init(const machine_t *);
extern int	machine_pc1640_init(const machine_t *);
extern int	machine_pc200_init(const machine_t *);
extern int	machine_ppc512_init(const machine_t *);
extern int	machine_pc2086_init(const machine_t *);
extern int	machine_pc3086_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t  	*pc1512_get_device(void);
extern const device_t 	*pc1640_get_device(void);
extern const device_t 	*pc200_get_device(void);
extern const device_t 	*ppc512_get_device(void);
extern const device_t 	*pc2086_get_device(void);
extern const device_t 	*pc3086_get_device(void);
#endif

/* m_at.c */
extern void	machine_at_common_init_ex(const machine_t *, int type);
extern void	machine_at_common_init(const machine_t *);
extern void	machine_at_init(const machine_t *);
extern void	machine_at_ps2_init(const machine_t *);
extern void	machine_at_common_ide_init(const machine_t *);
extern void	machine_at_ibm_common_ide_init(const machine_t *);
extern void	machine_at_ide_init(const machine_t *);
extern void	machine_at_ps2_ide_init(const machine_t *);

extern int	machine_at_ibm_init(const machine_t *);

//IBM AT with custom BIOS
extern int	machine_at_ibmatami_init(const machine_t *); // IBM AT with AMI BIOS
extern int	machine_at_ibmatpx_init(const machine_t *); //IBM AT with Phoenix BIOS
extern int	machine_at_ibmatquadtel_init(const machine_t *); // IBM AT with Quadtel BIOS

extern int	machine_at_ibmxt286_init(const machine_t *);

#if defined(DEV_BRANCH) && defined(USE_SIEMENS)
extern int	machine_at_siemens_init(const machine_t *); //Siemens PCD-2L. N82330 discrete machine. It segfaults in some places
#endif

#if defined(DEV_BRANCH) && defined(USE_OPEN_AT)
extern int	machine_at_open_at_init(const machine_t *);
#endif

/* m_at_286_386sx.c */
#if defined(DEV_BRANCH) && defined(USE_AMI386SX)
extern int	machine_at_headland_init(const machine_t *);
#endif
extern int	machine_at_tg286m_init(const machine_t *);
extern int	machine_at_ama932j_init(const machine_t *);
extern int	machine_at_px286_init(const machine_t *);
extern int	machine_at_quadt286_init(const machine_t *);
extern int	machine_at_mr286_init(const machine_t *);

extern int	machine_at_neat_init(const machine_t *);
extern int	machine_at_neat_ami_init(const machine_t *);

extern int	machine_at_goldstar386_init(const machine_t *);

extern int	machine_at_award286_init(const machine_t *);
extern int	machine_at_gdc212m_init(const machine_t *);
extern int	machine_at_gw286ct_init(const machine_t *);
extern int	machine_at_super286tr_init(const machine_t *);
extern int	machine_at_spc4200p_init(const machine_t *);
extern int	machine_at_spc4216p_init(const machine_t *);
extern int	machine_at_kmxc02_init(const machine_t *);
extern int	machine_at_deskmaster286_init(const machine_t *);

extern int	machine_at_shuttle386sx_init(const machine_t *);
extern int	machine_at_adi386sx_init(const machine_t *);
extern int	machine_at_commodore_sl386sx_init(const machine_t *);
extern int	machine_at_wd76c10_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*at_ama932j_get_device(void);
extern const device_t	*at_commodore_sl386sx_get_device(void);
#endif

/* m_at_386dx_486.c */

extern int	machine_at_acc386_init(const machine_t *);
extern int	machine_at_asus386_init(const machine_t *);
extern int  machine_at_ecs386_init(const machine_t *);
extern int	machine_at_micronics386_init(const machine_t *);

extern int	machine_at_pb410a_init(const machine_t *);

extern int	machine_at_acera1g_init(const machine_t *);
extern int	machine_at_ali1429_init(const machine_t *);
extern int	machine_at_winbios1429_init(const machine_t *);

extern int	machine_at_opti495_init(const machine_t *);
extern int	machine_at_opti495_ami_init(const machine_t *);
extern int	machine_at_opti495_mr_init(const machine_t *);

extern int	machine_at_vli486sv2g_init(const machine_t *);
extern int	machine_at_ami471_init(const machine_t *);
extern int	machine_at_dtk486_init(const machine_t *);
extern int	machine_at_px471_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_WIN471)
extern int	machine_at_win471_init(const machine_t *);
#endif

extern int	machine_at_r418_init(const machine_t *);
extern int	machine_at_ls486e_init(const machine_t *);
extern int	machine_at_4dps_init(const machine_t *);
extern int	machine_at_alfredo_init(const machine_t *);
extern int	machine_at_486sp3g_init(const machine_t *);
extern int	machine_at_486ap4_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t 	*at_acera1g_get_device(void);
#endif

/* m_at_commodore.c */
extern int	machine_at_cmdpc_init(const machine_t *);

/* m_at_compaq.c */
extern int	machine_at_portableii_init(const machine_t *);
extern int	machine_at_portableiii_init(const machine_t *);
extern int	machine_at_portableiii386_init(const machine_t *);
#ifdef EMU_DEVICE_H
extern const device_t 	*at_cpqiii_get_device(void);
#endif

/* m_at_socket4_5.c */
extern int  machine_at_excalibur_init(const machine_t *);

extern int	machine_at_batman_init(const machine_t *);
extern int	machine_at_ambradp60_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_VPP60)
extern int	machine_at_valuepointp60_init(const machine_t *);
#endif
extern int	machine_at_p5mp3_init(const machine_t *);
extern int	machine_at_586mc1_init(const machine_t *);

extern int	machine_at_plato_init(const machine_t *);
extern int	machine_at_ambradp90_init(const machine_t *);
extern int	machine_at_430nx_init(const machine_t *);

extern int	machine_at_p54tp4xe_init(const machine_t *);
extern int	machine_at_endeavor_init(const machine_t *);
extern int	machine_at_zappa_init(const machine_t *);
extern int	machine_at_gw2kzp_init(const machine_t *);
extern int	machine_at_mb500n_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_VECTRA54)
extern int	machine_at_vectra54_init(const machine_t *);
#endif
extern int	machine_at_powermate_v_init(const machine_t *);
extern int	machine_at_acerv30_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*at_endeavor_get_device(void);
#endif

/* m_at_socket7_s7.c */
extern int	machine_at_chariot_init(const machine_t *);
extern int	machine_at_mr586_init(const machine_t *);
extern int	machine_at_thor_init(const machine_t *);
extern int	machine_at_gw2katx_init(const machine_t *);
extern int	machine_at_mrthor_init(const machine_t *);
extern int	machine_at_pb640_init(const machine_t *);

extern int	machine_at_acerm3a_init(const machine_t *);
extern int	machine_at_acerv35n_init(const machine_t *);
extern int	machine_at_ap53_init(const machine_t *);
extern int	machine_at_p55t2p4_init(const machine_t *);
extern int	machine_at_p55t2s_init(const machine_t *);
extern int	machine_at_8500tuc_init(const machine_t *);
extern int	machine_at_m7shi_init(const machine_t *);
extern int	machine_at_tc430hx_init(const machine_t *);
extern int	machine_at_equium5200_init(const machine_t *);
extern int	machine_at_p65up5_cp55t2d_init(const machine_t *);

extern int	machine_at_p55tvp4_init(const machine_t *);
extern int	machine_at_p55va_init(const machine_t *);
extern int	machine_at_i430vx_init(const machine_t *);
extern int	machine_at_brio80xx_init(const machine_t *);
extern int	machine_at_8500tvxa_init(const machine_t *);
extern int	machine_at_pb680_init(const machine_t *);

extern int	machine_at_nupro592_init(const machine_t *);
extern int	machine_at_tx97_init(const machine_t *);
extern int	machine_at_ym430tx_init(const machine_t *);
extern int	machine_at_mb540n_init(const machine_t *);
extern int	machine_at_p5mms98_init(const machine_t *);

extern int	machine_at_ficva502_init(const machine_t *);

extern int	machine_at_ficpa2012_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*at_pb640_get_device(void);
#endif

/* m_at_super7_ss7.c */
extern int	machine_at_ax59pro_init(const machine_t *);
extern int	machine_at_mvp3_init(const machine_t *);

/* m_at_socket8.c */
extern int	machine_at_686nx_init(const machine_t *);
extern int	machine_at_v60n_init(const machine_t *);
extern int	machine_at_vs440fx_init(const machine_t *);
extern int	machine_at_gw2kvs_init(const machine_t *);
extern int	machine_at_ap440fx_init(const machine_t *);
extern int	machine_at_mb600n_init(const machine_t *);
extern int	machine_at_8500ttc_init(const machine_t *);
extern int	machine_at_m6mi_init(const machine_t *);
#ifdef EMU_DEVICE_H
extern void	machine_at_p65up5_common_init(const machine_t *, const device_t *northbridge);
#endif
extern int	machine_at_p65up5_cp6nd_init(const machine_t *);

/* m_at_slot1.c */
extern int	machine_at_p65up5_cpknd_init(const machine_t *);
extern int	machine_at_kn97_init(const machine_t *);

extern int	machine_at_lx6_init(const machine_t *);

extern int	machine_at_p6i440e2_init(const machine_t *);

extern int	machine_at_p2bls_init(const machine_t *);
extern int	machine_at_p3bf_init(const machine_t *);
extern int	machine_at_bf6_init(const machine_t *);
extern int	machine_at_ax6bc_init(const machine_t *);
extern int	machine_at_atc6310bxii_init(const machine_t *);
extern int	machine_at_tsunamiatx_init(const machine_t *);
extern int	machine_at_p6sba_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t 	*at_tsunamiatx_get_device(void);
#endif

/* m_at_slot2.c */
extern int	machine_at_6gxu_init(const machine_t *);
extern int	machine_at_s2dge_init(const machine_t *);

/* m_at_socket370.c */
extern int	machine_at_s370slm_init(const machine_t *);

extern int	machine_at_cubx_init(const machine_t *);
extern int	machine_at_atc7020bxii_init(const machine_t *);
extern int	machine_at_ambx133_init(const machine_t *);
extern int	machine_at_63a_init(const machine_t *);
extern int	machine_at_s370sba_init(const machine_t *);
extern int	machine_at_apas3_init(const machine_t *);

/* m_at_t3100e.c */
extern int	machine_at_t3100e_init(const machine_t *);

/* m_europc.c */
extern int	machine_europc_init(const machine_t *);
#ifdef EMU_DEVICE_H
extern const device_t europc_device;
#endif

/* m_oivetti_m24.c */
extern int	machine_olim24_init(const machine_t *);

/* m_pcjr.c */
extern int	machine_pcjr_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*pcjr_get_device(void);
#endif

/* m_ps1.c */
extern int	machine_ps1_m2011_init(const machine_t *);
extern int	machine_ps1_m2121_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_PS1M2133)
extern int	machine_ps1_m2133_init(const machine_t *);
#endif

/* m_ps1_hdc.c */
#ifdef EMU_DEVICE_H
extern void	ps1_hdc_inform(void *, uint8_t *);
extern const device_t ps1_hdc_device;
#endif

/* m_ps2_isa.c */
extern int	machine_ps2_m30_286_init(const machine_t *);

/* m_ps2_mca.c */
extern int	machine_ps2_model_50_init(const machine_t *);
extern int	machine_ps2_model_55sx_init(const machine_t *);
extern int	machine_ps2_model_70_type3_init(const machine_t *);
#if defined(DEV_BRANCH) && defined(USE_PS2M70T4)
extern int	machine_ps2_model_70_type4_init(const machine_t *);
#endif
extern int	machine_ps2_model_80_init(const machine_t *);

/* m_tandy.c */
extern int	tandy1k_eeprom_read(void);
extern int	machine_tandy_init(const machine_t *);
extern int	machine_tandy1000hx_init(const machine_t *);
extern int	machine_tandy1000sl2_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*tandy1k_get_device(void);
extern const device_t	*tandy1k_hx_get_device(void);
#endif

/* m_xt.c */
extern int	machine_pc_init(const machine_t *);
extern int	machine_pc82_init(const machine_t *);

extern int	machine_xt_init(const machine_t *);
extern int	machine_genxt_init(const machine_t *);

extern int	machine_xt86_init(const machine_t *);

extern int	machine_xt_amixt_init(const machine_t *);
extern int	machine_xt_dtk_init(const machine_t *);
extern int	machine_xt_jukopc_init(const machine_t *);
extern int	machine_xt_open_xt_init(const machine_t *);
extern int	machine_xt_pxxt_init(const machine_t *);

extern int  machine_xt_hed919_init(const machine_t *);

/* m_xt_compaq.c */
extern int	machine_xt_compaq_init(const machine_t *);

/* m_xt_laserxt.c */
#if defined(DEV_BRANCH) && defined(USE_LASERXT)
extern int	machine_xt_laserxt_init(const machine_t *);
extern int	machine_xt_lxt3_init(const machine_t *);
#endif

/* m_xt_t1000.c */
extern int	machine_xt_t1000_init(const machine_t *);
extern int	machine_xt_t1200_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*t1000_get_device(void);
extern const device_t	*t1200_get_device(void);
#endif

/* m_xt_zenith.c */
extern int	machine_xt_zenith_init(const machine_t *);

/* m_xt_xi8088.c */
extern int	machine_xt_xi8088_init(const machine_t *);

#ifdef EMU_DEVICE_H
extern const device_t	*xi8088_get_device(void);
#endif


#endif	/*EMU_MACHINE_H*/
