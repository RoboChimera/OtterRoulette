#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

int square = 25;
int x;
int y;
int buttonsKilled;

void buttonClick(GtkWidget *button, gpointer data) {
	int number = GPOINTER_TO_INT(data) + 1;
	int kill = rand() % 25;

	if (number == kill) {
		g_print("\n You lost!");
		gtk_main_quit();
	} else {
		g_print("\n Button: %i, %i", number, kill);
		gtk_widget_destroy(button);
		buttonsKilled++;

		if (buttonsKilled == 25) {
			g_print("\n You won!");
			gtk_main_quit();
		}
	}
}

int main(int argc, char *argv[]) {
	GtkWidget *window, *grid;
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "OtterRoulette");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	for (int i = 0; i < square; i++) {
		GtkWidget *button;
		button = gtk_button_new_with_label("O");
		g_signal_connect(button, "clicked", G_CALLBACK(buttonClick), GPOINTER_TO_INT(i));
		gtk_grid_attach(GTK_GRID(grid), button, x, y, 1, 1);
		if (x / 4) {
			y++;
			x = 0;
		} else {
			x++;
		}
	}

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
