#include <glib-2.0/glib/garray.h>

#include "launcher.h"

GArray *command_list;
int command_count;

gint cmp_func(gconstpointer a, gconstpointer b) {
    return strcasecmp(((cmd_descr*) a)->name, ((cmd_descr*) b)->name);
}

int list_commands(char * config) {
    cmd_descr cmd;
    char buf[sizeof cmd];
    FILE * f = fopen(config, "rt");
    if (f == 0) {
        error(1, 0, "Can not open file: %s", config);
        return 3;
    }
    int line = 0;
    char format[32];
    sprintf(format, "%%%is %%%i[^\t] %%%i[^\n]", (int) (sizeof (cmd.shortcut) - 1),
            (int) (sizeof (cmd.name) - 1), (int) (sizeof (cmd.command) - 1));
    command_count = 0;
    command_list = g_array_new(FALSE, FALSE, sizeof (cmd_descr));
    while (++line, fgets(buf, sizeof buf, f)) {
        if (buf[0] == '\n' || buf[0] == '#')continue;
        if (sscanf(buf, format, cmd.shortcut, cmd.name, cmd.command) == 3) {
            g_array_append_val(command_list, cmd);
            ++command_count;
        } else error(1, 0, "Error in line %i", line);
    }
    g_array_sort(command_list, cmp_func);
    return 0;
}

int cmd_count() {
    return command_count;
}

cmd_descr * nth_command(int n) {
    return n >= 0 && n < cmd_count() ? &g_array_index(command_list, cmd_descr, n) : 0;
}

