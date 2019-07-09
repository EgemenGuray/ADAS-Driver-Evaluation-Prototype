#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "deqll.h"
#include "oracle.h"


double set_avg_fuel_cons = 20;
double set_slope = 0;
double set_load_level = 1;
int external_effect = 1;
// 1 -> highway , 2 -> rural, 3 traffic
int skill = 3;
// 1 -> james may , 2 -> serseri, 3 -> kasap


double calculate_gforce (int speed_1, int speed_2, double time){
    double x = (double) speed_1;
    double y = (double) speed_2;
    double z =  time;
    double kmh_to_mps = 0.2778;
    double ret_val = ((y - x)*kmh_to_mps)/(z*9.81);
    //printf("\n\nG-FORCE: %f\n\n", ret_val);
    return ret_val;

}
double calculate_ins_fuel(int speed, double acc, double avg_fuel_cons, double slope, int load_level){
    double ret_val;
    if(acc <= 0) {
        ret_val = avg_fuel_cons / 2;
        int r = rand() % 26; // offset 0 + 25
        int sign = rand() % 2;
        if (sign) {
            ret_val = ret_val + avg_fuel_cons * (double)r / 100;
        }else{
            ret_val = ret_val - avg_fuel_cons * (double)r / 100;
        }
    }else {
        int r = rand() % 101;
        ret_val = avg_fuel_cons * 1 + (acc * 100);

        if (slope > 0) {
                ret_val = ret_val * (1 + slope / 5);
                if(load_level == 3){
                    ret_val = ret_val * 2.5;
                }

        } else if(slope < 0){
                slope = slope * -1;
                //printf("before %f\n", ret_val);
                ret_val = ret_val / (1 + slope / 5);
        }


    }




    return ret_val;

}
double calculate_brk_point(double cur_brk_grade, double acc){

// harsh ise puan kir hars degil ise puan ver

}


double calculate_acc_point(double cur_acc_grade, double acc){

    // harsh ise puan kir hars degil ise puan ver

}

double calculate_crs_point(double cur_crs_grade, double speed, double avg_speed){

    // speeding 85+ puan kir avg speed den cok oynayan degerler var ise puan kir

}

double calculate_ant_point(double cur_ant_grade, double acc){

    // acc + - sign degisimi yuzde 50 den ne kadar offsa o kdr cok kir ne kadar az sa o kdr puan ver

}

double calculate_fuel_point(double cur_fuel_grade, double fuel, double avg_fuel){

    // avg fuel cons
}


double calculate_point(double cur_grade, double acc){


    double reward = true;
    double acc_thres = 0.20; // acceleration threshold
    double brk_thres = -0.27; // braking threshold
    double offset = 0;
    if(acc < 0){
        offset = acc - brk_thres;
        if(offset < 0) reward = false;
    }else{
        offset = acc_thres - acc;
        if(offset < 0) reward = false;
    }
    double weight_coef = ((1/sqrt(2*(22/7)*0.004*0.004)) * exp((-(cur_grade-50)*(cur_grade-50))/(2*1600)))/ 50;
    if(!reward) weight_coef = 2;
    double coef_adj = 7;

    double ret_val = coef_adj * weight_coef * offset;
    if (cur_grade + ret_val > 100.0) ret_val = cur_grade - 100;
    if (cur_grade + ret_val < 0.0) ret_val = 0 - cur_grade;
    //printf("WIEGHT: %f\n POINT: %f\n", weight_coef, ret_val);
    return ret_val;


}


