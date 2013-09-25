/*
 * (C) Copyright 2010
 * Vipin Kumar, ST Micoelectronics, vipin.kumar@st.com.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/spr13xx_misc.h>
#include <asm/arch/ca9_ltimer.h>

/* Timer, HZ specific defines */
#define CONFIG_SYS_HZ				(1000000)
#define PRESCALER	PRESCALER_249
#define TIMER_TICKS	(CONFIG_SPEARCA9_HZ_CLK / (PRESCALER + 1))
#define TIMER_RES	(TIMER_TICKS / CONFIG_SYS_HZ)
#define READ_TIMER()	readl(&ca9_timer_p->count)

static struct ca9_timer_regs *const ca9_timer_p =
    (struct ca9_timer_regs *)CONFIG_SPEAR_CA9TMR_BASE;

static ulong timestamp;
static ulong lastdec;

void reset_timer(void);
void set_timer(ulong t);
ulong get_timer(ulong base);
void show_timer(char *s);

static void init_timer(void);
static void reset_timer_masked(void);
static ulong get_timer_masked(void);
static int timer_initialized = FALSE;

static void init_timer(void)
{
	if (timer_initialized == FALSE) {
		/* disable timers */
		writel((PRESCALER << 8) | AUTO_RELOAD, &ca9_timer_p->control);

		/* load value for free running */
		writel(FREE_RUNNING, &ca9_timer_p->load);

		/* auto reload, start timer */
		writel(readl(&ca9_timer_p->control) | TIMER_ENABLE,
				&ca9_timer_p->control);

		reset_timer_masked();

		timer_initialized = TRUE;
	}

}

/*
 * timer without interrupts
 */

void reset_timer(void)
{
	if (timer_initialized == FALSE) { init_timer(); }
	reset_timer_masked();
}

ulong get_timer(ulong base)
{
	if (timer_initialized == FALSE) { init_timer(); }
	return (get_timer_masked() / TIMER_RES) - base;
}

void set_timer(ulong t)
{
	if (timer_initialized == FALSE) { init_timer(); }
	timestamp = t;
}


static void reset_timer_masked(void)
{
	/* reset time */
	lastdec = READ_TIMER();
	timestamp = 0;
}

static ulong get_timer_masked(void)
{
	ulong now = READ_TIMER();

	if (now <= lastdec) {
		/* normal mode */
		timestamp += lastdec - now;
	} else {
		/* we have an overflow ... */
		timestamp += lastdec + FREE_RUNNING - now;
	}
	lastdec = now;

	return timestamp;
}

void show_timer(char *s)
{
	ulong t = get_timer(0);
	uartDebug_Puts(s);
	uartDebug_Puts(" time = ");
	uartDebug_Putdec((uint)t);
	uartDebug_Puts(" us \r\n");
}
