// include/emerging_sys.h
// Emerging System Library
// Version 3.0

#ifndef EMERGING_SYS_H
#define EMERGING_SYS_H

#include "emerging.h"

// 端口操作宏
#define inb(p)         em_inb(p)
#define outb(p,v)      em_outb(p,v)
#define inw(p)         em_inw(p)
#define outw(p,v)      em_outw(p,v)
#define inl(p)         em_inl(p)
#define outl(p,v)      em_outl(p,v)

// 系统调用宏
#define halt()         em_system_halt()
#define reboot()       em_system_reboot()
#define shutdown()     em_system_shutdown()
#define beep(f,d)      em_system_beep(f,d)

// 定时器宏
#define timer_ticks()  em_timer_get_ticks()
#define sleep(ms)      em_timer_sleep(ms)

#endif // EMERGING_SYS_H