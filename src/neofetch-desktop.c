#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <vte/vte.h>
#include "rgba.h"

static void spawn_child_process (VteTerminal *terminal) {
    char *command_argv[2] = { "neofetch\0", NULL };

    vte_terminal_spawn_async (
        VTE_TERMINAL (terminal),
	VTE_PTY_NO_HELPER,
	NULL,
	command_argv,
	NULL,
	G_SPAWN_SEARCH_PATH,
	NULL,
	NULL,
	NULL,
	2000,
	NULL,
	NULL,
	NULL
    );
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *terminal;

    // Create a new window
    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW (window), "Neofetch Desktop");

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
    gtk_window_set_child (GTK_WINDOW (window), box);    

    // Create a new VTE terminal widget
    terminal = vte_terminal_new ();

    GdkRGBA fgcolor;
    GdkRGBA bgcolor;
    fgcolor = (GdkRGBA) { 1.0, 1.0, 1.0, 1.0}; // White
    bgcolor = (GdkRGBA) { 0.17, 0.0, 0.11, 1.0 }; // Aubergine

    // Workings of GDK_RGBA prevent this being static
    GdkRGBA palette[16] = {
      GDK_RGBA ("2c001e"), // Aubergine
      GDK_RGBA ("c01c28"), // Red
      GDK_RGBA ("2ec27e"), // Green
      GDK_RGBA ("f5c211"), // Yellow
      GDK_RGBA ("1e78e4"), // Blue
      GDK_RGBA ("9841bb"), // Magenta
      GDK_RGBA ("0ab9dc"), // Cyan
      GDK_RGBA ("c0bfbc"), // White
      GDK_RGBA ("5e5c64"), // Bright Black
      GDK_RGBA ("ed333b"), // Bright Red
      GDK_RGBA ("57e389"), // Bright Green
      GDK_RGBA ("f8e45c"), // Bright Yellow
      GDK_RGBA ("51a1ff"), // Bright Blue
      GDK_RGBA ("c061cb"), // Bright Magenta
      GDK_RGBA ("4fd2fd"), // Bright Cyan
      GDK_RGBA ("f6f5f4"), // Bright White
    };

    // Set the foreground and background colors
    vte_terminal_set_colors (VTE_TERMINAL (terminal), &fgcolor, &bgcolor, &palette, 16);

    // Disable cursor blink
    vte_terminal_set_cursor_blink_mode (VTE_TERMINAL (terminal), VTE_CURSOR_BLINK_OFF);

    gtk_widget_set_vexpand (terminal, TRUE);
    gtk_widget_set_hexpand (terminal, TRUE);
    gtk_box_append (GTK_BOX (box), terminal);
    spawn_child_process (VTE_TERMINAL (terminal));

    // Show the window
    gtk_window_present (GTK_WINDOW (window));

    // Disable window resize
    gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
}

int main (int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    // Create a new GTK application
    app = gtk_application_new ("org.vandine.ken.neofetch", G_APPLICATION_DEFAULT_FLAGS);

    // Connect the activate function to the activate signal
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

    // Run the GTK application
    status = g_application_run (G_APPLICATION (app), argc, argv);

    // Clean up the application
    g_object_unref (app);

    return status;
}
