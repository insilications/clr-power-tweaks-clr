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
 *   the Free Software Foundation, version 3 of the License.
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

#define _GNU_SOURCE

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <argp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <clr_power.h>
#include <sys/utsname.h>

#include "data.h"

#define _free(_ptr) rfree((_ptr))

void * rfree (void *ptr)
{
    free(ptr);
    return NULL;
}

const char *argp_program_version = "Clear Linux Project for Intel Architecture Power Tweaks v" VERSION;

const char *argp_program_bug_address = PACKAGE_BUGREPORT;

const char doc[] = "Power Tweaks -- adjusts runtime kernel options for optimal power and performance";

const char args_doc[] = "";

static struct argp_option options[] = {
	{ "debug", 'd', 0, OPTION_ARG_OPTIONAL, "Display debug/verbose output" },
	{ "server", 'S', 0, OPTION_ARG_OPTIONAL, "Treat system as a server platform" },
	{ "desktop", 'D', 0, OPTION_ARG_OPTIONAL, "Treat system as a desktop platform" },
	{ 0 },
};

struct arguments
{
	char *args[1];
	bool debug;
	int server_desktop;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key) {
	case 'd':
		arguments->debug = true;
		break;
	case 'S':
		arguments->server_desktop = 1;
		break;
	case 'D':
		arguments->server_desktop = -1;
		break;
	case ARGP_KEY_ARG:
		if (state->arg_num > 0)
			argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

static int get_kernel_version(void)
{
    struct utsname version;
    char *p;
    int r;

    uname(&version);
    p = version.release - 1;
    r = 1;
    do {
        r <<= 8;
        if (p) {
            r += atoi(++p);
            p = strchr(p, '.');
        }
    } while (r < 0x1000000);
    return r - 0x1000000;
}

static void _wrmsr(const char *addr, const char *argm)
{
    FILE *fpLDD = NULL;
    char *wrmsrCMD = NULL;
    asprintf(&wrmsrCMD, "sudo wrmsr %s %s", addr, argm);
    printf("wrmsrCMD: %s\n", wrmsrCMD);
    fpLDD = popen(wrmsrCMD, "r");
    wrmsrCMD = _free(wrmsrCMD);
    int status = pclose(fpLDD);
    if (fpLDD != NULL && status != -1) {
        printf("wrmsrCMD: successful\n");
    } else {
        printf("wrmsrCMD: failed\n");
    }
}

int main(int argc, char **argv)
{
	struct arguments arguments;
	int status = 0;
	// int system_is_server;

	arguments.debug = false;
	// arguments.server_desktop = is_server();
	arguments.server_desktop = -1;

	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	lib_init(arguments.debug);

	/* system tweaks */
	// for (int i = 0; write_list[i].pathglob != 0; i++) {
	// 	/*
	// 	 * If it's a server, or we don't know, apply generic settings as well as server ones.
	// 	 * If it's a desktop, apply only desktop settings
	// 	 */
	// 	if (((arguments.server_desktop >= 0) && (write_list[i].where >= 0)) ||
	// 	    ((arguments.server_desktop == -1) && (write_list[i].where <= 0))) {
	// 		status |= write_string_to_files(write_list[i].pathglob,
	// 				write_list[i].string);
	// 	}
	// }

//	usleep(150000);

	// Maximum turbo limit 01/02/03/04/05/06/07/08/09/10
	// Maximum turbo limit 53/53/51/51/51/50/50/49/49/49
	// sudo wrmsr 0x1AD 0x3132323333333535
	// sudo wrmsr 0x1AE 0x3131
	// _wrmsr("0x1AE", "0x3131");
	_wrmsr("0x1AD", "0x3132323333333535");

	/* USB autosuspend for non-HID */

	/* Runtime PM for PCI */
	do_usb_pm();

	/* turn off Wake-on-Lan */
	do_WOL();

	do_pci_pm();
	do_gfx_pm();
	// do_cpu_pm();
	verify_time();

	/* user tweaks or overrides */
	// FILE *f = fopen("/etc/clr-power-tweaks.conf", "r");
	// if (f) {
	// 	for (;;) {
	// 		char match[PATH_MAX];
	// 		char value[PATH_MAX];
	// 		char line[PATH_MAX];
	// 		int ret;
 //
	// 		if (fgets(line, PATH_MAX, f) == NULL)
	// 			break;
 //
	// 		ret = sscanf(line, "%s %s", match, value);
	// 		if (ret >= 1) {
	// 			/* comment */
	// 			if ((strlen(match) > 0) && (match[0] == '#')) {
	// 				continue;
	// 			};
	// 		};
	// 		if (ret == 1) {
	// 			if (arguments.debug)
	// 				fprintf(stderr, "Adding \"%s\" to exclusion list\n", match);
	// 			string_exclude(match);
	// 		};
	// 		if (ret == 2) {
	// 			write_string_to_files(match, value);
	// 			string_exclude(match);
	// 		}
	// 	}
	// 	fclose(f);
	// }

	/* system tweaks */
	for (int i = 0; write_list[i].pathglob != 0; i++) {
		/*
		 * If it's a server, or we don't know, apply generic settings as well as server ones.
		 * If it's a desktop, apply only desktop settings
		 */
		if (((arguments.server_desktop >= 0) && (write_list[i].where >= 0) &&
			(get_kernel_version() >= write_list[i].min_kernel_version) &&
			(get_kernel_version() < write_list[i].max_kernel_version)) ||
			((arguments.server_desktop == -1) && (write_list[i].where <= 0) &&
			(get_kernel_version() >= write_list[i].min_kernel_version) &&
			(get_kernel_version() < write_list[i].max_kernel_version))) {
			status |= write_string_to_files(write_list[i].pathglob, write_list[i].string);
		}
	}

	/* do zero pages will loop and do work every 5 seconds, so it must be last */
	//	do_zero_pages();
	// return EXIT_SUCCESS;
	return status;
}
