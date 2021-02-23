/*
 *    Clear Linux Project for Intel Architecture Power tweaks
 *
 *   This program should do all the things that are hard in udev,
 *   that PowerTOP suggests should be changed from their kernel defaults
 *
 *      Copyright (C) 2012-2018 Intel Corporation
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, version 2 or later of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Authors:
 *         Arjan van de Ven <arjan@linux.intel.com>
 *
 */

#pragma once

/*
 * For settings, the `where` field should normally be '0' - assume server
 * If you need to specify a setting for desktop only, use '-1'.
 * For servers, prefer '0' but use '1' if there's a desktop-alternate value.
 * You shouldn't have 2 entries where '0' is used as a value for `where`.
 */

struct write_struct {
	char *pathglob;
	char *string;
	int where; // -1 client, 0 neutral (assume server), 1 server only
};

struct write_struct write_list[] = {
	{"/proc/sys/vm/dirty_ratio", "80", -1},
	{"/proc/sys/vm/dirty_background_ratio", "70", -1},
	{"/proc/sys/kernel/unprivileged_bpf_disabled", "1", -1},
	{"/proc/sys/vm/swappiness", "5", -1},
	{"/proc/sys/vm/dirty_writeback_centisecs", "30000", -1},
	{"/proc/sys/vm/dirty_expire_centisecs", "30000", -1},
	{"/proc/sys/fs/xfs/xfssyncd_centisecs", "30000", -1},
	{"/proc/sys/vm/vfs_cache_pressure", "50", -1},
	// {"/proc/sys/vm/min_free_kbytes", "336662", -1},
	{"/proc/sys/vm/min_free_kbytes", "262144", -1},
	{"/proc/sys/vm/vfs_cache_pressure", "50", -1},
	{"/proc/sys/fs/inotify/max_user_watches", "324288", -1},

	{"/sys/kernel/mm/transparent_hugepage/khugepaged/scan_sleep_millisecs", "30000", -1},
	{"/sys/devices/virtual/graphics/fbcon/cursor_blink", "0", -1},
	{"/sys/kernel/rcu_expedited", "0", -1},
	{"/proc/sys/vm/mmap_min_addr", "65536", -1},

// oom less
	{"/proc/sys/vm/extfrag_threshold", "100", -1},
	{"/sys/kernel/mm/ksm/sleep_millisecs", "4000", -1},

	{"/sys/kernel/mm/ksm/pages_to_scan", "1000", -1},
	{"/proc/sys/net/core/rmem_max", "1703936", -1},
	{"/proc/sys/net/core/wmem_max", "1703936", -1},
	{"/proc/sys/net/core/somaxconn", "4096", -1},
	{"/proc/sys/net/core/netdev_max_backlog", "5000", -1},
	{"/proc/sys/net/core/netdev_budget", "1000", -1},
	{"/proc/sys/net/core/netdev_budget_usecs", "5000", -1},
	{"/proc/sys/net/ipv4/tcp_fastopen", "3", -1},
	{"/proc/sys/net/ipv4/tcp_timestamps", "0", -1},
	{"/proc/sys/net/ipv4/tcp_mtu_probing", "1", -1},
	{"/proc/sys/net/ipv4/tcp_base_mss", "1024", -1},

	{"/proc/sys/kernel/sysrq", "1", -1},

// This tuneable decides the minimum time a task will be be allowed to
// run on CPU before being pre-empted out
	{"/proc/sys/kernel/sched_min_granularity_ns", "2250000", -1},
	{"/proc/sys/kernel/sched_migration_cost_ns", "50000", -1},
// Ability of tasks being woken to preempt the current task
	{"/proc/sys/kernel/sched_wakeup_granularity_ns", "15000000", -1},
    
