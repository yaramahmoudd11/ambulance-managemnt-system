#include "Hospital.h"
#include <iostream>
#include <string>
#include "LinkedQueue.h"
#include "Patient.h"
#include "Car.h"
#include "priQueue.h"
#include "CancelQueue.h"

Hospital::Hospital() :
    patient(NULL), car(NULL), no_nc(0), no_sc(0), free_nc(0), free_sc(0), id(0), no_EP(0) {}

Hospital::Hospital(int nc, int speed1,int sc, int speed2, int ID) :
     no_nc(nc), no_sc(sc), free_nc(nc), free_sc(sc), no_EP(0),id(ID+1)
{
    Car* c = nullptr;
    for (int i = 0; i < nc; i++)
    {
        c = new Car(speed1);
        c->setHospitalID(id-1);
        c->setCarType(0);
        np_cars.enqueue(c);
    }
    for (int i = 0; i < sc; i++)
    {
        c = new Car(speed2);
        c->setHospitalID(id-1);
        c->setCarType(1);
        sp_cars.enqueue(c);
    }
}

Hospital:: ~Hospital() 
{
    delete car;
    car = nullptr;
    delete patient;
    patient = nullptr;
    Patient* patient;
    while (nc_patients.dequeue(patient)) {
        delete patient;
    }
    int pri;
    while (ec_patients.dequeue(patient, pri)) {
        delete patient;
    }

    while (sc_patients.dequeue(patient)) {
        delete patient;
    }

    Car* car;
    while (np_cars.dequeue(car)) {
        delete car;
    }

    while (sp_cars.dequeue(car)) {
        delete car;
    }
}

//void Hospital::setTime(int time)
//{
//    TimeStep = time;
//}


void Hospital::addpatient(Patient* k)
{
    if (k->getPatientType() == 1)
    {
        nc_patients.enqueue(k);
        no_NP++;
    }
    else if (k->getPatientType() == 2)
    {
        sc_patients.enqueue(k);
        no_SP++;
    }
    else
    {
        ec_patients.enqueue(k, k->getSeverity());
        no_EP++;
    }
    patient = nullptr;
}

bool Hospital::remove_np_patient(Patient*& removed)
{
    if (nc_patients.isEmpty())
    {
        return false;
    }
    else
    {
        nc_patients.dequeue(removed);
        no_NP--;
        return true;
    }
}

bool Hospital::remove_sp_patient(Patient*& removed)
{
    if (sc_patients.isEmpty())
    {
        return false;
    }
    else
    {
        sc_patients.dequeue(removed);
        return true;
    }
}

bool Hospital::remove_ec_patient(Patient*& removed)
{
    if (ec_patients.isEmpty())
    {
        return false;
    }
    else
    {
        int sev;
        ec_patients.dequeue(removed,sev);
        return true;
    }
}
int  Hospital::getbusytime() {
    int count = 0;
    Car* cc;
    while (!np_cars.isEmpty())
    {
        np_cars.dequeue(cc);
        count += cc->getBusyTime();
    }
    while (!sp_cars.isEmpty())
    {
        sp_cars.dequeue(cc);
        count += cc->getBusyTime();
    }
    return count;
}
int  Hospital::gettotalwt() {
    Patient* pp;
    int pri;
    int count = 0;
    while (!nc_patients.isEmpty())
    {
        nc_patients.dequeue(pp);
        count += pp->getWT();
    }
    while (!ec_patients.isEmpty())
    {
        ec_patients.dequeue(pp, pri);
        ec_patients.dequeue(pp, pri);
        count += pp->getWT();
    }
    return count;

}
int Hospital::getid()
{
    return id;
}
Car* Hospital::assign_patient()
{
    Patient* k = nullptr;
    int s;
    Car* c = nullptr;
    if (!ec_patients.isEmpty())
    {
        if (!np_cars.isEmpty())
        {
            np_cars.dequeue(c);
            free_nc--;
            ec_patients.dequeue(k, s);
            no_EP--;
            c->assignPatient(k);
        }
        else if(!sp_cars.isEmpty())
        {
            sp_cars.dequeue(c);
            free_sc--;
            ec_patients.dequeue(k, s);
            no_EP--;
            c->assignPatient(k);
        }
    }
    else
    {
        if (!nc_patients.isEmpty() && !np_cars.isEmpty())
        {
            nc_patients.dequeue(k);
            free_nc--;
            np_cars.dequeue(c);
            no_NP--;
            c->assignPatient(k);
        }
        else if (!sc_patients.isEmpty() && !sp_cars.isEmpty())
        {
            sc_patients.dequeue(k);
            free_sc--;
            sp_cars.dequeue(c);
            no_SP--;
            c->assignPatient(k);
        }
    }
    return c;
}
void Hospital::checkupmovn()
{
    Car* a;

    while (checkup_list.peek(a))
    {
        if (a->getFinishServiseTime() <= TimeStep)
        {
            checkup_list.dequeue(a);
            if (a->getCarType() == 0)
            {
                np_cars.enqueue(a);
                free_nc++;
            }
            else if (a->getCarType() == 1)
            {
                sp_cars.enqueue(a);
                free_sc++;
            }
        }
        else
        {
            break;
        }
    }
}

