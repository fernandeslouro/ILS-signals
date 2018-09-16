#include "ILS.h"

struct timeval start;
struct timeval stop;

bool flag_control=false;

//*********** Time Difference *****************
// Retorna uma diferença de tempo em ms. 
float timedifference_msec(struct timeval t0, struct timeval t1)
{
	return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

//*********** On Draw Event *****************
// Repete a cada 100ms para renovar o ambiente grífico.
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
	gpointer user_data)
{

	gettimeofday(&start, NULL);

	GtkWidget *win = gtk_widget_get_toplevel(widget);

	// Size of window
	int width, height;
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
	

	// Calls drawing Functions--------------------------------

	// ILS indicator
	ILS_ind_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	// ILS Markers indicator
	Markers_ind_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	// Attitude indicator
	ATT_ind_drawing(cr, CAIRO_OPERATOR_DEST_OVER );
	// Maps
	Map_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	// Control pannel
	if (flag_control) Control_pannel_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	// Runway view
	else Runway_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	// Borders
	Borders_drawing(cr, CAIRO_OPERATOR_DEST_OVER );

	//-------------------------------------------------------------

	// If needed printing the time elapsed during one cycle
	gettimeofday(&stop, NULL);
	float elapsed = timedifference_msec(start, stop);
	//printf("took %f\n", elapsed);

	return FALSE;
}

//*********** Time Handler *****************
// Timer
static gboolean time_handler(GtkWidget *widget)
{

	gtk_widget_queue_draw(widget);

	return TRUE;
}


//*********** When Clicked *****************
// When a click event occurs, this function checks the position 
// and interprets the intention of the user
static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
	// Left click
    if (event->button == 1) {

    	// Switch control button
    	if (((event->x)<1200) && ((event->x)>1100) && ((event->y)>400) && ((event->y)<450))
    	{
    		if (flag_control) flag_control=false;
    		else flag_control=true;
    	}

    	// Change Airport Button
    	if (flag_control==true){

    		if(((event->x)<366) && ((event->x)>11)){
    			if (((event->y)<695) && ((event->y)>605)) n_aeroporto=0; //Lisboa
    			if (((event->y)<793) && ((event->y)>703)) n_aeroporto=1; //Porto
    		}
    		if(((event->x)<732) && ((event->x)>377)){
    			if (((event->y)<695) && ((event->y)>605)) n_aeroporto=2; //Faro
    			if (((event->y)<793) && ((event->y)>703)) n_aeroporto=3; //Bragança
    			if (((event->y)<891) && ((event->y)>801)) n_aeroporto=4; //Viseu
    		}
    		else if (((event->x)<1098) && ((event->x)>743)){
    			if (((event->y)<499) && ((event->y)>409)) n_aeroporto=5; //Leiria
    			if (((event->y)<597) && ((event->y)>507)) n_aeroporto=6; //Cascais
    			if (((event->y)<695) && ((event->y)>605)) n_aeroporto=7; //Évora
    			if (((event->y)<793) && ((event->y)>703)) n_aeroporto=8; //Beja
    			if (((event->y)<891) && ((event->y)>801)) n_aeroporto=9; //Portimão
    		}
    	}   
    }
    return TRUE;
}

//*********** Visual *****************
// Main da Visual.c.
/* Função que corre numa thread paralela ao ILS.c. Tem como função definir as 
coordenadas do ecrã que servem para mudar variáveis, como se tratasse de botões e também 
atualizar a janela gráfica. Está definida para atualizar a cada 10 ms mas, como esta 
função corre em cerca de 100 ms, é esse o tempo que demora a atualizar o gráfico. Como 
se trata de imagens que são constantemente sobrepostas, não há a hipótese de desenhar 
apenas por cima, o que tornaria o ambiente gráfico mais rápido. A thread corre todos 
os ficheiro referidos em cima nesta lista. */
void *visual(void* param)
{

	// Cairo Init Sequence
	GtkWidget *window;
	GtkWidget *darea;

	ArgCV *args = (ArgCV*) param;
	gtk_init(&(args->argc), &(args->argv));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (window), darea);

	// Set event handlers
	g_signal_connect(G_OBJECT(darea), "draw",
		G_CALLBACK(on_draw_event), NULL);

	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(window, "button-press-event", 
		G_CALLBACK(clicked), NULL);

	// Set window properties
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 1600, 900);
	gtk_window_set_title(GTK_WINDOW(window), "ILS");

	// Add timer
	g_timeout_add(10, (GSourceFunc) time_handler, (gpointer) window);
	gtk_widget_show_all(window);

	gtk_main();


}