    // sched_autogroup would improve interactive desktop performance in the face of
	// multi‐ process, CPU-intensive workloads. Whereas it would harm performance,
	// thus disable it on Server
    {"/proc/sys/kernel/sched_autogroup_enabled", "1", -1},

// audio pm
	{"/sys/module/snd_hda_intel/parameters/power_save", "0", -1},
	{"/sys/module/snd_hda_intel/parameters/power_save_controller", "0", -1},
// P state stuff
	{"/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor", "performance", -1},
// we want at least half performance, this helps us in race-to-halt and
// to give us reasonable responses
	{"/sys/devices/system/cpu/intel_pstate/min_perf_pct", "70", -1},
	{"/proc/sys/net/core/default_qdisc", "fq", -1},

// Disable acceptance of all ICMP redirected packets on all interfaces.
	{"/proc/sys/net/ipv4/conf/all/accept_redirects", "0", -1},
// 	{"/proc/sys/net/ipv6/conf/all/accept_redirects", "0", -1},
	{"/proc/sys/net/ipv4/conf/default/accept_redirects", "0", -1},
// 	{"/proc/sys/net/ipv6/conf/default/accept_redirects", "0", -1},

// Disables sending of all IPv4 ICMP redirected packets on all interfaces.
	{"/proc/sys/net/ipv4/conf/all/send_redirects", "0", -1},
	{"/proc/sys/net/ipv4/conf/default/send_redirects", "0", -1},

// Disables acceptance of secure ICMP redirected packets on all interfaces.
	{"/proc/sys/net/ipv4/conf/all/secure_redirects", "0", -1},
	{"/proc/sys/net/ipv4/conf/default/secure_redirects", "0", -1},

// SATA link power management
	{"/sys/class/scsi_host/*/link_power_management_policy", "max_performance", -1},

// Performance tuning for SATA and NVME storage
	{"/sys/block/nvme*/queue/scheduler", "bfq", -1},
	{"/sys/block/sd*/queue/scheduler", "bfq", -1},
	// {"/sys/block/loop*/queue/scheduler", "bfq", -1},

	{"/sys/block/nvme*/queue/write_cache", "write back", -1},
	{"/sys/block/sd*/queue/write_cache", "write back", -1},

	{"/sys/block/nvme*/queue/iosched/back_seek_penalty", "1", -1},
	{"/sys/block/sda/queue/iosched/back_seek_penalty", "3", -1},
	{"/sys/block/sdb/queue/iosched/back_seek_penalty", "3", -1},
	{"/sys/block/sdc/queue/iosched/back_seek_penalty", "3", -1},
	{"/sys/block/sdd/queue/iosched/back_seek_penalty", "3", -1},
	{"/sys/block/sde/queue/iosched/back_seek_penalty", "1", -1},

	{"/sys/block/nvme*/queue/iosched/low_latency", "1", -1},
	{"/sys/block/sda/queue/iosched/low_latency", "0", -1},
	{"/sys/block/sdb/queue/iosched/low_latency", "0", -1},
	{"/sys/block/sdc/queue/iosched/low_latency", "0", -1},
	{"/sys/block/sdd/queue/iosched/low_latency", "0", -1},
	{"/sys/block/sde/queue/iosched/low_latency", "1", -1},

	{"/sys/block/nvme*/queue/read_ahead_kb", "128", -1},
	{"/sys/block/sda/queue/read_ahead_kb", "1024", -1},
	{"/sys/block/sdb/queue/read_ahead_kb", "1024", -1},
	{"/sys/block/sdc/queue/read_ahead_kb", "1024", -1},
	{"/sys/block/sdd/queue/read_ahead_kb", "1024", -1},
	{"/sys/block/sde/queue/read_ahead_kb", "128", -1},

	// {"/sys/block/nvme0n1/queue/max_sectors_kb", "1280", -1},
	// {"/sys/block/nvme1n1/queue/max_sectors_kb", "1280", -1},
	// {"/sys/block/sda/queue/max_sectors_kb", "1024", -1},
	// {"/sys/block/sdb/queue/max_sectors_kb", "1024", -1},
	// {"/sys/block/sdc/queue/max_sectors_kb", "1024", -1},
	// {"/sys/block/sdd/queue/max_sectors_kb", "1024", -1},
	// {"/sys/block/sde/queue/max_sectors_kb", "1280", -1},

