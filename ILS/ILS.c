//*********** ILS.c *****************
// função que cria uma thread para que o Visual corra e, em paralelo, 
// cria uma socket UDP para receber dados provenientes de tanto o grupo 
// da atitude como da posição num ciclo infinito em que está constantemente 
// à espera de novos dados. Os dados são tratados, convertidos para a sua 
// posição no ecrã em pixeis, e as variáveis globais correspondentes são alteradas.

#include "ILS.h"

// GLOBAL VARIALES -------
bool visual_flag_pos=false;
bool visual_flag_att=false;

/*-------Data for drawing-------*/
// Map big
int map_big_px=0;
int map_big_py=0;
int map_big_yaw=0;

// Map small
int map_small_px=0;
int map_small_py=0;
int map_small_yaw=0;

// Runway
int runway_pz=0;
int runway_px=0;
int runway_py=0;
float altitude_a=0;

// ILS indicator
int  ILS_heading=0;
bool ILS_flag=false;
int  ILS_x=0;
int  ILS_y=0;
bool ILS_outer_marker=false;
bool ILS_middle_marker=false;
bool ILS_inner_marker=false;

// ATT indicator
int ATT_pitch=0;
int ATT_roll=0;

// Airport
float pos_r[3];
float att_r;

//*********** planify *****************
// Função que recebe dados de atitude e posição, tanto da aeronave
// como da pista de aterragem e as converte para unidades de distância
void planify(float* pos_a, float* pos_r, float* pos_a_m, float* pos_r_m)
{

	// Distancia

	float R = 6371000; // metres
	float phi_1 = pos_a[0]*DEG2RAD;
	float phi_2 = pos_r[0]*DEG2RAD;
	float d_phi = (pos_r[0]-pos_a[0])*DEG2RAD;
	float d_lambda = (pos_r[1]-pos_a[1])*DEG2RAD;

	float a = sin(d_phi/2) * sin(d_phi/2) +cos(phi_1) * cos(phi_2) *sin(d_lambda/2) * sin(d_lambda/2);
	float d = R* 2 * atan(sqrt(a)/ sqrt(1-a));

	// Bearing
	float y = sin(d_lambda) * cos(phi_2);
	float x = cos(phi_1)*sin(phi_2)-
				sin(phi_1)*cos(phi_2)*cos(d_lambda);
	float brng = atan2(y, x);

	// x,y position
	pos_a_m[0]=d*cos(brng);
	pos_a_m[1]=d*sin(brng);
	pos_a_m[2]=pos_a[2];

	pos_r_m[0]=0;
	pos_r_m[1]=0;
	pos_r_m[1]=pos_r[2];
}


