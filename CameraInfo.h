#pragma once

// Hands 2017 2.2M Challenge camera info (Intel RealSense SR300), see "Camera info.txt" included in the challenge data
#define focus_x 475.065948
#define focus_y 475.065857
#define u_0 315.944855
#define v_0 245.287079

#define focus_x_MSRA 241.42
#define focus_y_MSRA 241.42

#define focus_x_ICVL 241.42
#define focus_y_ICVL 241.42

#define u_0_MSRA 160
#define v_0_MSRA 120
#define u_0_ICVL 160
#define v_0_ICVL 120

double projection_u(double x, double z);
double projection_v(double y, double z);
double recover_x(double u, double d);
double recover_y(double v, double d);

double projection_u_MSRA(double x, double z);
double projection_v_MSRA(double y, double z);
double recover_x_MSRA(double u, double d);
double recover_y_MSRA(double v, double d);

double projection_u_ICVL(double x, double z);
double projection_v_ICVL(double y, double z);
double recover_x_ICVL(double u, double d);
double recover_y_ICVL(double v, double d);