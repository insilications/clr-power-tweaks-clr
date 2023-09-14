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
#include <stdlib.h>
#include <limits.h>
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define MAX_VERSION INT_MAX
#define MIN_VERSION 0

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
	int min_kernel_version;
	int max_kernel_version;
};

struct write_struct write_list[] = {
{"/proc/sys/vm/dirty_ratio", "95", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/dirty_background_ratio", "60", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/randomize_va_space", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/swappiness", "9", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/dirty_writeback_centisecs", "40000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/dirty_expire_centisecs", "40000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/fs/xfs/xfssyncd_centisecs", "40000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/fs/xfs/filestream_centisecs", "20000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/min_free_kbytes", "342000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/vfs_cache_pressure", "20", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/fs/inotify/max_user_watches", "524288", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/fs/file-max", "4194303", -1, MIN_VERSION, MAX_VERSION},

{"/sys/kernel/mm/transparent_hugepage/defrag", "madvise", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/transparent_hugepage/enabled", "always", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/transparent_hugepage/shmem_enabled", "advise", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/transparent_hugepage/khugepaged/scan_sleep_millisecs", "30000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/virtual/graphics/fbcon/cursor_blink", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/rcu_expedited", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/mmap_min_addr", "65536", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/overcommit_memory", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/unprivileged_bpf_disabled", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/msgmax", "65535", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/msgmnb", "65535", -1, MIN_VERSION, MAX_VERSION},


{"/sys/devices/system/clocksource/clocksource0/current_clocksource", "tsc", -1, MIN_VERSION, MAX_VERSION},


// oom less
// {"/sys/kernel/mm/lru_gen/enabled", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/vm/extfrag_threshold", "100", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/kernel/mm/uksm/run", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/kernel/mm/uksm/sleep_millisecs", "8000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/ksm/run", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/ksm/sleep_millisecs", "18000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/kernel/mm/ksm/pages_to_scan", "1000", -1, MIN_VERSION, MAX_VERSION},


// This tuneable decides the minimum time a task will be be allowed to
// run on CPU before being pre-empted out
// 5.13.x
{"/sys/kernel/debug/sched/min_granularity_ns", "2250000", -1, KERNEL_VERSION(5,13,0), MAX_VERSION},
{"/sys/kernel/debug/sched/migration_cost_ns", "50000", -1, KERNEL_VERSION(5,13,0), MAX_VERSION},
// Number of tasks to iterate in a single balance run.
// Limited because this is done with IRQs disabled.
{"/sys/kernel/debug/sched/nr_migrate", "256", -1, KERNEL_VERSION(5,13,0), MAX_VERSION},
// Ability of tasks being woken to preempt the current task
{"/sys/kernel/debug/sched/wakeup_granularity_ns", "15000000", -1, KERNEL_VERSION(5,13,0), MAX_VERSION},
// 5.x.x
{"/proc/sys/kernel/sched_min_granularity_ns", "2250000", -1, MIN_VERSION, KERNEL_VERSION(5,13,0)},
{"/proc/sys/kernel/sched_migration_cost_ns", "50000", -1, MIN_VERSION, KERNEL_VERSION(5,13,0)},
// Ability of tasks being woken to preempt the current task
{"/proc/sys/kernel/sched_wakeup_granularity_ns", "15000000", -1, MIN_VERSION, KERNEL_VERSION(5,13,0)},

{"/proc/sys/kernel/sched_rt_runtime_us", "980000", -1, MIN_VERSION, MAX_VERSION},

// sched_autogroup would improve interactive desktop performance in the face of
// multi‐ process, CPU-intensive workloads. Whereas it would harm performance,
// thus disable it on Server
{"/proc/sys/kernel/sched_autogroup_enabled", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/sched_energy_aware", "0", -1, MIN_VERSION, MAX_VERSION},

// P state stuff
{"/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu5/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu6/cpufreq/scaling_max_freq", "5300000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu7/cpufreq/scaling_max_freq", "5300000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu8/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu9/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu10/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu11/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu12/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu13/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu14/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu15/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu16/cpufreq/scaling_max_freq", "5300000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu17/cpufreq/scaling_max_freq", "5300000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu18/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu19/cpufreq/scaling_max_freq", "5100000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq", "3700000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu*/power/energy_perf_bias", "performance", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu*/power/energy_perf_bias", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor", "performance", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/cpu*/cpufreq/energy_performance_preference", "performance", -1, MIN_VERSION, MAX_VERSION},

// SPR uncore
// {"/sys/devices/system/cpu/intel_uncore_frequency/package_00_die_00/max_freq_khz", "2300000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/devices/system/cpu/intel_uncore_frequency/package_01_die_00/max_freq_khz", "2300000", -1, MIN_VERSION, MAX_VERSION},

// we want at least half performance, this helps us in race-to-halt and
// to give us reasonable responses
{"/sys/devices/system/cpu/intel_pstate/min_perf_pct", "60", -1, MIN_VERSION, MAX_VERSION},
{"/sys/devices/system/cpu/intel_pstate/hwp_dynamic_boost", "1", -1, MIN_VERSION, MAX_VERSION},


// Disable acceptance of all ICMP redirected packets on all interfaces.
{"/proc/sys/net/ipv4/conf/all/accept_redirects", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/proc/sys/net/ipv6/conf/all/accept_redirects", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/conf/default/accept_redirects", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/proc/sys/net/ipv6/conf/default/accept_redirects", "0", -1, MIN_VERSION, MAX_VERSION},

// Disables sending of all IPv4 ICMP redirected packets on all interfaces.
{"/proc/sys/net/ipv4/conf/all/send_redirects", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/conf/default/send_redirects", "0", -1, MIN_VERSION, MAX_VERSION},

// Disables acceptance of secure ICMP redirected packets on all interfaces.
{"/proc/sys/net/ipv4/conf/all/secure_redirects", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/conf/default/secure_redirects", "0", -1, MIN_VERSION, MAX_VERSION},

{"/proc/sys/net/ipv4/conf/all/accept_source_route", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/conf/default/accept_source_route", "0", -1, MIN_VERSION, MAX_VERSION},

// net misc
{"/proc/sys/net/core/rmem_default", "10485760", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/wmem_default", "10485760", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/rmem_max", "16777216", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/wmem_max", "16777216", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/somaxconn", "8192", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/netdev_max_backlog", "5000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/netdev_budget", "1000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/netdev_budget_usecs", "5000", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_wmem", "4096 12582912 16777216", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_rmem", "4096 12582912 16777216", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_max_syn_backlog", "8096", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_max_tw_buckets", "231072", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_slow_start_after_idle", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_tw_reuse", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_fastopen", "3", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_timestamps", "0", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_mtu_probing", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_base_mss", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_fin_timeout", "5", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/udp_rmem_min", "8192", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/udp_wmem_min", "8192", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/high_order_alloc_disable", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/core/default_qdisc", "fq", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_congestion_control", "bbr2", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_ecn", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_ecn_fallback", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/net/ipv4/tcp_window_scaling", "1", -1, MIN_VERSION, MAX_VERSION},


// SATA link power management
{"/sys/class/scsi_host/*/link_power_management_policy", "max_performance", -1, MIN_VERSION, MAX_VERSION},
{"/sys/bus/pci/devices/*/power/control", "on", -1, MIN_VERSION, MAX_VERSION},

// USB link power management
{"/sys/bus/usb/devices/*/power/control", "on", -1, MIN_VERSION, MAX_VERSION},



// audio pm
{"/sys/module/snd_hda_intel/parameters/power_save", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/module/snd_hda_intel/parameters/power_save_controller", "0", -1, MIN_VERSION, MAX_VERSION},




// Performance tuning for SATA and NVME storage
{"/sys/block/nvme0n1/queue/scheduler", "none", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/scheduler", "none", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/scheduler", "none", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/scheduler", "bfq", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/scheduler", "bfq", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/scheduler", "bfq", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/scheduler", "bfq", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/scheduler", "bfq", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/loop*/queue/scheduler", "none", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/back_seek_penalty", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/back_seek_penalty", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/back_seek_penalty", "3", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/back_seek_penalty", "3", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/back_seek_penalty", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/back_seek_penalty", "3", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/back_seek_penalty", "3", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/back_seek_penalty", "1", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/loop*/queue/read_ahead_kb", "4096", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/rotational", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/rotational", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/rotational", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/rotational", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/loop*/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/max_sectors_kb", "512", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/max_sectors_kb", "2048", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sda/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdc/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/nr_requests", "2048", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/nr_requests", "2048", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/nr_requests", "2048", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/timeout_sync", "38", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/timeout_sync", "38", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/timeout_sync", "200", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/timeout_sync", "132", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/timeout_sync", "10", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/timeout_sync", "200", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/timeout_sync", "132", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/timeout_sync", "38", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/strict_guarantees", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/strict_guarantees", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/strict_guarantees", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/strict_guarantees", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/strict_guarantees", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/strict_guarantees", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/strict_guarantees", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/strict_guarantees", "0", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/fifo_expire_sync", "83", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/fifo_expire_sync", "83", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/fifo_expire_sync", "80", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/fifo_expire_sync", "263", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/fifo_expire_sync", "10", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/fifo_expire_sync", "80", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/fifo_expire_sync", "263", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/fifo_expire_sync", "83", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/fifo_expire_async", "167", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/fifo_expire_async", "167", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/fifo_expire_async", "1000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/fifo_expire_async", "353", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/fifo_expire_async", "250", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/fifo_expire_async", "1000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/fifo_expire_async", "353", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/fifo_expire_async", "167", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/back_seek_max", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},

// {"/sys/block/nvme0n1/queue/iosched/slice_idle_us", "16", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/nvme1n1/queue/iosched/slice_idle_us", "16", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/iosched/slice_idle_us", "3000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/iosched/slice_idle_us", "3000", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/iosched/slice_idle_us", "16", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/iosched/slice_idle_us", "3000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/iosched/slice_idle_us", "3000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/iosched/slice_idle_us", "16", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/nomerges", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/queue/nomerges", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/nomerges", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/nomerges", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/nvme0n1/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme1n1/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/nvme2n1/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sda/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},

{"/sys/block/sda/device/queue_depth", "32", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdb/device/queue_depth", "32", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdb/device/queue_depth", "32", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/sdc/device/queue_depth", "32", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sdd/device/queue_depth", "32", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/sde/device/queue_depth", "256", -1, MIN_VERSION, MAX_VERSION},



{"/sys/block/bcache0/queue/scheduler", "none", -1, MIN_VERSION, MAX_VERSION},
//
{"/sys/block/bcache0/queue/write_cache", "write back", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/read_ahead_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/max_sectors_kb", "1024", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/nr_requests", "4096", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/back_seek_penalty", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/low_latency", "1", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/timeout_sync", "37", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/strict_guarantees", "0", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/fifo_expire_sync", "83", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/fifo_expire_async", "167", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/back_seek_max", "32000", -1, MIN_VERSION, MAX_VERSION},
// {"/sys/block/bcache0/queue/iosched/slice_idle_us", "16", -1, MIN_VERSION, MAX_VERSION},
//
{"/sys/block/bcache0/queue/rotational", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/add_random", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/rq_affinity", "2", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/nomerges", "1", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/io_poll", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/queue/io_poll_delay", "-1", -1, MIN_VERSION, MAX_VERSION},
//
{"/sys/block/bcache0/bcache/cache_mode", "writeback", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/bcache/writeback_delay", "400", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/bcache/sequential_cutoff", "134217728", -1, MIN_VERSION, MAX_VERSION},
{"/sys/block/bcache0/bcache/writeback_percent", "40", -1, MIN_VERSION, MAX_VERSION},
{"/sys/fs/bcache/7032f90c-f15f-4d71-8218-3bb9caad28c5/congested_read_threshold_us", "0", -1, MIN_VERSION, MAX_VERSION},
{"/sys/fs/bcache/7032f90c-f15f-4d71-8218-3bb9caad28c5/congested_write_threshold_us", "0", -1, MIN_VERSION, MAX_VERSION},

// Reload the microcode at boot
{"/sys/devices/system/cpu/microcode/reload", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/sysrq", "1", -1, MIN_VERSION, MAX_VERSION},
{"/proc/sys/kernel/nmi_watchdog", "0", -1, MIN_VERSION, MAX_VERSION},

// Disable coredump
{"/proc/sys/kernel/core_pattern", "|/bin/false", -1, MIN_VERSION, MAX_VERSION},
// Enable turbo mode max
{"/proc/sys/kernel/sched_itmt_enabled", "1", -1, MIN_VERSION, MAX_VERSION},
{NULL, NULL, 0, 0, 0}
};
