#include "cordiccart2pol.h"

typedef ap_fixed<16, 2, AP_RND, AP_WRAP, 1> fixed_data_t;
typedef ap_fixed<16, 3, AP_RND, AP_WRAP, 1> cura_t;

fixed_data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

cura_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE mode=s_axilite port=return

	// Write your code here
	ap_uint<5> num_iter = NO_ITER;
	fixed_data_t curx = x;
	fixed_data_t cury = y;
	cura_t cura = 0;
	fixed_data_t tempx = curx;

	// Rotate by 90
	if (cury > 0){
		cura = cura + ((cura_t)(1.5708));
		curx = cury;
		cury = -tempx;
	}else{
		cura = cura - ((cura_t)(1.5708));
		curx = -cury;
		cury = tempx;
	}

	for(int i=0; i < num_iter; i++){
		tempx = curx;

		if (cury > 0){
			// Perform rotation
			curx = curx + (cury >> i);
			cury = cury - (tempx >> i);

			// update angle
			cura = cura + angles[i];
		}else{
			// Perform rotation
			curx = curx - (cury >> i);
			cury = cury + (tempx >> i);

			// update angle
			cura = cura - angles[i];
		}
	}
	
	*theta = cura;
	*r = ((data_t)curx)*0.60727;
}