//*********** ILS_data_pos *****************
// Função que calcula os vários desvios em relação ao trajeto correto
// da aeronave, assim como distâncias em pixeis para desenhar no Visual.
// Também calcula as elipses da aeronave a aterrar e a posição da
// aeronave no mapa de Portugal.
void ILS_data_pos(float* pos_a, float* att_a, float* pos_r, float att_r){

	float vertical_sep	=0;
	float horizontal_sep=0;

	// Map pixels-----------------------------------------------------------------------------

	map_big_px		=(int) (LON_2*pow(pos_a[0],2)+LON_1*pos_a[0]+LON_0);
	map_big_py		=(int) (LAT_2*pow(pos_a[1],2)+LAT_1*pos_a[1]+LAT_0);
	map_big_yaw		=(int) att_a[2];

	map_small_px	=(int) (LON_2*pow(pos_a[0],2)+LON_1*pos_a[0]+LON_0)*0.05*0.82*0.9;
	map_small_py	=(int) (LAT_2*pow(pos_a[1],2)+LAT_1*pos_a[1]+LAT_0)*0.05*0.82*0.9;
	map_small_yaw	=(int) att_a[2];

	// Converting latitude and longitude to meters---------------------------------------------

	float pos_a_m[3], pos_r_m[3];
	planify(pos_a, pos_r, pos_a_m, pos_r_m);

	// Calculations ILS ------------------------------------------------------------------------
	float a_glide_slope=0;
	float a_deviation=0;

	// Glide Slope

	a_glide_slope = atan2(pos_a_m[2]-pos_r_m[2],sqrt(pow(pos_r_m[0]-pos_a_m[0],2)+pow(pos_r_m[1]-pos_a_m[1],2)))/DEG2RAD-3;

	// Deviation

	a_deviation = att_r - atan2(pos_a_m[1]-pos_r_m[1],pos_a_m[0]-pos_r_m[0])/DEG2RAD;

	while (a_deviation < -180) a_deviation += 360;
	while (a_deviation > 180) a_deviation -= 360;


	// Disturbances

	// False Glide Slope--------

	if (a_glide_slope>10)
		a_glide_slope=a_glide_slope-12;

	// Write result--------

	ILS_x=(int) (a_deviation*SCALE_ILS);
	ILS_y=(int) (a_glide_slope*SCALE_ILS);

	// ILS flag if within Range------------------------------------

	double distance=sqrt(pow(pos_a_m[0]-pos_r_m[0],2)+pow(pos_a_m[1]-pos_r_m[1],2));

	// Localizer Range-----

	if((distance<=LOC_SMALL_R && a_deviation<=abs(LOC_SMALL_ANG)) || (distance<=LOC_LARGE_R && a_deviation<=abs(LOC_LARGE_ANG)))
		ILS_flag=true;
	else {
		ILS_flag=false;
		ILS_x=0;
		ILS_y=0;
	}

	// Glide Slope Range (if outside range and within localizes GS needle dissapears)----

	if(!(distance<=GS_R && a_deviation<=abs(GS_ANG)) && ILS_flag)
		ILS_y=1000;
	
	// Runway coordinates---------------------------

	runway_pz	= (int) ((pos_a_m[2]-pos_r_m[2])/7);
	runway_px	=1000-(int) ( cos(att_r*DEG2RAD)*(pos_a_m[0]-pos_r_m[0])+sin(att_r*DEG2RAD)*(pos_a_m[1]-pos_r_m[1]))/7;
	runway_py	=	  (int) (-sin(att_r*DEG2RAD)*(pos_a_m[0]-pos_r_m[0])+cos(att_r*DEG2RAD)*(pos_a_m[1]-pos_r_m[1]))/7;

	altitude_a 	=pos_a_m[2];

	// Marker positions-----------------------------------------------------------------------------

	float a=(pos_a_m[2]-pos_r_m[2]+140)*sin(MARKER_ANGx*DEG2RAD);
	float b=(pos_a_m[2]-pos_r_m[2]+140)*sin(MARKER_ANGy*DEG2RAD);

	float inner_x=INNER_MARKER*cos(att_r*DEG2RAD)+pos_r_m[0];
	float inner_y=INNER_MARKER*sin(att_r*DEG2RAD)+pos_r_m[1];

	float middle_x=MIDDLE_MARKER*cos(att_r*DEG2RAD)+pos_r_m[0];
	float middle_y=MIDDLE_MARKER*sin(att_r*DEG2RAD)+pos_r_m[1];

	float outer_x=OUTER_MARKER*cos(att_r*DEG2RAD)+pos_r_m[0];
	float outer_y=OUTER_MARKER*sin(att_r*DEG2RAD)+pos_r_m[1];

	// Inner Marker Condition flag

	if ((  pow((cos(att_r*DEG2RAD)*(pos_a_m[0]-inner_x)+sin(att_r*DEG2RAD)*(pos_a_m[1]-inner_y))/a,2)
		+  pow((sin(att_r*DEG2RAD)*(pos_a_m[0]-inner_x)-cos(att_r*DEG2RAD)*(pos_a_m[1]-inner_y))/b,2))<=1
		&& pos_a_m[2]<=MARKER_MAX_HEIGHT)
	{
		ILS_inner_marker=true;
	}
	else ILS_inner_marker=false;

	// Middle Marker Condition flag

	if ((  pow((cos(att_r*DEG2RAD)*(pos_a_m[0]-middle_x)+sin(att_r*DEG2RAD)*(pos_a_m[1]-middle_y))/a,2)
		+  pow((sin(att_r*DEG2RAD)*(pos_a_m[0]-middle_x)-cos(att_r*DEG2RAD)*(pos_a_m[1]-middle_y))/b,2))<=1
		&& pos_a_m[2]<=MARKER_MAX_HEIGHT)
	{
		ILS_middle_marker=true;
	}
	else ILS_middle_marker=false;


	// Outer Marker Condition flag

	if ((  pow((cos(att_r*DEG2RAD)*(pos_a_m[0]-outer_x)+sin(att_r*DEG2RAD)*(pos_a_m[1]-outer_y))/a,2)
		+  pow((sin(att_r*DEG2RAD)*(pos_a_m[0]-outer_x)-cos(att_r*DEG2RAD)*(pos_a_m[1]-outer_y))/b,2))<=1
		&& pos_a_m[2]<=MARKER_MAX_HEIGHT)
	{
		ILS_outer_marker=true;
	}
	else ILS_outer_marker=false;

	// In case of error flag

	if(ILS_inner_marker==true && ILS_outer_marker==true && ILS_middle_marker==true){
		ILS_inner_marker=false;
		ILS_middle_marker=false;
		ILS_outer_marker=false;
	}

	// Set Flag for Visual drawing
	visual_flag_pos=true;

	return;
}

