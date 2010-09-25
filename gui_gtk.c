#include "launcher.h"

typedef struct {
    GtkWidget *shortcut_label, *name_label;
} entry;

entry *labels;

gboolean key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    //puts(event->string);
    if (event->keyval == GDK_Escape)gtk_main_quit();
    else {
        int i;
        for (i = 0; i < cmd_count(); i++)
            if (strlen(event->string) > 0 &&
                    strcmp(event->string, nth_command(i)->shortcut) == 0) break;
        if (i < cmd_count()) {
            run_command(nth_command(i)->command);
            gtk_main_quit();
        }
    }
    return TRUE;
}

gboolean destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
    return TRUE;
}

gboolean timer_exit(gpointer data) {
    gtk_main_quit();
    return FALSE;
}

PangoAttrList *letter_label_attr_list;

void init_attr_list() {
    letter_label_attr_list = pango_attr_list_new();
    PangoAttribute *fcolor = pango_attr_foreground_new(0xffff, 0, 0);
    pango_attr_list_insert(letter_label_attr_list, fcolor);
}

void create_labels(cmd_descr *cmd, entry *en) {
    en->shortcut_label = gtk_label_new(cmd->shortcut);
    gtk_label_set_attributes(GTK_LABEL(en->shortcut_label), letter_label_attr_list);
    en->name_label = gtk_label_new(cmd->name);
}

int show_gui(int *argc, char ***argv) {
    gtk_init(argc, argv);
    init_attr_list();
    GtkWidget *wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(wnd), "AppLauncher");
    g_signal_connect(wnd, "destroy", G_CALLBACK(destroy), 0);
    GtkTable *table = GTK_TABLE(gtk_table_new(cmd_count(), 2, FALSE));
    gtk_container_add(GTK_CONTAINER(wnd), GTK_WIDGET(table));
    labels = malloc(cmd_count() * sizeof (entry));
    for (int i = 0; i < cmd_count(); i++) {
        create_labels(nth_command(i), labels + i);
        gtk_table_attach(table, labels[i].shortcut_label, 0, 1, i, i + 1,
                GTK_EXPAND, GTK_EXPAND, 2, 0);
        gtk_table_attach(table, labels[i].name_label, 1, 2, i, i + 1,
                GTK_EXPAND, GTK_EXPAND, 2, 0);
    }
    g_signal_connect(wnd, "key-press-event", G_CALLBACK(key_pressed), 0);
    gtk_window_position(GTK_WINDOW(wnd), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(wnd);
    if (get_time() > 0) g_timeout_add_seconds(get_time(), timer_exit, 0);
    gtk_main();
    free(labels);
    return 0;
}

