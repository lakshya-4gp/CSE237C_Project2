#include "cordiccart2pol.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE mode=s_axilite port=return
	// Write your code here
	int num_iter = NO_ITER;
	float curx = x;
	float cury = y;
	float cura = 0;

	// Rotate by 90
	int sigma = (cury > 0)? 1:-1;
	float tempx = curx;
	cura = cura + sigma*(1.5708);
	curx = sigma*cury;
	cury = -sigma*tempx;


	for(int i=0; i < num_iter; i++){
		sigma = (cury > 0)? 1:-1;
		tempx = curx;

		// Perform rotation
		curx = curx + cury*sigma*Kvalues[i];
		cury = cury - tempx*sigma*Kvalues[i];

		// update angle
		cura = cura + sigma*angles[i];
	}
	
	*theta = cura;
	*r = curx*0.60727;
}
