/* Asynchronous part of GSM Layer 1 */

/* (C) 2010 by Harald Welte <laforge@gnumonks.org>
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdint.h>

#include <debug.h>
#include <arm.h>

#include <osmocore/msgb.h>

#include <layer1/sync.h>
#include <layer1/async.h>
#include <layer1/mframe_sched.h>
#include <layer1/sched_gsmtime.h>
#include <layer1/l23_api.h>

extern const struct tdma_sched_item rach_sched_set_ul[];

/* safely enable a message into the L1S TX queue */
void l1a_txq_msgb_enq(struct llist_head *queue, struct msgb *msg)
{
	l1a_lock_sync();
	msgb_enqueue(queue, msg);
	l1a_unlock_sync();
}

/* Enable a repeating multiframe task */
void l1a_mftask_enable(enum mframe_task task)
{
	/* we don't need locking here as L1S only reads mframe.tasks */
	mframe_enable(task);
}

/* Disable a repeating multiframe task */
void l1a_mftask_disable(enum mframe_task task)
{
	/* we don't need locking here as L1S only reads mframe.tasks */
	mframe_disable(task);
}

/* Set the mask for repeating multiframe tasks */
void l1a_mftask_set(uint32_t tasks)
{
	/* we don't need locking here as L1S only reads mframe.tasks */
	mframe_set(tasks);
}

/* Initialize asynchronous part of Layer1 */
void l1a_init(void)
{
	l1a_l23api_init();
}
