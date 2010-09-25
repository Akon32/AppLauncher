/* 
 * File:   main.c
 * Author: akon
 *
 * Created on 4 Июнь 2010 г., 9:26
 */

#include "launcher.h"

int run_command(char * cmd) {
    execl("/bin/sh", "sh", "-c", cmd, 0);
    error(1, errno, "Can not run command: %s", cmd);
}

int main(int argc, char** argv) {
    return parse_options(argc, argv) ||
            list_commands(get_config_file()) || show_gui(&argc, &argv);
}

