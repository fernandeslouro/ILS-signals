#include "ILS.h"

//*********** Runway Drawing *****************
// Desenha a aeronave em duas vistas: vertical e de topo. 
// A aeronave apenas aparece na figura quando estiver a menos
// de 7 Km da pista, já que esse foi o valor que encontramos 
// para a distância do marker de fora até ao início da pista. 
void Runway_drawing(cairo_t *cr, cairo_operator_t op)
{

// Side View -----------------------------------------------------------

	// Sky figure
	cairo_save(cr);
	cairo_surface_t *image1;
	image1 = cairo_image_surface_create_from_png ("images/sky.png");
	cairo_set_source_surface (cr, image1, 0,400);
	cairo_rectangle (cr, 0,400,1200,250);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_paint (cr);
	cairo_restore(cr);

	// Forest figure
	cairo_save(cr);
	cairo_surface_t *image2;
	image2 = cairo_image_surface_create_from_png ("images/forrest2.png");
	cairo_rectangle (cr, 0,150+400,1200,150);
	cairo_clip (cr);
	cairo_new_path (cr);
	cairo_scale (cr, 0.6, 0.2);
	cairo_set_source_surface (cr, image2, -100, 1100+1700);
	cairo_paint (cr);
	cairo_restore(cr);

	// Landing strip vertical view
	cairo_save(cr);
	cairo_set_line_width(cr, 1);
	cairo_move_to (cr, 0, 620-52);
	cairo_line_to (cr, 1000, 620);
	cairo_stroke (cr);
	cairo_rectangle (cr, 1000, 350+300-30, 200, 10 );
	cairo_set_source_rgba (cr,0.756, 0.682, 0.682,  1);
	cairo_fill (cr);
	cairo_restore(cr);

	// Plane in vertical view
	cairo_save(cr);
	cairo_surface_t *image3;
	cairo_rectangle (cr, 0,350,1200,300);
	cairo_clip (cr);
	cairo_new_path (cr);
	image3 = cairo_image_surface_create_from_png ("images/plane.png");
	// 32px middle lenght, 25 px middle height
	cairo_set_source_surface (cr, image3, runway_px-32, 620-25-runway_pz);
	cairo_paint (cr);
	cairo_restore(cr);

	// Markers square
	cairo_save(cr);
	cairo_set_source_rgba (cr,0.964, 0.074, 0.074,  1);
	cairo_rectangle(cr, 995-OUTER_MARKER/7, 640,10,10); //20= 140m
	cairo_rectangle(cr, 995-MIDDLE_MARKER/7,640,10,10);
	cairo_rectangle(cr, 995-INNER_MARKER/7, 640,10,10);
	cairo_fill(cr);
	cairo_restore(cr);

	// Marker signal lobes---------
	// Outer Marker
	cairo_save(cr);
	cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
	cairo_move_to(cr, (1000-OUTER_MARKER/7), 640);
	cairo_line_to(cr, (1000-OUTER_MARKER/7-(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_line_to(cr, (1000-OUTER_MARKER/7+(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_fill(cr);
	cairo_restore(cr);

	//  Middle Marker
	cairo_save(cr);                                                                               
	cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
	cairo_move_to(cr, (1000-MIDDLE_MARKER/7), 640);
	cairo_line_to(cr, (1000-MIDDLE_MARKER/7-(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_line_to(cr, (1000-MIDDLE_MARKER/7+(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_fill(cr);
	cairo_restore(cr);

	// Inner Marker
	cairo_save(cr);
	cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
	cairo_move_to(cr, (1000-INNER_MARKER/7), 640);
	cairo_line_to(cr, (1000-INNER_MARKER/7-(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_line_to(cr, (1000-INNER_MARKER/7+(MARKER_MAX_HEIGHT/7.0)*tan(MARKER_ANGx*DEG2RAD)), (640-MARKER_MAX_HEIGHT/7));
	cairo_fill(cr);
	cairo_restore(cr);

// Top View -----------------------------------------------------------

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
	cairo_surface_t *image4;
	cairo_rectangle (cr, 1000,350+250,200,300);
	cairo_clip (cr);
	cairo_new_path (cr);
	image4 = cairo_image_surface_create_from_png ("images/run.png");
	cairo_scale (cr, 0.3,0.2);
	cairo_set_source_surface (cr, image4, 1000/0.3, 740/0.2);
	cairo_paint (cr);
	cairo_restore(cr);

	// Markers square
	cairo_save(cr);
	cairo_set_source_rgba (cr,0.964, 0.074, 0.074,  1);
	cairo_rectangle(cr, 995-OUTER_MARKER/7, 400+250+120,10,10); //20= 140m
	cairo_rectangle(cr, 995-MIDDLE_MARKER/7,400+250+120,10,10);
	cairo_rectangle(cr, 995-INNER_MARKER/7, 400+250+120,10,10);
	cairo_fill(cr);
	cairo_restore(cr);

	// Plane in top view
	cairo_save(cr);
	cairo_surface_t *image5;
	cairo_rectangle (cr, 0,400+250,1200,250);
	cairo_clip (cr);
	cairo_new_path (cr);
	image5 = cairo_image_surface_create_from_png ("images/plane_top.png");
	// 31px middle lenght, 28 middle height
	cairo_set_source_surface (cr, image5, runway_px-31, 775-21-runway_py);
	cairo_paint (cr);
	cairo_restore(cr);


	//  Elipses in Top View
	float a,b;
	if ((altitude_a+140)>MARKER_MAX_HEIGHT)
	{
		a=2*(MARKER_MAX_HEIGHT)/7.0*tan(MARKER_ANGx*DEG2RAD);
		b=2*(MARKER_MAX_HEIGHT)/7.0*tan(MARKER_ANGy*DEG2RAD);
	}
	else
	{
		a=(altitude_a+140)/7.0*tan(MARKER_ANGx*DEG2RAD);
		b=(altitude_a+140)/7.0*tan(MARKER_ANGy*DEG2RAD);
	}

	if (a>0){
		//Ellipse Outer Marker
		cairo_save(cr);
		cairo_rectangle (cr, 0,400+250,1200,250);
		cairo_clip (cr);

		cairo_translate(cr, 1000-OUTER_MARKER/7, 400+250+125);
		cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
		cairo_scale(cr, 1, b/a);
		cairo_arc(cr, 0, 0, a,0, 2*M_PI);
		cairo_fill(cr);
		cairo_restore(cr);

		//Ellipse Middle Marker
		cairo_save(cr);
		cairo_rectangle (cr, 0,400+250,1200,250);
		cairo_clip (cr);
		cairo_translate(cr, 1000-MIDDLE_MARKER/7, 400+250+125);
		cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
	 	cairo_scale(cr, 1, b/a);
		cairo_arc(cr, 0, 0, a,0, 2*M_PI);
		cairo_fill(cr);
		cairo_restore(cr);

		//Ellipse Inner Marker
		cairo_save(cr);
		cairo_rectangle (cr, 0,400+250,1200,250);
		cairo_clip (cr);
		cairo_translate(cr, 1000-INNER_MARKER/7, 400+250+125);
		cairo_set_source_rgba (cr, 0.964, 0.074, 0.074, 0.5);
	 	cairo_scale(cr, 1, b/a);
		cairo_arc(cr, 0, 0, a,0, 2*M_PI);
		cairo_fill(cr);
		cairo_restore(cr);
	}

	// Draw Switch button ------------------------------------------
	cairo_save(cr);
	cairo_surface_t *image6;
	cairo_rectangle (cr, 1100,400,100,50);
	cairo_clip (cr);
	cairo_new_path (cr);
	image6 = cairo_image_surface_create_from_png ("images/off.png");
	cairo_set_source_surface (cr, image6, 1100, 400);
	cairo_paint (cr);
	cairo_restore(cr);

	// Destroy images for memory management
	cairo_surface_destroy (image1);
	cairo_surface_destroy (image2);
	cairo_surface_destroy (image3);
	cairo_surface_destroy (image4);
	cairo_surface_destroy (image5);
	cairo_surface_destroy (image6);

}
