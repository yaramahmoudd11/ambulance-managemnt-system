#include "Patient.h"
#include<iostream>
Patient::Patient()
    : ID(0), RT(0), PT(0), NearestHospital(0), Distance(0), severity(0), Ptype(0), WT(0)
{
}

Patient::Patient(int ptype, int rt, int id, int nearestHospital, int distance, int severity)
    : Ptype(ptype), RT(rt), ID(id), NearestHospital(nearestHospital), Distance(distance), severity(severity)
{
    PT = 0;
    WT = PT - RT;
}

Patient::Patient(const Patient& other)
    : ID(other.ID), RT(other.RT), PT(other.PT), NearestHospital(other.NearestHospital),
    Distance(other.Distance), severity(other.severity), Ptype(other.Ptype), WT(other.WT)
{
}

Patient::Patient(int id, int hid, int rt)
    : ID(id), RT(0), PT(0), NearestHospital(hid), Distance(0), severity(0), Ptype(0), WT(0), CT(rt)
{
}

Patient::~Patient()
{

}

void Patient::setFinishTime(int ft)
{
    FT = ft;
}
void Patient::setWT()
{
    WT = RT - PT;
}
int Patient::getWT()
{
    return WT;
}
void Patient::setRequestTime(int rt)
{
    RT = rt;
}

void Patient::setPickupTime(int pt)
{
    PT = pt;
    WT = PT - RT;
}

void Patient::setNearestHospital(int hospital)
{
    NearestHospital = hospital;
}

void Patient::setDistance(int distance)
{
    Distance = distance;
}

void Patient::setSeverity(int severity)
{
    severity = severity;
}

void Patient::setPatientType(int type)
{
    Ptype = type;
}

int Patient::getID() const
{
    return ID;
}

int Patient::getRequestTime() const
{
    return RT;
}
int Patient::getFinishTime() const
{
    return FT;
}

int Patient::getPickupTime() const
{
    return PT;
}

int Patient::getNearestHospital() const
{
    return NearestHospital;
}

int Patient::getDistance() const
{
    return Distance;
}

int Patient::getSeverity() const
{
    return severity;
}

int Patient::getPatientType() const
{
    return Ptype;
}

int Patient::getWaitingTime() const
{
    return WT;
}

int Patient::getCancelTime() const { return CT; }

bool Patient::operator==(const Patient& other) const {
    return this->ID == other.ID;
}


ostream& operator<<(ostream& os, const Patient* car)
{
    os << car->getID() << ", ";  // Assuming Patient class has getID()
    return os;
}
