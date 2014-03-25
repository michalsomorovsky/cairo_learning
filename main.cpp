#include <iostream>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <pango/pangocairo.h>

static void do_drawing(cairo_t *);

int points[11][2] =
{
    { 0, 85 },
    { 75, 75 },
    { 100, 10 },
    { 125, 75 },
    { 200, 85 },
    { 150, 125 },
    { 160, 190 },
    { 100, 150 },
    { 40, 190 },
    { 50, 125 },
    { 0, 85 }
};

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                              gpointer user_data)
{
    do_drawing(cr);

    return FALSE;
}

using namespace std;

static void do_drawing(cairo_t *cr)
{
    double xc = 100.0;
    double yc = 100.0;
    double radius = 10.0;
    double angle1 = 0.0  * (M_PI/180.0);  /* angles are specified */
    double angle2 = 360.0 * (M_PI/180.0);  /* in radians           */

    cairo_set_line_width (cr, 10.0);
    cairo_arc (cr, xc, yc, radius, angle1, angle2);
    cairo_stroke (cr);

    cairo_set_line_width (cr, 1.0);
    cairo_rectangle(cr, 200.0, 100.0, 100.0, 100.0);
    cairo_stroke(cr);

    //cairo_move_to(cr, 0.0, 0.0);
    //cairo_line_to(cr, 100.0, 100.0);
    //cairo_line_to(cr, 100.0, 150.0);
    //cairo_curve_to(cr, 120.0, 130.0, 140.0, 150.0, 200.0, 150.0);
    //cairo_move_to(cr, 250.0, 150.0);
    //cairo_text_path(cr, "lama");
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_scale(cr, 1, 0.7);
    cairo_arc(cr, 300, 100, 50, 0, 2*M_PI);
    cairo_fill(cr);
    //cairo_stroke(cr);

    PangoLayout *layout;
    PangoFontDescription *font_description;

    font_description = pango_font_description_new ();
    pango_font_description_set_family (font_description, "serif");
    pango_font_description_set_weight (font_description, PANGO_WEIGHT_BOLD);
    pango_font_description_set_absolute_size (font_description, 12 * PANGO_SCALE);

    layout = pango_cairo_create_layout (cr);
    pango_layout_set_font_description (layout, font_description);
    pango_layout_set_text (layout, "Hello, world", -1);

    cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
    cairo_move_to (cr, 250.0, 100.0);
    pango_cairo_show_layout (cr, layout);

    g_object_unref (layout);
    pango_font_description_free (font_description);

    /* draw helping lines */
    //cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    //cairo_set_line_width (cr, 6.0);

    //cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
    //cairo_fill (cr);

    //cairo_arc (cr, xc, yc, radius, angle1, angle1);
    //cairo_line_to (cr, xc, yc);
    //cairo_arc (cr, xc, yc, radius, angle2, angle2);
    //cairo_line_to (cr, xc, yc);
    //cairo_stroke (cr);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *darea;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
    g_signal_connect(G_OBJECT(darea), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 460, 240);
    gtk_window_set_title(GTK_WINDOW(window), "Other shapes");

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
