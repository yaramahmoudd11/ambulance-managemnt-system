#pragma once
#include "Time.h"
#include "Patient.h"
#include <string>
#include<iostream>
using namespace std;
//class Patient; 
//
class Car {
private:
    //int TimeStep = 0;
    int speed;
    int busyTime;
    int AssignTime;
    Patient* P = nullptr;
    int pickTime;
    int FinishTime;
    int H_ID;
    enum CarType { Spc, NC };
    enum CarStatus { Back, Out, Free };
    CarType carType;
    CarStatus carStatus;
    static int carid;
    bool failure = false;
    int ServiceTime;
    int FinishServiseTime;
public:

    Car();
    Car(int speed, int busyTime, int assignTime, Patient* P, int pickTime, int finishTime, int H_ID, CarType carType, CarStatus carStatus);
    Car(const Car& other);
    Car( Patient* other);
    Car(int speed);
    ~Car();

    void setSpeed(int speed);
    void setBusyTime(int busyTime);
    void setAssignTime(int assignTime);
    void setPatient(Patient* patient);
    void setPickTime(int pickTime);
    void setFinishTime(int finishTime);
    void setHospitalID(int H_ID);
    void setCarType(int carType);
    void setCarStatus(CarStatus carStatus);
    void SetServiseTime(int time);
    void SetFinishServiseTime(int time);


    int getSpeed() const;
    int getBusyTime() const;
    int getAssignTime() const;
    Patient* getPatient() const;
    int getPickTime() const;
    int getFinishTime() const;
    int getcarid() const;
    int getServiseTime() const;
    int getFinishServiseTime() const;

    int getHospitalID() const;
    CarType getCarType() const;
    CarStatus getCarStatus() const;

    void assignPatient(Patient* patient);
    void DropPatient();
    int calcPT(int distance);
    int calcFT();
    int calcAT();
    void cancelFT();
    bool operator==(const Car& other) const;
    //void setTime(int time);
    void fail();
    bool Gatfailure();
    void BackCarFail();
    
    friend ostream& operator<<(ostream& os, const Car* car);
};