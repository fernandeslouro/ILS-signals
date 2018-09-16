#include "ILS.h"


struct timeval start;
struct timeval stop;

struct {
	float x;
	float alt;
	float y;
	float land;
	float scal_x;
	float scal_y;
	float ils_x;
	float ils_y;
	float heading;
} glob;


double DegreesToRadians( double degrees )
{
	return((double)((double)degrees * ( (double)PI/(double)180.0 )));
}

void do_drawing(cairo_t *cr, int w,
	int h, cairo_operator_t op)
{

	// Sky figure
	cairo_save(cr);
	cairo_surface_t *image2;
	image2 = cairo_image_surface_create_from_png ("images/sky.png");
	cairo_set_source_surface (cr, image2, 0,400);
	cairo_rectangle (cr, 0,400,1200,250);
	cairo_clip (cr);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);

	// Forest figure
	cairo_save(cr);
	cairo_surface_t *image3;
	image3 = cairo_image_surface_create_from_png ("images/forrest2.png");
	cairo_rectangle (cr, 0,150+400,1200,150);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_scale (cr, 0.6, 0.2);
	cairo_set_source_surface (cr, image3, -100, 1100+1700);
	cairo_paint (cr);
	cairo_restore(cr);

	// Landing strip vertical view
	cairo_save(cr);
	cairo_set_line_width(cr, 1); 
	cairo_move_to (cr, 0, 350+185);
	cairo_line_to (cr, 1000, 350+300-30);
	cairo_stroke (cr);
	cairo_rectangle (cr, 1000, 350+300-30, 200, 10 );
	cairo_set_source_rgba (cr,0.756, 0.682, 0.682,  1);
	cairo_fill (cr);
	cairo_restore(cr);
	
	// Plane in vertical view
	cairo_save(cr);
	cairo_surface_t *image;
	cairo_rectangle (cr, 0,350,1200,300);
	cairo_clip (cr);
	cairo_new_path (cr); 
	image = cairo_image_surface_create_from_png ("images/plane.png");
	cairo_scale (cr, glob.scal_x, glob.scal_y);
	//printf("pos %f %f\n",glob.x, glob.alt);
	cairo_set_source_surface (cr, image, glob.x, glob.alt+350/glob.scal_y);
	cairo_paint (cr);
	cairo_restore(cr);

	// Markers
	cairo_save(cr);	
	cairo_set_source_rgba (cr,0.964, 0.074, 0.074,  1);
	cairo_rectangle(cr, 1000-OUTER_MARKER/7, 620,10,10);
	cairo_rectangle(cr, 1000-MIDDLE_MARKER/7,620,10,10);
	cairo_rectangle(cr, 1000-INNER_MARKER/7, 620,10,10);
	cairo_fill(cr);
	cairo_restore(cr);

	// Grass in top view
	cairo_save(cr);	
	cairo_rectangle(cr, 0,400+250,1200,250);
	cairo_set_source_rgba (cr,0.094, 0.466, 0.137,  1);
	cairo_fill(cr);
	cairo_restore(cr);

	// ILS approach in top view
	cairo_save(cr);
	cairo_set_line_width(cr, 1); 
	cairo_move_to (cr, 0, 775);
	cairo_line_to (cr, 1000, 775);
	cairo_stroke (cr);
	cairo_restore(cr);

	// Runaway in top view
	cairo_save(cr);
	cairo_surface_t *image7;
	cairo_rectangle (cr, 1000,350+250,200,300);
	cairo_clip (cr);
	cairo_new_path (cr); 
	image7 = cairo_image_surface_create_from_png ("images/run.png");
	cairo_scale (cr, 0.3,0.2);
	cairo_set_source_surface (cr, image7, 1000/0.3, 740/0.2);
	cairo_paint (cr);
	cairo_restore(cr);

	// Plane in top view
	cairo_save(cr);
	cairo_surface_t *image8;
	cairo_rectangle (cr, 0,400+250,1200,250);
	cairo_clip (cr);
	cairo_new_path (cr); 
	image8 = cairo_image_surface_create_from_png ("images/plane_top.png");
	cairo_scale (cr, glob.scal_x*4, glob.scal_y*2);
	cairo_set_source_surface (cr, image8, 0.25*glob.x, 0.5*glob.y/glob.scal_y);
	cairo_paint (cr);
	cairo_restore(cr);
	
	cairo_surface_destroy (image);
	cairo_surface_destroy (image2);
	cairo_surface_destroy (image3);
	cairo_surface_destroy (image7);
	cairo_surface_destroy (image8);

}

float timedifference_msec(struct timeval t0, struct timeval t1)
{
	return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
	gpointer user_data)
{      

	gettimeofday(&start, NULL);

	GtkWidget *win = gtk_widget_get_toplevel(widget);

	int width, height;
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
	
	if (glob.land > glob.alt)
	{
		glob.x += 1000*glob.scal_x;
		glob.alt += 52.4*glob.scal_x;
	}else if (glob.x < 1250/glob.scal_x){
		glob.x += 1000*glob.scal_x;
	}
	
	//glob.heading = 10;
	//ILS_heading += 1;
	//ILS_x = 2; //deg
	//ILS_y = 2; //deg
	//ATT_pitch += 10; //deg
	//ATT_roll = 45; //deg

	// ILS indicator

	printf("Attitude pitch: %d roll: %d\n",ATT_pitch, ATT_roll);

	// ILS Markers
	map_drawing(cr);

	// Runway view
	do_drawing(cr, width, height, CAIRO_OPERATOR_DEST_OVER );

	// Attitude indicator
	ATT_drawing(cr, width, height, CAIRO_OPERATOR_DEST_OVER );

	// Map
	map_drawing(cr, width, height, CAIRO_OPERATOR_DEST_OVER );

	gettimeofday(&stop, NULL);
	float elapsed = timedifference_msec(start, stop);
	//printf("took %f\n", elapsed);
	
	return FALSE;
}

static gboolean time_handler(GtkWidget *widget)
{

	gtk_widget_queue_draw(widget);

	return TRUE;
}

void *visual(void* param)
{
	GtkWidget *window;
	GtkWidget *darea;  

	glob.scal_x = 0.05;
	glob.scal_y = 0.08;
	glob.x = 0;
	glob.y = 754;
	glob.alt = (300-52.4-80)/glob.scal_y;
	glob.land = (300-52.4-0)/glob.scal_y;
	glob.ils_x=42;
	glob.ils_y=-42;
	//14 -> 0.5deg
	ArgCV *args = (ArgCV*) param;
	gtk_init(&(args->argc), &(args->argv));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (window), darea);

	g_signal_connect(G_OBJECT(darea), "draw", 
		G_CALLBACK(on_draw_event), NULL);  
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 1600, 900);
	gtk_window_set_title(GTK_WINDOW(window), "ILS");

	g_timeout_add(10, (GSourceFunc) time_handler, (gpointer) window);
	gtk_widget_show_all(window);

	gtk_main();


}
