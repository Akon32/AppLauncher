/* 
 * File:   launcher.h
 * Author: akon
 *
 * Created on 6 Июнь 2010 г., 19:34
 */

#ifndef _LAUNCHER_H
#define	_LAUNCHER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define __USE_BSD
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <error.h>
#include <assert.h>
#include <gdk/gdkkeysyms.h>

#define SHORTCUT_LEN 8
#define NAME_LEN 64
#define COMMAND_LEN (1024-NAME_LEN-SHORTCUT_LEN)

    typedef struct {
        char shortcut[SHORTCUT_LEN];
        char name[NAME_LEN];
        char command[COMMAND_LEN];
    } cmd_descr;

    int parse_options(int argc, char ** argv);
    char * get_config_file(void);
    int get_time(void);

    int list_commands(char * dir);
    int cmd_count(void);
    cmd_descr *nth_command(int n);

    int show_gui(int *, char***);

    int run_command(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* _LAUNCHER_H */

