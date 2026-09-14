#include <gtk/gtk.h>

typedef struct {
    int row;
    int column;
    bool pressed;
    char value;
}ButtonData;

static bool IsGameWon;
static GtkWidget *WinButton;
static GtkWidget *grid;
static void XWon(void) {
    gtk_button_set_label(GTK_BUTTON(WinButton), "X Won! Press to restart!");
    IsGameWon = true;
}

static void OWon(void) {
    gtk_button_set_label(GTK_BUTTON(WinButton), "0 Won! Press to restart!");
    IsGameWon = true;
}

static char toegrid[3][3];
static int k = 0;
//static ButtonData data;
static void reset_event(GtkWidget *widget, gpointer user_data) {
    GtkWidget* button;
    int i = 0;
    int j = 0;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            toegrid[i][j] = '\0';
            button = gtk_grid_get_child_at(GTK_GRID(grid), j, i);
            gtk_button_set_label(GTK_BUTTON(button)," ");

        }
    }
    gtk_button_set_label(GTK_BUTTON(WinButton), "Press any button to play!");
    k = 0;
    
}

static void click_event(GtkWidget *widget, gpointer user_data) {

    int i = 0;
    int j = 0;
    ButtonData *data = user_data;
    if (IsGameWon) {
        data->pressed = false;
    }

    if (data->pressed == false) {
        if (k % 2 == 0) {
            gtk_button_set_label(GTK_BUTTON(widget), "X");
            data->value = 'X';
            k++;
        } else {
            gtk_button_set_label(GTK_BUTTON(widget), "0");
            data->value = 'O';
            k++;
        }
        data->pressed = true;
        toegrid[data->row][data->column] = data->value;
    }



    for ( j = 0; j < 3; j++) {
        if (toegrid[0][j] == toegrid[1][j] && toegrid[1][j] == toegrid[2][j]) {
            if (toegrid[2][j] == 'X') {
                //X won!!
                XWon();
            } else if (toegrid[2][j] == 'O') {
                //0 won!!
                OWon();
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (toegrid[i][0] == toegrid[i][1] && toegrid[i][1] == toegrid[i][2]) {
            if (toegrid[i][2] == 'X') {
                //X won!!
                XWon();
            } else if (toegrid[i][2] == 'O') {
                //0 won!!
                OWon();
            }
        }
    }

    if (toegrid[0][0] == toegrid[1][1] && toegrid[1][1] == toegrid[2][2]) {
        if (toegrid[2][2] == 'X') {
            //X won!!
            XWon();
        } else if (toegrid[2][2] == 'O') {
            //0 won!!
            OWon();
        }
    }

    if (toegrid[0][2] == toegrid[1][1] && toegrid[1][1] == toegrid[2][0]) {
        if (toegrid[2][0] == 'X') {
            //X won!!
            XWon();
        } else if (toegrid[2][0] == 'O') {
            // won!!
            OWon();
        }
    }
    if (k == 9) {
        //Tie!!
        IsGameWon = true;
        gtk_button_set_label(GTK_BUTTON(WinButton), "Tie! Press to restart!");
    }

}

static void activate(GtkApplication* app, gpointer user_data) {


    int i = 0;
    int j = 0;

    GtkWidget* window = gtk_application_window_new(app);
    grid = gtk_grid_new();
    GtkWidget* button = gtk_button_new();

    gtk_button_set_label(GTK_BUTTON(WinButton), "Press any button to play!");


    gtk_window_set_title(GTK_WINDOW(window), "TicTacToe");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_child(GTK_WINDOW(window), grid);


    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ButtonData *data = g_malloc(sizeof(ButtonData));

            data->row = i;
            data->column = j;

            button = gtk_button_new();
            g_signal_connect(button, "clicked", G_CALLBACK(click_event), data);


            gtk_grid_attach(GTK_GRID (grid), button, j, i, 1, 1);
        }
    }

            WinButton = gtk_button_new();
            gtk_grid_attach(GTK_GRID (grid), WinButton, 0, 3, 3, 1);
            g_signal_connect(WinButton, "clicked", G_CALLBACK(reset_event), NULL);



    gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);

    gtk_window_present(GTK_WINDOW(window));

}

int main(int argc, char** argv) {
    int k = 0;
    int status;

    GtkApplication *app = gtk_application_new("Liv.app", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app),argc, argv);

    g_object_unref(app);

    return status;
}