//*********** ILS_data_att *****************
// Função que recebe dados de atitude da aeronave e as 
// transforma em pixeis, para enviar para o Visual
void ILS_data_att(float* att_a)
{

	ILS_heading=att_a[2];
	ATT_pitch=(int) att_a[0]*(2.7);
	ATT_roll=(int) att_a[1];

	visual_flag_att=true;
	return;
}

//*********** die *****************
// Função que termina o programa caso um erro ocorra
void die(char *s)
{
    perror(s);
    exit(1);
}

//*********** main do ILS.c *****************
// Main do ILS.c. Função que cria uma thread para o Visual,
// e depois corre infinitamente para receber dados de clientes.
int main(int argc, char *argv[]) {

	// Socket variables----------------------------------
	struct sockaddr_in si_me, si_other;
    int s, i, slen = sizeof(si_other) , recv_len;
	char data[DATA_SIZE];
	int id=0;

	// Data variables------------------------------------
	float pos_a[3], att_a[3];

	//Aeroporto de Lisboa de predefinição
	n_aeroporto=0;
	pos_r[1]=38.77559;
	pos_r[0]=-9.13536;
	pos_r[2]=0; 
	att_r=59; 

	// Initiating socket connection----------------------
    //Create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT_N);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

	// Initiating visual thread------------------------
	pthread_t t1;
	ArgCV args;
	args.argc = argc;
	args.argv = argv;
	pthread_create(&t1, NULL, visual, &args);


	//--- loop wait on a connection ---
	while ( 1 ) {

        memset(data, 0, sizeof(data));

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, data, DATA_SIZE, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        // Issue with float number separation
		for (int i = 0; i < strlen(data)-2; ++i)
		{
			if (data[i] == '.')
			{
				data[i] = ',';
			}
		}

		// Prints received message
		printf("data %s \n", data);

		// Scans data from attitude
		if (data[0]==ID_ATT)
		{
			if (sscanf(data, "%*d %f %f %f\n", &att_a[0], &att_a[1], &att_a[2])!=0)
			ILS_data_att(att_a);
		}
		// scan data from position
		else if (data[0]==ID_POS)
		{
			if (sscanf(data, "%*d %*f %*f %*f %f %f %f %*f %*f\n", &pos_a[0], &pos_a[1], &pos_a[2])!=0){
				pos_a[2]=pos_a[2];
				ILS_data_pos(pos_a, att_a, pos_r, att_r);
			}
		}
	}

	close(s);
	return 0;
}
