#include <iostream>
#include <cmath>
#include <fstream>
#include "FlightLib.h"

FlightLib flight;

int main() {
	float n = 1;
	float v = 50;
	float w = 15;
	float s = 7;
	float ar = 8;
	float c_d_0 = 0.02;
	float c_l_max = 1.2;

	std::cout << "Vs: " << flight.v_s(w, n, s,  c_l_max) << "\n";
	std::cout << "Vx: " << flight.v_gamma(w, n, s, ar, c_d_0) << "\n";
	std::cout << "Vy: " << flight.v_vy(w, n, s, ar, c_d_0) << "\n";

	/*
	std::ofstream myfile;
	myfile.open("example.csv");

	while (t < t_sweep) {
		
		y = source.doublet(t, t_start, width, delta_y, y_init);
		yf = filter.rate_saturation(ybf, y, dt, y_dt_min, y_dt_max);

		myfile << t << "," << y << "," << yf << "\n";

		xbf = y;
		ybf = yf;
		t += dt;
	}

	myfile.close();*/
}