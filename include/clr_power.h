#ifndef __INCLUDE_GUARD_CLR_POWER_H__
#define __INCLUDE_GUARD_CLR_POWER_H__

extern void write_string_to_file(const char *filename, const char *string);
extern void do_pci_pm(void);
extern void do_WOL(void);
extern void do_usb_pm(void);
extern void do_gfx_pm(void);
#endif
