//
//  simulator.h
//  simulator
//
//

#ifndef simulator_h
#define simulator_h

#include <vector>
#include <cmath>
#include "mdp.h"


class Simulator{
public:
    int num_games;
    float alpha_value;
    float gamma_value;
    float epsilon_value;
    MDP mdp;
    vector<vector<double>> Q;
    
    
    Simulator(int ng, double alp, double gamma, double ep){
        num_games = ng;
        alpha_value = alp;
        gamma_value = gamma;
        epsilon_value = ep;
        vector<double> entry = {0,0,0};
        for(int i = 0; i < 10369; i++)
            Q.push_back(entry);
        mdp = MDP();
    };
    
    ~Simulator(){};
    
    int f_function(){
        
        random_device rd;
        mt19937_64 mt(rd());
        uniform_real_distribution<double> distribution(0, 1);
        double x = distribution(mt);
        if(x < epsilon_value){
            srand(unsigned(time(NULL)));
            return rand() % 3;
        }
        else{
            int state = mdp.discretize_state();
            int action_selected = 0;
            for(int i =0; i < 3; i++){
                if(Q[state][i] > Q[state][action_selected])
                    action_selected = i;
            }
            return action_selected;
        }
        
        
    };
    
    void train_agent(){
        for(int i = 0; i < 100000; i++){
            //cout<<"trainning round: "<<i<<endl;
            mdp = MDP();
            int olddstate = mdp.discretize_state();
            int newdstate;
            int action_selected;
            int bounced;
            int reward;
            
            while(1){
                action_selected = f_function();
                bounced = mdp.simulate_one_time_step(action_selected);
                newdstate = mdp.discretize_state();
                
                reward = 0;
                if(newdstate == 10368)
                    reward = -1;
                if(bounced == 1)
                    reward = 1;
                
                double max = -__DBL_MAX__;
                for(int i = 0; i < 3; i++){
                    if(max < Q[newdstate][i]) max = Q[newdstate][i];
                }
                
                double temp = (reward + gamma_value * max - Q[olddstate][action_selected]);
                Q[olddstate][action_selected] += alpha_value * temp;
                if(newdstate == 10368)break;
                olddstate = newdstate;
            
            }
        }
        cout<<"done training"<<endl;

    
    }
    
    void playgame(){
        int total_boucne = 0;
        for(int i = 0; i < num_games; i++){
            mdp = MDP();
            int ct = 0;
            while(mdp.discretize_state() != 10368){
                int action_selected = f_function();

                int bounced = mdp.simulate_one_time_step(action_selected);
        
                if(bounced){
                    ct += 1;
                }
            }
            
            total_boucne += ct;
        }
        total_boucne /= num_games;
        cout<<"avrg score: "<<total_boucne<<endl;
    }
    
};


#endif /* simulator_h */
