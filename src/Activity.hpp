#pragma once
#include <stdlib.h>
#include "Basic.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Pair.hpp"

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
             String acName, String loName, Pair<Time, Time> t) {
        isPrivate = acType;
        week = w;
        locationID = loID;
        activityName = acName;
        locationName = loName;
        activityTime = t;
    }
    activity(bool acType, int w, int loID, \
             String acName, String loName, Time start, Time end) {
        isPrivate = acType;
        week = w;
        locationID = loID;
        activityName = acName;
        locationName = loName;
        activityTime = Pair<Time, Time>(start, end);
    }
    int getActivityType() const {
        return isPrivate ? 1:0;
    }
    int getLocationID() const {
        return locationID;
    }
    int getWeek() const {
        return week;
    }
    String getActivityName() const {
        return activityName;
    }
    String getLocationName() const {
        return locationName;
    }
    Pair<Time, Time> getActivityTime() const {
        return activityTime;
    }
    void changeTime(bool isStart, Time t) {
        if (isStart) activityTime.first = t;
        else
            activityTime.second = t;
    }
    void changeTime(Time t1, Time t2) {
        activityTime.first = t1;
        activityTime.second = t2;
    }
    void changeTime(Pair<Time, Time> t) {
        activityTime = t;
    }
};
