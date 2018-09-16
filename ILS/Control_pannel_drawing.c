#include "ILS.h"


int n_aeroporto=0;

//*********** Control Pannel Drawing *****************
// Desenha o painel de controlo. São aqui introduzidos os dados
// de cada aeroporto (posição e ângulo de guinada da pista).
void Control_pannel_drawing(cairo_t *cr, cairo_operator_t op)
{

	// Draw all buttons UNSELECTED---------------------------------------
	cairo_surface_t *image;

	// Button Lisboa
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/lisboa.png");
	cairo_set_source_surface (cr,image, 11, 605);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Porto
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/porto.png");
	cairo_set_source_surface (cr,image, 11, 703);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Faro
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/faro.png");
	cairo_set_source_surface (cr,image, 377, 605);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Bragança
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/bragança.png");
	cairo_set_source_surface (cr,image, 377, 703);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Viseu
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/viseu.png");
	cairo_set_source_surface (cr,image, 377, 801);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Leiria
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/leiria.png");
	cairo_set_source_surface (cr,image, 743, 409);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Cascais
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/cascais.png");
	cairo_set_source_surface (cr,image, 743, 507);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Evora
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/evora.png");
	cairo_set_source_surface (cr,image, 743, 605);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Beja
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/beja.png");
	cairo_set_source_surface (cr,image, 743, 703);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Button Portimão
	cairo_save(cr);
	image = cairo_image_surface_create_from_png ("images/portimao.png");
	cairo_set_source_surface (cr,image, 743, 801);
	cairo_new_path (cr); 
	cairo_paint (cr);
	cairo_restore(cr);
	cairo_surface_destroy (image);

	// Draw SELECTED Button-----------------------------------

	switch(n_aeroporto){

		case 0:
			// Aeroporto Lisboa
			pos_r[1]=38.77559;
			pos_r[0]=-9.13536;
			pos_r[2]=0;
			att_r=59;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/lisboa_sel.png");
			cairo_set_source_surface (cr,image, 11, 605);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/LIS.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 1:
			// Aeroporto Porto
			pos_r[1]=41.24211;
			pos_r[0]=-8.67855;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/porto_sel.png");
			cairo_set_source_surface (cr,image, 11, 703);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/OPO.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 2:
			// Aeroporto Faro
			pos_r[1]=37.01759;
			pos_r[0]=-7.96972;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/faro_sel.png");
			cairo_set_source_surface (cr,image, 377, 605);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/FAO.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 3:
			// Aerodromo de Bragança
			pos_r[1]=41.85718;
			pos_r[0]=-6.70726;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/bragança_sel.png");
			cairo_set_source_surface (cr,image, 377, 703);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/BGC.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 4:
			// Aerodromo Viseu
			pos_r[1]=40.72556;
			pos_r[0]=-7.88904;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/viseu_sel.png");
			cairo_set_source_surface (cr,image, 377, 801);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/VSE.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 5:
			// Aerodromo Leiria
			pos_r[1]=39.77995;
			pos_r[0]=-8.82077;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/leiria_sel.png");
			cairo_set_source_surface (cr,image, 743, 409);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/LPJF.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 6:
			// Aerodromo Cascais
			pos_r[1]=38.72194;
			pos_r[0]=-9.35361;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/cascais_sel.png");
			cairo_set_source_surface (cr,image, 743, 507);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/LCT.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 7:
			// Aerodromo Evora
			pos_r[1]=38.53153;
			pos_r[0]=-7.88828;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/evora_sel.png");
			cairo_set_source_surface (cr,image, 743, 605);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/LPEV.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 8:
			// Aerodromo Beja
			pos_r[1]=38.06118;
			pos_r[0]=-7.87692;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/beja_sel.png");
			cairo_set_source_surface (cr,image, 743, 703);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/BYJ.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

		case 9:
			// Aerodromo Portimao
			pos_r[1]=37.14949;
			pos_r[0]=-8.58448;
			pos_r[2]=0;
			att_r=0;

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/portimao_sel.png");
			cairo_set_source_surface (cr,image, 745, 801);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);

			cairo_save(cr);
			image = cairo_image_surface_create_from_png ("images/PRM.png");
			cairo_set_source_surface (cr,image, 11, 410);
			cairo_new_path (cr); 
			cairo_paint (cr);
			cairo_restore(cr);
			cairo_surface_destroy (image);
			break;

	}

	// Draw Switch button ------------------------------------------
	
	cairo_save(cr);
	cairo_surface_t *image4;
	cairo_rectangle (cr, 1100,400,100,50);
	cairo_clip (cr);
	cairo_new_path (cr);
	image4 = cairo_image_surface_create_from_png ("images/on.png");
	cairo_set_source_surface (cr, image4, 1100, 400);
	cairo_paint (cr);
	cairo_restore(cr);

	cairo_surface_destroy (image4);

}