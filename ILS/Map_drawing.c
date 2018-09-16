#include "ILS.h"

//*********** add_map *****************
//
void add_map(cairo_t *cr, int row, int column, int cx, int cy, cairo_operator_t op)
{
	// If image within range
	if (column<10 && column>=0 && row<25 && row>=0){

		// Cairo drawing sequence
		cairo_save(cr);
		cairo_surface_t *image2;

		cairo_rectangle (cr,0,0, WIDTH_W, HEIGHT_W);
		cairo_clip (cr);
		cairo_new_path (cr);
		char str[30];
		memset(str, 0, sizeof(str));

		// Selects image based on the column and width
		sprintf(str,"map/row-%d-col-%d.png", row+1, column+1);
		image2 = cairo_image_surface_create_from_png (str);
		cairo_set_source_surface (cr,image2, cx, cy);

		cairo_new_path (cr); 
		cairo_paint (cr);
		cairo_restore(cr);
		cairo_surface_destroy (image2);
	}

}

//*********** Map_drawing *****************
// Draws t
void Map_drawing(cairo_t *cr, cairo_operator_t op)
{

	cairo_save(cr);
	cairo_surface_t *image2;

	int column 	= (int) map_big_px/WIDTH_IM;
	int row 	= (int) map_big_py/HEIGHT_IM;

	// DRAW BIGMAP--------------------------------------------------
	//---------------------------------------------------------------

	int center_x=(map_big_px-column*WIDTH_IM);
	int center_y=(map_big_py-row*HEIGHT_IM);

	//Center map image drawing
	add_map(cr,row, column, WIDTH_W/2.0 - center_x, HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);

	// Neighbours image determination - check which other images appear in frame
	// add image right
	if(center_x>WIDTH_W/2)
	{ 
		add_map(cr,row, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);

		// add image up
		if(center_y<HEIGHT_W/2)
		{
			add_map(cr,row-1, column, WIDTH_W/2.0 - center_x, 			-HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row-1, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x,-HEIGHT_IM + HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
		// add image down
		else if(center_y>HEIGHT_W-HEIGHT_W/2)
		{
			add_map(cr,row+1, column,	WIDTH_W/2.0 - center_x, 		HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row+1, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x,HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
	
	}
	// add image left
	else if (center_x<WIDTH_IM-WIDTH_W/2)
	{ 

		add_map(cr,row, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		
		// add image up
		if(center_y<HEIGHT_W/2)
		{
			add_map(cr,row-1, column, WIDTH_W/2.0 - center_x, 			  -HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row-1, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, -HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
		// add image down
		else if(center_y>HEIGHT_W-HEIGHT_W/2)
		{
			add_map(cr,row+1, column, WIDTH_W/2.0 - center_x, 			  HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row+1, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
	}
	// add image left and right
	else
	{ 
		add_map(cr,row, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		add_map(cr,row, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);

		// add image up
		if(center_y<HEIGHT_W/2)
		{
			add_map(cr,row-1, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, -HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row-1, column, WIDTH_W/2.0 - center_x, 			  -HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row-1, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x,  -HEIGHT_IM + HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
		// add image down
		else if(center_y>HEIGHT_W-HEIGHT_W/2)
		{
			add_map(cr,row+1, column-1, -WIDTH_IM+WIDTH_W/2.0 - center_x, HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row+1, column,	WIDTH_W/2.0 - center_x, 		  HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
			add_map(cr,row+1, column+1, WIDTH_IM+WIDTH_W/2.0 - center_x,  HEIGHT_IM+ HEIGHT_W/2.0 - center_y, CAIRO_OPERATOR_DEST_OVER);
		}
	}


	// Plane big map-----------
	cairo_save(cr);
	cairo_surface_t *p_big;
	cairo_new_path (cr); 

	p_big = cairo_image_surface_create_from_png ("images/plane_top_map.png");

	int ww, hh;  
	double rad = 0.0;

	//Rotate according to yaw
	ww = cairo_image_surface_get_width (p_big);
	hh = cairo_image_surface_get_height (p_big);
	rad = ILS_heading *DEG2RAD;
	cairo_translate(cr, ww/2.0, hh/2.0);
	cairo_rotate(cr, rad);
	cairo_translate(cr, - ww/2.0, -hh/2.0);
	cairo_translate(cr,(WIDTH_W/2-ww/2)*cos(rad), -(WIDTH_W/2-ww/2)*sin(rad));
	cairo_translate(cr,(HEIGHT_W/2-hh/2)*sin(rad), (HEIGHT_W/2-hh/2)*cos(rad));
	cairo_set_source_surface(cr,p_big, 0,0);

	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (p_big);


	// DRAW MINIMAP--------------------------------------------------
	//---------------------------------------------------------------

	cairo_rectangle (cr, WIDTH_W,0, 250,HEIGHT_W);
	cairo_clip (cr);
	cairo_new_path (cr);

	// Image minimap
	image2 = cairo_image_surface_create_from_png ("map/mini_mapa_PT.png");
	cairo_set_source_surface (cr, image2,WIDTH_W, 0);

	//Cairo drawing
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image2);

	// Plane small map
	cairo_save(cr);
	cairo_surface_t *p_small;
	cairo_new_path (cr); 
	p_small = cairo_image_surface_create_from_png ("images/plane_top_smap.png");
	
	//Rotate according to yaw
	ww = cairo_image_surface_get_width (p_small);
	hh = cairo_image_surface_get_height (p_small);
	rad = ILS_heading *DEG2RAD;
	cairo_translate(cr, ww/2.0, hh/2.0);
	cairo_rotate(cr, rad);
	cairo_translate(cr, - ww/2.0, -hh/2.0);
	cairo_translate(cr,(WIDTH_W+map_small_px)*cos(rad), -(WIDTH_W+map_small_px)*sin(rad));
	cairo_translate(cr,(map_small_py)*sin(rad), (map_small_py)*cos(rad));
	cairo_set_source_surface(cr,p_small, 0,0);

	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (p_small);

}