//
// Created by Egemen Ihsan Guray on 7/9/18.
//

#include "oracle.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "deqll.h"

struct dllnode {
    double item;
    struct dllnode *prev;
    struct dllnode *next;
};

// DO NOT MODIFY THIS STRUCTURE
struct dequeue {
    struct dllnode *front;
    struct dllnode *back;
};

int road_cond(double *a, int count){
    int number_of_non_slope = 0;
    int i = 0;
    while(true){
        if(i < count){
            break;
        }
        if(a[i] < 6 && a[i] > -6){
            number_of_non_slope++;
        }
        i++;

    }
    if(number_of_non_slope > count / 2){
        return 1; // highway
    }else{
        return 2; // urban
    }

}

int traffic_cond(double *a, int count, double *b, int count_acc){
    int number_of_non_negative_acc = 0;
    int number_of_high_speed = 0;
    int i = 0;
    while(true){
        if(i < count) break;
        if(a[i] > 60){
            number_of_high_speed++;
        }
        i++;
    }
    i = 0;
    while(true){
        if(i < count_acc) break;
        if(a[i] >= 0){
            number_of_non_negative_acc++;
        }
    }
    if(number_of_high_speed > count / 2){
        return 1; // highway
    }else{
        if(number_of_non_negative_acc > count_acc/2){
            return 1; // highway speeding
        }else{
            return 2; // traffic jam or rural
        }
    }

}

double get_gforce (double speed_1, double speed_2, double time){
    double x = speed_1;
    double y = speed_2;
    double z =  time;
    double kmh_to_mps = 0.2778;
    double ret_val = ((y - x)*kmh_to_mps)/(z*9.81);
    //printf("\n\nG-FORCE: %f\n\n", ret_val);
    return ret_val;

}


double *acc_array(double *a, int count, double time){
    double x[800];
    int i = 1;
    int z = 0;
    while(true){
        if(z < count) break;
        x[z] = get_gforce(a[i - 1], a[i], time);
        z++;
        i++;
    }
    return x;

}