	{"/sys/block/nvme*/queue/nr_requests", "36", -1},
	{"/sys/block/sda/queue/nr_requests", "54", -1},
	{"/sys/block/sdb/queue/nr_requests", "54", -1},
	{"/sys/block/sdc/queue/nr_requests", "54", -1},
	{"/sys/block/sdd/queue/nr_requests", "54", -1},
	{"/sys/block/sde/queue/nr_requests", "36", -1},

	{"/sys/block/nvme0n1/queue/iosched/timeout_sync", "30", -1},
	{"/sys/block/nvme1n1/queue/iosched/timeout_sync", "125", -1},
	{"/sys/block/sd*/queue/iosched/timeout_sync", "200", -1},
	{"/sys/block/sd*/queue/iosched/timeout_sync", "200", -1},
	{"/sys/block/sd*/queue/iosched/timeout_sync", "200", -1},
	{"/sys/block/sd*/queue/iosched/timeout_sync", "200", -1},
	{"/sys/block/sd*/queue/iosched/timeout_sync", "125", -1},

	{"/sys/block/nvme*/queue/iosched/fifo_expire_sync", "125", -1},
	{"/sys/block/sd*/queue/iosched/fifo_expire_sync", "263", -1},

	{"/sys/block/nvme*/queue/iosched/fifo_expire_async", "250", -1},
	{"/sys/block/sd*/queue/iosched/fifo_expire_async", "253", -1},

	// {"/sys/block/nvme0n1/queue/iosched/back_seek_max", "268435456", -1},
	// {"/sys/block/nvme1n1/queue/iosched/back_seek_max", "16777216", -1},
	// {"/sys/block/sda/queue/iosched/back_seek_max", "16384", -1},
	// {"/sys/block/sdb/queue/iosched/back_seek_max", "16384", -1},
	// {"/sys/block/sdc/queue/iosched/back_seek_max", "16384", -1},
	// {"/sys/block/sdd/queue/iosched/back_seek_max", "16384", -1},
	// {"/sys/block/sde/queue/iosched/back_seek_max", "125829120", -1},

	{"/sys/block/nvme*/queue/iosched/slice_idle", "0", -1},
	{"/sys/block/sd*/queue/iosched/slice_idle", "0", -1},
    
	{"/sys/block/nvme*/queue/iosched/slice_idle_us", "16", -1},
	{"/sys/block/sda/queue/iosched/slice_idle_us", "5300", -1},
	{"/sys/block/sdb/queue/iosched/slice_idle_us", "5300", -1},
	{"/sys/block/sdc/queue/iosched/slice_idle_us", "5300", -1},
	{"/sys/block/sdd/queue/iosched/slice_idle_us", "5300", -1},
	{"/sys/block/sde/queue/iosched/slice_idle_us", "16", -1},

	{"/sys/block/nvme*/queue/add_random", "0", -1},
	{"/sys/block/sda/queue/add_random", "0", -1},
	{"/sys/block/sdb/queue/add_random", "0", -1},
	{"/sys/block/sdc/queue/add_random", "0", -1},
	{"/sys/block/sdd/queue/add_random", "0", -1},
	{"/sys/block/sde/queue/add_random", "0", -1},

	{"/sys/block/bcache0/bcache/cache_mode", "writeback", -1},
	{"/sys/block/bcache0/queue/read_ahead_kb", "512", -1},
	{"/sys/block/bcache0/bcache/writeback_delay", "300", -1},
	{"/sys/block/bcache0/bcache/sequential_cutoff", "8388608", -1},
	{"/sys/block/bcache0/bcache/writeback_percent", "40", -1},
	{"/sys/fs/bcache/755950e5-4570-40bd-8fa7-1c663270dbca/congested_read_threshold_us", "0", -1},
	{"/sys/fs/bcache/755950e5-4570-40bd-8fa7-1c663270dbca/congested_write_threshold_us", "0", -1},

// Enable turbo mode max
// {"/proc/sys/kernel/sched_itmt_enabled", "1", -1},

// Reload the microcode at boot
	{"/sys/devices/system/cpu/microcode/reload", "0", -1},
	
	{"/proc/sys/kernel/nmi_watchdog", "0", -1},
	
	
	// End of list.
	{NULL, NULL, 0}
};
