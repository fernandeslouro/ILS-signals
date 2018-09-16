#include "ILS.h"

//*********** ATT indicator drawing *****************
// Desenha o indicador de atitude.
void ATT_ind_drawing(cairo_t *cr, cairo_operator_t op)
{

	// ATT grelha interior----------------------------------------
	cairo_save(cr);
	cairo_surface_t *image1;
	cairo_rectangle (cr, 1205,585,385,230);
	cairo_clip (cr);
	cairo_new_path (cr); 
	image1 = cairo_image_surface_create_from_png ("images/grelha.png");

	// Translation + Rotatio
	int ww = cairo_image_surface_get_width (image1);
	int hh = cairo_image_surface_get_height (image1);
	float rad = -ATT_roll *DEG2RAD;
	cairo_translate(cr, ww/2.0,hh/2.0);
	cairo_rotate(cr, rad);
	cairo_translate(cr, - ww/2.0, -hh/2.0+ATT_pitch); 
	cairo_translate(cr,1205.0*cos(rad), -1205.0*sin(rad));
	cairo_translate(cr,515.0*sin(rad), 515.0*cos(rad));
	cairo_set_source_surface (cr, image1, 0,0);
	cairo_paint (cr);
	cairo_restore(cr);

	// ATT outside of the angles---------------------------------------
	cairo_save(cr);
	cairo_surface_t *image2;
	cairo_rectangle (cr, 1205,585,385,230);
	cairo_clip (cr);
	cairo_new_path (cr); 
	image2 = cairo_image_surface_create_from_png ("images/roda2.png");

	// Rotation
	ww = cairo_image_surface_get_width (image2);
	hh = cairo_image_surface_get_height (image2);
	rad = -ATT_roll *DEG2RAD;
	cairo_translate(cr, ww/2.0, hh/2.0);
	cairo_rotate(cr, rad);
	cairo_translate(cr, - ww/2.0, -hh/2.0);
	cairo_translate(cr,1212.0*cos(rad), -1212.0*sin(rad));
	cairo_translate(cr,520.0*sin(rad), 520.0*cos(rad));
	cairo_set_source_surface (cr, image2, 0,0);
	cairo_paint (cr);
	cairo_restore(cr);

	// ATT outside indicator-----------------------------------------
	cairo_save(cr);
	cairo_surface_t *image3;
	image3 = cairo_image_surface_create_from_png ("images/out1.png");
	cairo_set_source_surface (cr, image3, 1200, 500);
	cairo_paint (cr);
	cairo_restore(cr);

	// ATT level and arrow---------------------------------------
	cairo_save(cr);
	cairo_surface_t *image4;
	image4 = cairo_image_surface_create_from_png ("images/out2.png");
	cairo_set_source_surface (cr, image4, 1200, 500);
	cairo_paint (cr);
	cairo_restore(cr);

	// Destroys images because of memory usage
	cairo_surface_destroy (image1);
	cairo_surface_destroy (image2);
	cairo_surface_destroy (image3);
	cairo_surface_destroy (image4);
}