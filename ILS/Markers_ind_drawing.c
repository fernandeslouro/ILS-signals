#include "ILS.h"

int counter=1;

//*********** Sound *****************
// Thread que faz com um som toque quando necessário
void *sound(void* param){

	// If Inner Marker
	if (ILS_inner_marker==true)
	{
		system("mpv beep3.mp3");
	}
	// If Middle Marker
	else if (ILS_middle_marker==true)
	{
		int a = *((int *) param);
		free(param);
		if (a == 0)
		{
			system("mpv beep2.mp3");
		}
		else
		{
			system("mpv beep4.mp3");
		}
	}
	// If Outer Marker
	else if (ILS_outer_marker==true)
	{
		system("mpv beep1.mp3");
	}
}

//*********** Markers Indicator Drawing *****************
// Desenha os markers e as elipses que mostram o alcance em termos de 
// altitude e de posição do avião para que o piloto saiba que passou 
// no marker de fora, no médio ou no de dentro. Emite um aviso sonoro 
// quando passa nestes três markers, através do uso de uma thread apenas 
// para esse uso específico. Foi utilizada uma thread aqui porque, da 
// forma como implementamos o aviso sonoro, o programa bloqueava a 
// reproduzir o som. Assim, o som toca em paralelo com o restante programa.
void Markers_ind_drawing(cairo_t *cr, cairo_operator_t op)
{

	cairo_save(cr);
	cairo_surface_t *image;

	cairo_rectangle (cr,1200,350, 400, 200);
	cairo_clip (cr);
	cairo_new_path (cr);

	//Inside Outer Marker------------------------------
	if (ILS_inner_marker==true)
	{

		// Thread for Sound
		if (counter == 1)
		{
			pthread_t t2;
			int aux = 0;
			pthread_create(&t2, NULL, sound, NULL);
		}

		// Sequence o images
		if (counter>=1 && counter<=3){ //blinks short
			image = cairo_image_surface_create_from_png ("images/Inner_Marker.png");
		} 
		else if (counter>=4 && counter<=6) //nothing
			image = cairo_image_surface_create_from_png ("images/No_Marker.png");

		// Counter Update
		counter++;
		if(counter==7)
			counter=1;
	}

	//Inside Middle Marker------------------------------
	else if (ILS_middle_marker==true)
	{

		// Thread for Sound
		if (counter == 1 )
		{
			pthread_t t2;
			int *aux = malloc(sizeof(*aux));
			*aux = 0;
			pthread_create(&t2, NULL, sound, aux);
		}else if (counter == 12)
		{
			pthread_t t2;
			int *aux = malloc(sizeof(*aux));
			*aux = 1;
			pthread_create(&t2, NULL, sound, aux);
		}

		// Sequence o images
		if (counter>=1 && counter<=9) //blinks long
			image = cairo_image_surface_create_from_png ("images/Middle_Marker.png");
		else if (counter>=10 && counter<=12) //nothing
			image = cairo_image_surface_create_from_png ("images/No_Marker.png");
		else if (counter>=12 && counter<=14) //blinks short
			image = cairo_image_surface_create_from_png ("images/Middle_Marker.png");
		else if (counter>=15 && counter<=17) //nothing
			image = cairo_image_surface_create_from_png ("images/No_Marker.png");

		// Counter Update
		counter++;
		if(counter==18)
			counter=1;
	}
	//Inside Inner Marker------------------------------
	else if (ILS_outer_marker==true)
	{

		// Thread for Sound
		if (counter == 1)
		{
			pthread_t t2;
			int aux = 0;
			pthread_create(&t2, NULL, sound, &aux);
		}

		// Sequence o images
		if (counter>=1 && counter<=9) //blinks long
			image = cairo_image_surface_create_from_png ("images/Outer_Marker.png");
		else if (counter>=10 && counter<=12) //nothing
			image = cairo_image_surface_create_from_png ("images/No_Marker.png");

		// Counter Update
		counter++;
		if(counter==13)
			counter=1;
	}
	else // Reset counters
	{
		counter=1;
		image = cairo_image_surface_create_from_png ("images/No_Marker.png");	
	}

	// Cairo Sequence
	cairo_set_source_surface (cr,image, 1200, 350);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);
}