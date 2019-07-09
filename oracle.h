//
// Created by Egemen Ihsan Guray on 7/9/18.
//

#ifndef VEHICLEEVAL_ORACLE_H
#define VEHICLEEVAL_ORACLE_H

#endif //VEHICLEEVAL_ORACLE_H

int road_cond(double *a, int count);


int traffic_cond(double *a, int count, double *b, int count_acc);

double get_gforce (double speed_1, double speed_2, double time);

double *acc_array(double *a, int count, double time);

