# include "headers.h"

vector<Courier>couriers;


int priority_value(const string& p){
   if(p == "high") return 3;
   if(p == "medium") return 2;
   if(p == "low") return 1;
   return 0;
}

bool compare_priority(const Courier& a , const Courier& b){
    return a.priority_value > b.priority_value;
}

void read_courier(const string& filename){
    ifstream infile(filename);

    int dest;
    string prio;

    while(infile>>dest>>prio){
        couriers.push_back({dest,prio,priority_value(prio)});
    }

    
    sort(couriers.begin(), couriers.end(), compare_priority);
}
