//
//  mdp.h
//  simulator
//
//  Created by Enkhjargalyn Nyam-Ochir on 2/22/17.
//  Copyright © 2017 Lufan Zhou. All rights reserved.
//

#ifndef mdp_h
#define mdp_h

#include <vector>
#include <random>
using namespace std;

class MDP{
public:
    double ball_x;
    double ball_y;
    double velocity_x;
    double velocity_y;
    double paddle_y;
    double paddle_height;
    vector<double> actions;

    MDP(){
        ball_x=0.5;
        ball_y=0.5;
        velocity_x=0.03;
        velocity_y=0.01;
        paddle_y=0.4;
        paddle_height = 0.2;
        actions = {0, 0.04, -0.04};
    };
    ~MDP(){};
    
    int simulate_one_time_step(int action_selected){
        
        
        
        random_device rd;
        mt19937_64 mt(rd());
        uniform_real_distribution<double> distributionU(-0.015, 0.015);
        uniform_real_distribution<double> distributionV(-0.03, 0.03);
        
        ball_x += velocity_x;
        ball_y += velocity_y;
        if(action_selected == 1) paddle_y += 0.04;
        if(action_selected == 2) paddle_y -= 0.04;
        
        if(paddle_y > 0.8) paddle_y = 1.6 - paddle_y;
        if(paddle_y < 0) paddle_y = - paddle_y;
            
        if(ball_y < 0){
            ball_y = -ball_y;
            velocity_y = -velocity_y;
        }

        if(ball_y > 1){

            ball_y = 2 - ball_y;
            velocity_y = -velocity_y;
        }

        if(ball_x < 0){

            ball_x = -ball_x;
            velocity_x = -velocity_x;
        }
        int bounced = 0;
        
        if(ball_x > 1 && ball_y >= paddle_y && ball_y <= paddle_y + paddle_height){
            bounced = 1;

            ball_x = 2 - ball_x;
            double U = distributionU(mt);
            double V = distributionV(mt);
            velocity_x = -velocity_x + U;
            velocity_y = velocity_y + V;

            
            if(velocity_x < 0.03 && velocity_x >=0)
                velocity_x = 0.031;
            if(velocity_x > -0.03 && velocity_x < 0)
                velocity_x = -0.031;
            
        }

        return bounced;
        
    };

    
    int discretize_state(){
        int dx = int(ball_x/(double(1)/12));
        int dy = int(ball_y/(double(1)/12));
        int dvx = 0;
        int dvy = 0;
        int dp = int(12 * paddle_y / (1 - 0.2));
        
        if(velocity_x < 0)
            dvx = 1;
        
        if(velocity_y > 0.015)
            dvy = 1;
        
        if(velocity_y < 0.015)
            dvy = 2;
        
        if(paddle_y == 1 - 0.2)
            dp = 11;
        
        //cout<<dx<<" "<<dy<<" "<<dvx<<" "<<dvy<<" "<<dp<<endl;
        //cout<<"paddle_y"<<paddle_y<<endl;
            
            // (144)(2)(3)(12)+1 = 10369
            // 0 - 10367 10368
        int discrete = ((((dx * 12 + dy)*2 + dvx)*3 + dvy)*12 + dp);
        if(ball_x > 1)
            discrete = 10368;
        
        return discrete;
        
    
    };


};




#endif /* mdp_h */
