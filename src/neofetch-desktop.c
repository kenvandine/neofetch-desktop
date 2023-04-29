#include <gtk/gtk.h>
#include <vte/vte.h>

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
