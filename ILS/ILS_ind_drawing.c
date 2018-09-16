#include "ILS.h"

//*********** ILS Indicator Drawing *****************
// Desenha o indicador de ILS
void ILS_ind_drawing(cairo_t *cr, cairo_operator_t op)
{

	// ILS inside fixed----------------------------------
	cairo_save(cr);
	cairo_surface_t *image1;

	// If flag on NAV green, if off, NAV red
	if (ILS_flag)
	{
		image1 = cairo_image_surface_create_from_png ("images/inside_green.png");
	}
	else
	{
		image1 = cairo_image_surface_create_from_png ("images/inside_red.png");
	}

	cairo_rectangle (cr, 1200, 0 , 360,360);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_set_source_surface (cr, image1, 1200, 0);
	cairo_paint (cr);
	cairo_restore(cr);
	
	// Heading indicator-------------------------------------
	cairo_save(cr);
	cairo_surface_t *image2;

	image2 = cairo_image_surface_create_from_png ("images/roda_heading3.png");

	// Indicator rotates
	int ww, hh;  
	double rad = 0.0;
	ww = cairo_image_surface_get_width (image2);
	hh = cairo_image_surface_get_height (image2);
	rad =  -ILS_heading*DEG2RAD;
	cairo_translate(cr, ww/2.0, hh/2.0);
	cairo_rotate(cr, rad);
	cairo_translate(cr, - ww/2.0, -hh/2.0);
	cairo_translate(cr,1200.0*cos(rad), -1200.0*sin(rad));
	cairo_set_source_surface(cr,image2, 0,0);
	cairo_paint (cr);
	cairo_rectangle (cr, 1200, 0, 360, 360);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_restore(cr);

	// ILS outside shell ---------------------------------------
	cairo_save(cr);
	cairo_surface_t *image3;

	//Image without OBS cursor as not necessary
	image3 = cairo_image_surface_create_from_png ("images/roda_outside.png");

	cairo_rectangle (cr, 1200, 0, 360, 360);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_set_source_surface (cr, image3, 1200/1+2, 5);
	cairo_paint (cr);
	cairo_restore(cr);

	// ILS needles---------------------------------------------
	cairo_save(cr);
	cairo_set_source_rgba (cr,0.756, 0.682, 0.682,  1);
	cairo_arc (cr, 1381, 179, 92, 0, 2 * PI);
	cairo_clip (cr);	
	cairo_set_line_width(cr, 5); 

	// If flag on draws position, if off draws standard
	if (ILS_flag)
	{
		cairo_move_to (cr, 1377-ILS_x, 95);
		cairo_line_to (cr, 1377-ILS_x, 260);
		cairo_move_to (cr, 1295, 176+ILS_y);
		cairo_line_to (cr, 1458, 176+ILS_y);
	}
	else
	{
		cairo_move_to (cr, 1377, 95);
		cairo_line_to (cr, 1377, 260);
		cairo_move_to (cr, 1295, 176);
		cairo_line_to (cr, 1458, 176);
	}

	cairo_stroke (cr);
	cairo_restore(cr);

	// Destroys images, releasing mamory
	cairo_surface_destroy (image1);
	cairo_surface_destroy (image2);
	cairo_surface_destroy (image3);
}