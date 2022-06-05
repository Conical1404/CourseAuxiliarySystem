#include "Activity.h"

activity::activity(bool acType, int w, int loID, \
            String acName, String loName, Pair<Time, Time> t) {
    isPrivate = acType;
    week = w;
    locationID = loID;
    activityName = acName;
    locationName = loName;
    activityTime = t;
}

activity::activity(bool acType, int w, int loID, \
            String acName, String loName, Time start, Time end) {
    isPrivate = acType;
    week = w;
    locationID = loID;
    activityName = acName;
    locationName = loName;
    activityTime = Pair<Time, Time>(start, end);
}

int activity::getActivityType() const {
    return isPrivate ? 1:0;
}


int activity::getLocationID() const {
    return locationID;
}

int activity::getWeek() const {
    return week;
}

String activity::getActivityName() const {
    return activityName;
}

String activity::getLocationName() const {
    return locationName;
}

Pair<Time, Time> activity::getActivityTime() const {
    return activityTime;
}

void activity::changeTime(bool isStart, Time t) {
    if (isStart)
        activityTime.first = t;
    else
        activityTime.second = t;
}

void activity::changeTime(Time t1, Time t2) {
    activityTime.first = t1;
    activityTime.second = t2;
}


void activity::changeTime(Pair<Time, Time> t) {
    activityTime = t;
}
