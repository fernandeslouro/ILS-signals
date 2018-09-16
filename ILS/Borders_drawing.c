#include "ILS.h"

//*********** Borders Drawing *****************
// Desenha bordas entre os indicadores
void Borders_drawing(cairo_t *cr, cairo_operator_t op)
{
	cairo_save(cr);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 3);

	// Border #1 
	cairo_move_to(cr, 0, 400);
	cairo_line_to(cr, 1200, 400);
	cairo_line_to(cr, 1200, 900);
	cairo_stroke(cr); 

	// Border #2
	cairo_move_to(cr, 0, 0);
	cairo_line_to(cr, 1200, 0);
	cairo_line_to(cr, 1200, 900);
	cairo_line_to(cr, 0, 900);
	cairo_line_to(cr, 0, 0);
	cairo_stroke(cr); 

	// Border #3 separating runways when visible
	if (!flag_control)
	{
		cairo_move_to(cr, 0, 648);
		cairo_line_to(cr, 1200, 648);
		cairo_stroke(cr); 
	}

	// Border #4
 	cairo_move_to(cr, 950, 0);
	cairo_line_to(cr, 950, 400);
	cairo_stroke(cr);

	// Border #5
	cairo_move_to(cr, 1200, 400);
	cairo_line_to(cr, 1600, 400);
	cairo_stroke(cr); 

	cairo_restore(cr);
}