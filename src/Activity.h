#pragma once
#include <stdlib.h>
#include "Basic.h"
#include "String.h"
#include "Vector.h"
#include "Pair.h"

class activity {
 private:
    bool isPrivate;
    int week;
    int locationID;
    String activityName;
    String locationName;
    Pair<Time, Time> activityTime;

 public:
    activity(bool acType, int w, int loID, \
             String acName, String loName, Pair<Time, Time> t);
    activity(bool acType, int w, int loID, \
             String acName, String loName, Time start, Time end);
    int getActivityType() const;
    int getLocationID() const;
    int getWeek() const;
    String getActivityName() const;
    String getLocationName() const;
    Pair<Time, Time> getActivityTime() const;
    void changeTime(bool isStart, Time t);
    void changeTime(Time t1, Time t2);
    void changeTime(Pair<Time, Time> t);
};
