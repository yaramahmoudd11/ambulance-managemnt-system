#include "Car.h"
#include <iostream>
#include <string>
using namespace std;
int Car::carid = 0;
Car::Car()
    : speed(0), busyTime(0), AssignTime(0), P(nullptr), pickTime(0), FinishTime(0), H_ID(0), carType(NC), carStatus(Free) {
    carid++;
}

Car::Car(int s, int bT, int aT, Patient* PP, int pT, int fT, int ID, CarType T, CarStatus S)
    : speed(s), busyTime(bT), AssignTime(aT), P(PP), pickTime(pT), FinishTime(fT), H_ID(ID), carType(T), carStatus(S) {
    carid++;
}
Car::Car( Patient* other)
    : speed(0), busyTime(0), AssignTime(0), P(other), pickTime(0), FinishTime(0), H_ID(0), carType(NC), carStatus(Free) {
    carid++;
}

Car::Car(const Car& other)
    : speed(other.speed), busyTime(other.busyTime), AssignTime(other.AssignTime), pickTime(other.pickTime),
    FinishTime(other.FinishTime), H_ID(other.H_ID), carType(other.carType), carStatus(other.carStatus) {
    if (other.P) {
        P = new Patient(*other.P);
    }
    else {
        P = nullptr;
    }
}

Car::Car(int s)
    :speed(s), busyTime(0), AssignTime(0), P(nullptr), pickTime(0), FinishTime(0), H_ID(0), carType(NC), carStatus(Free) {
    carid++;
}


Car::~Car() {
    delete P;
    P = nullptr;
}

void Car::setSpeed(int speed) { this->speed = speed; }
void Car::setBusyTime(int busyTime) { this->busyTime += busyTime; }
void Car::setAssignTime(int assignTime) { this->AssignTime = assignTime; }
void Car::setPatient(Patient* patient) { this->P = patient; }
void Car::setPickTime(int pickTime) { this->pickTime = pickTime; }
void Car::setFinishTime(int finishTime) { this->FinishTime = finishTime; }
void Car::setHospitalID(int H_ID) { this->H_ID = H_ID; }
void Car::setCarType(int carType) { 
    if (carType == 0)
    {
        this->carType = NC;
    }
    else
    {
        this->carType = Spc;
    }
}
void Car::setCarStatus(CarStatus carStatus) { this->carStatus = carStatus; }

void Car::SetServiseTime(int time)
{
    ServiceTime = time;
}

void Car::SetFinishServiseTime(int time)
{
    FinishServiseTime = time + ServiceTime;
}

int Car::getSpeed() const { return speed; }
int Car::getBusyTime() const { return busyTime; }
int Car::getAssignTime() const { return AssignTime; }
Patient* Car::getPatient() const { return P; }
int Car::getPickTime() const { return pickTime; }
int Car::getFinishTime() const { return FinishTime; }
int Car::getcarid() const { return carid; }

int Car::getServiseTime() const { return ServiceTime; }

int Car::getFinishServiseTime() const
{
    return FinishServiseTime;
}

int Car::getHospitalID() const { return H_ID; }
Car::CarType Car::getCarType() const { return carType; }
Car::CarStatus Car::getCarStatus() const { return carStatus; }


int Car::calcFT()
{
    return TimeStep;
}
int Car::calcAT() {
    return TimeStep;
}
void Car::assignPatient(Patient* patient)
{
    calcAT();
    pickTime = TimeStep + (patient->getDistance() / speed);
    patient->setPickupTime(pickTime);
    FinishTime = pickTime + (patient->getDistance() / speed);
    patient->setFinishTime(FinishTime);
    setPatient(patient);
}

void Car::DropPatient()
{
    setPatient(nullptr);
    calcFT();
}
int Car::calcPT(int distance)
{
    int s = getSpeed();
    int at = getAssignTime();
    return at + (distance / s);
}
void Car::cancelFT()
{
    FinishTime = 2 * TimeStep - AssignTime;
    
}
bool Car::operator==(const Car& other) const {
    return this->P == other.P;
}

//void Car::setTime(int time)
//{
//    TimeStep = time;
//}

void Car::fail()
{
    failure = true;
    FinishTime = 2 * TimeStep - AssignTime;
}

bool Car::Gatfailure()
{
    return failure;
}

void Car::BackCarFail()
{
    failure = true;
    int distance_left = (speed) * (FinishTime - TimeStep);
    P->setDistance(distance_left);

}


ostream& operator<<(ostream& os, const Car* car)
{
    if (car->getCarType() == 0) { os << "N"; }
    if (car->getCarType() == 1) { os << "S"; }
    if (car->failure)
    {
        os << car->getcarid() << "_H" << car->getHospitalID() + 1 << ", ";
    }
    else if (car->P == nullptr)
    {
        os << car->getcarid() << "_H" << car->getHospitalID() + 1 << ", ";
    }
    else
    {
        os << car->getcarid() << "_H" << car->getHospitalID() + 1 << "_P" << car->getPatient()->getID() << ", ";
    }
    return os;
}