void Hospital::addcar(Car* k)
{
    if (k->Gatfailure())
    {
        k->SetFinishServiseTime(TimeStep);
        checkup_list.enqueue(k);
    }
    else
    {
        if (k->getCarType() == 0)
        {
            np_cars.enqueue(k);
            free_nc++;
        }
        else
        {
            sp_cars.enqueue(k);
            free_sc++;
        }
    }

}

void Hospital::setfree_nc(int v)
{
    free_nc = v;
}

int Hospital::getfree_nc()
{
    return free_nc;
}



void Hospital::setfree_sc(int v)
{
    free_sc = v;
}

int Hospital::getfree_sc()
{
    return free_sc;
}

void Hospital::setno_nc(int n)
{
    no_nc = n;

}

int Hospital::getno_nc()
{
    return free_nc;
}

void Hospital::setno_sc(int n)
{
    no_sc = n;
}

int Hospital::getno_sc()
{
    return free_sc;
}
int Hospital::getno_scc()
{
    return no_sc;
}
int Hospital::GetEP()
{
    return no_EP;
}

int Hospital::GetNP()
{
    return no_NP;
}

int Hospital::GetSP()
{
    return no_SP;
}

CancelQueue Hospital::Getnc_patients()
{
    return nc_patients;
}
priQueue <Patient*> Hospital::Getec_patients()
{
    return ec_patients;
}
LinkedQueue <Patient*> Hospital::Getsc_patients()
{
    return sc_patients;
}

bool Hospital::cancelrequest(int id)
{
    return nc_patients.cancel(id);
}

void Hospital::detructcar()
{
     Car* car;
    while (np_cars.dequeue(car)) {
        delete car;
    }

    while (sp_cars.dequeue(car)) {
        delete car;
    }
}

void Hospital::setfail()
{
    fail = 1;
}

bool Hospital::getfail()
{
    if (fail == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Hospital::print()
{
    cout << "current Timestep: " << TimeStep;
    cout << endl;
    cout << "============    HOSPITAL #" << id << " data    ============\n";
    if (fail==1)
    {
        cout << "The Hospital is Failed" << endl;
    }
    else
    {
        cout << no_EP << " EP requests:";
        ec_patients.print();
        cout << endl;
        cout << no_SP << "SP requests:";
        sc_patients.print();
        cout << endl;
        cout << no_NP << "NP requests:";
        nc_patients.print();
        cout << endl;
        checkup_list.print();
        cout << endl;
        cout << "Free cars: " << free_sc << " SCars, " << free_nc << " NCars" << "\n";
    }
    cout << "============    HOSPITAL #" << id << " data  end  ============\n";
    cout << "--------------------------------------------------------------\n";
    cout << "press anykey to print next hospital\n";
}
