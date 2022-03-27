#include<stdio.h>
#include "Calendar.hpp"
#include "Pair.hpp"
#include "Basic.hpp"

inline void func(bool b){
    if(b==true) printf("success\n");
    else printf("failed\n");
}

int main(){
    Time t1(1,13,0);
    Time t2(1,13,45);
    Time t3(1,13,45);
    Time t4(1,14,30);
    Time t5(1,13,50);
    Time t6(1,13,10);
    Time t7(1,13,30);
    Pair<Time,Time> tt[10];
    int n = 5;
    tt[0] = Pair<Time,Time>(t1,t2);// 13:00-13:45
    tt[1] = Pair<Time,Time>(t3,t4);// 13:45-14:30
    tt[2] = Pair<Time,Time>(t5,t4);// 13:50-14:40
    tt[3] = Pair<Time,Time>(t6,t7);// 13:10-13:30
    tt[4] = Pair<Time,Time>(t6,t5);// 13:10-13:50
    segmentTree w;
    bool s;
    for(int i=0;i<n;i++){
        s = w.insert(tt[i]);
        func(s);
    }
    w.remove(tt[0]);
    s = w.insert(tt[3]);
    func(s);
}