int main() {

    struct dequeue *speed_deq_transmitter;
    speed_deq_transmitter = dequeue_create();

    struct dequeue *acc_deq;
    acc_deq = dequeue_create();

    struct dequeue *points_deq;
    points_deq = dequeue_create();

    struct dequeue *fuel_deq;
    fuel_deq = dequeue_create();


    srand(time(NULL));
    int x = 0;// counter for the loop
    int vehicle_speed;

    //================= CHANGE THE CONDITION HERE ==========================
    if(external_effect == 1){
        if(skill == 1){
            vehicle_speed = (rand() % 31) + 60; // vehicle speed between 60-90 (highway)
        }else if(skill == 2){
            vehicle_speed = (rand() % 14) + 80; // vehicle speed between 80-93 (highway)
        }else{
            vehicle_speed = (rand() % 7) + 90; // vehicle speed between 90-96 (highway)
        }

    }else if(external_effect == 2){
        vehicle_speed = (rand() % 21) + 20; // vehicle speed between 20-40 (rural)
    }else{
        vehicle_speed = (rand() % 15) + 15; // vehicle speed between 0-30 (traffic)
    }

    //================= CHANGE THE CONDITION HERE ==========================

    double prev_grade = 65;

    printf("[SPEED: %d]\n", vehicle_speed);
    dequeue_add_back((double)vehicle_speed, speed_deq_transmitter);
    int prev_sp = vehicle_speed;
    double ins_fuel;
    double prev_ac = 0;
    while(true){
        if(x > 399) break;

        //================= CHANGE THE CONDITION HERE ==========================
        int r = 0;

        if(external_effect == 1){
            r = rand() % 6; // offset -5 + 5 ->highway
        }else if(external_effect == 2){
            r = rand() % 9; // offset -10 + 10 -> rural
        }else{
            r = rand() % 21; // offset -20 + 20 -> traffic jam
        }


        //================= CHANGE THE CONDITION HERE ==========================

        int sign = rand() % 2;// false or negative


        if(sign){



            prev_ac = calculate_gforce((prev_sp), (vehicle_speed + r), 2);



            prev_sp = vehicle_speed + r;
            ins_fuel = calculate_ins_fuel(prev_sp, prev_ac, set_avg_fuel_cons, set_slope, set_load_level);
            printf("[SPEED: %d ACC: %f INS: %f]\n", prev_sp, prev_ac, ins_fuel);
            dequeue_add_back((double)prev_sp, speed_deq_transmitter);
            dequeue_add_back((double)prev_ac, acc_deq);
            dequeue_add_back((double)ins_fuel, fuel_deq);

        }else{

            prev_ac = calculate_gforce(prev_sp, (vehicle_speed - r), 2);




            prev_sp = vehicle_speed - r;
            ins_fuel = calculate_ins_fuel(prev_sp, prev_ac, set_avg_fuel_cons, set_slope, set_load_level);
            printf("[SPEED: %d ACC: %f INS: %f]\n", prev_sp, prev_ac, ins_fuel);
            dequeue_add_back((double)prev_sp, speed_deq_transmitter);
            dequeue_add_back((double)prev_ac, acc_deq);
            dequeue_add_back((double)ins_fuel, fuel_deq);


        }
        int offset_time = rand() % 8; // offset
        int sign_time = rand() % 2;// false or negative
        int manuel_speed_change_interval = 10;
        if(sign_time){
            manuel_speed_change_interval += offset_time;
        }else{
            manuel_speed_change_interval -= offset_time;
        }
        if(x % manuel_speed_change_interval == 0){
            int backup = vehicle_speed;

            //================= CHANGE THE CONDITION HERE ==========================

            if(external_effect == 1){
                if(skill == 1){
                    vehicle_speed = (rand() % 31) + 60; // vehicle speed between 60-90 (highway)
                }else if(skill == 2){
                    vehicle_speed = (rand() % 14) + 80; // vehicle speed between 80-93 (highway)
                }else{
                    vehicle_speed = (rand() % 7) + 90; // vehicle speed between 90-96 (highway)
                }
            }else if(external_effect == 2){
                vehicle_speed = (rand() % 21) + 20; // vehicle speed between 20-40 (rural)
            }else{
                vehicle_speed = (rand() % 15); + 15; // vehicle speed between 0-30 (traffic)
            }

            //================= CHANGE THE CONDITION HERE ==========================

            if(prev_sp - 5 <= vehicle_speed && vehicle_speed <= prev_sp + 5){
                vehicle_speed = backup;
            }else{

                prev_ac = calculate_gforce(prev_sp, vehicle_speed, 2);


                ins_fuel = calculate_ins_fuel(vehicle_speed, prev_ac, set_avg_fuel_cons, set_slope, set_load_level);

                printf("[SPEED: %d ACC: %f INS: %f]\n", vehicle_speed, prev_ac, ins_fuel);
                dequeue_add_back((double)prev_sp, speed_deq_transmitter);
                dequeue_add_back((double)prev_ac, acc_deq);
                dequeue_add_back((double)ins_fuel, fuel_deq);
            }

        }
        x++;
    }

    //printf("SPEED:\n");
    //dequeue_print(speed_deq_transmitter);
    //printf("G - FORCE:\n");
    //dequeue_print(acc_deq);
    //printf("INS FUEL:\n");
    //dequeue_print(fuel_deq);
    int *a = deq_to_array(speed_deq_transmitter);
    int *b = deq_to_array(acc_deq);
    printf("cond %d\n", traffic_cond(a, 400, b, 900));

    dequeue_print(points_deq);
    dequeue_destroy(speed_deq_transmitter);
    dequeue_destroy(acc_deq);
    dequeue_destroy(points_deq);
    dequeue_destroy(fuel_deq);
    return 0;

}