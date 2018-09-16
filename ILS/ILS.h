#ifndef CLASS_H
#define CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h> 

// For visual
#include <cairo.h>
#include <gtk/gtk.h>

#define PORT_N 		6000
#define DATA_SIZE 	32

#define PI 			3.14159265
#define DEG2RAD		(PI/180.0)
#define ID_ATT		'1'
#define ID_POS		'2'

// Map interpolation
static float LAT_2=-13.458254;
static float LAT_1=-825.125669;
static float LAT_0=58975.358300;

static float LON_2=-0.030996;
static float LON_1=1455.970051;
static float LON_0=15131.019990;

// Runway interpolation
#define SCALE_RUNWAY 		(1/7)
// ILS interpolation
#define SCALE_ILS 			(14.0/0.5)
// ATT interpolation
#define SCALE_ATT 			(10/27)

#define LOC_SMALL_R			31500
#define LOC_SMALL_ANG		10
#define LOC_LARGE_R			46300
#define LOC_LARGE_ANG		35
#define GS_R				18520
#define GS_ANG				8

#define OUTER_MARKER 		7000  
#define MIDDLE_MARKER 		1050
#define INNER_MARKER 		300

#define MARKER_ANGy 		85.0
#define MARKER_ANGx 		40.0
#define MARKER_MAX_HEIGHT 	1828

#define WIDTH_IM			642
#define	HEIGHT_IM			405
#define WIDTH_W				950
#define	HEIGHT_W			400


typedef struct ArgCV {
    int argc;
    char **argv;
} ArgCV;

// GLOBAL VARIALES -------
extern bool visual_flag_pos;
extern bool visual_flag_att;

/*Data for drawing*/
// Map big
extern int map_big_px;
extern int map_big_py;
extern int map_big_yaw;

// Map small
extern int map_small_px;
extern int map_small_py;
extern int map_small_yaw;

// Runway
extern int runway_pz;
extern int runway_px;
extern int runway_py;
extern float altitude_a;

// ILS indicator
extern int ILS_heading;
extern bool ILS_flag;
extern int ILS_x;
extern int ILS_y;
extern bool ILS_outer_marker;
extern bool ILS_middle_marker;
extern bool ILS_inner_marker;

// ATT indicator
extern int ATT_pitch;
extern int ATT_roll;

// Airport
extern float pos_r[3];
extern float att_r;
extern int n_aeroporto;
extern bool flag_control;

void *visual(void* param);

void Runway_drawing(cairo_t *cr, cairo_operator_t op);

void Control_pannel_drawing(cairo_t *cr, cairo_operator_t op);

void Map_drawing(cairo_t *cr, cairo_operator_t op);

void ILS_ind_drawing(cairo_t *cr, cairo_operator_t op);

void ATT_ind_drawing(cairo_t *cr, cairo_operator_t op);

void Markers_ind_drawing(cairo_t *cr, cairo_operator_t op);

void Borders_drawing(cairo_t *cr, cairo_operator_t op);

#endif