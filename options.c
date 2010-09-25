#include "launcher.h"

char * config_name;
int timeout = 16;

char * default_file(void) {
    char *home = getenv("HOME");
    if (!home)return 0;
    char def[] = "/.applauncher.list";
    char *d = malloc(strlen(home) + sizeof def);
    strcpy(d, home);
    strcat(d, def);
    return d;
}

int parse_options(int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--config") == 0 || strcmp(argv[i], "-c") == 0) {
            if (++i < argc)
                config_name = argv[i];
            else {
                error(1, 0, "Configuration file name required after %s", argv[i - 1]);
                return 1;
            }
        } else if (strcmp(argv[i], "--timeout") == 0 || strcmp(argv[i], "-t") == 0) {
            ++i;
            if (i < argc && sscanf(argv[i], " %i", &timeout) == 1 && time > 0);
            else {
                error(1, 0, "Timeout value (positive number) required after %s",
                        argv[i - 1]);
                return 2;
            }
        } else {
            error(1, 0, "Unknown key: %s", argv[i]);
            return 3;
        }
    }
    if (config_name == 0 && (config_name = default_file()) == 0) {
        error(1, 0, "Scripts file has not been setted");
        return 6;
    }
    return 0;
}

char * get_config_file(void) {
    return config_name;
}

int get_time(void) {
    return timeout;
}

