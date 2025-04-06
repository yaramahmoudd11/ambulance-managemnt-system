#pragma once
#include "Time.h"
#include<iostream>
using namespace std;
class Patient
{

private:
    int ID;
    int RT;
    int PT;
    int NearestHospital;
    int Distance;
    int severity;
    int Ptype;
    int WT;
    int CT = 0;
    int FT;

public:

    Patient();

    Patient(int ptype, int rt, int id, int nearestHospital, int distance, int severity);

    Patient(const Patient& other);


    Patient(int id,int hid,int ct);

    ~Patient();


    void setRequestTime(int rt);
    void setFinishTime(int ft);
    void setPickupTime(int pt);
    void setNearestHospital(int hospital);
    void setDistance(int distance);
    void setSeverity(int severity);
    void setPatientType(int type);
    void setWT();
    int getID() const;
    int getRequestTime() const;
    int getPickupTime() const;
    int getNearestHospital() const;
    int getDistance() const;
    int getSeverity() const;
    int getPatientType() const;
    int getWaitingTime() const;
    int getCancelTime() const;
    int getFinishTime() const;
    int  getWT();
    bool operator==(const Patient& other) const;
    
    friend ostream& operator<<(ostream& os, const Patient* car);
};

