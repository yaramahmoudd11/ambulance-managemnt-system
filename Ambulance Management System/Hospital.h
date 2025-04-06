#pragma once
#include "LinkedQueue.h"
#include "Patient.h"
#include "Car.h"
#include "priQueue.h"
#include "CancelQueue.h"
#include "Time.h"
#include "PriCancelQueue.h"

class Hospital
{
private:
	//int TimeStep = 0;
	Patient* patient;
	Car* car;
	CancelQueue nc_patients;
	priQueue <Patient*> ec_patients;
	LinkedQueue <Patient*> sc_patients;
	LinkedQueue <Car*> np_cars;
	LinkedQueue <Car*> sp_cars;
	LinkedQueue <Car*> checkup_list;
	int no_EP = 0;
	int no_SP = 0;
	int no_NP = 0;
	int no_nc;
	int no_sc;
	int free_nc = 0;
	int free_sc = 0;
	int id;
	int fail = 0;
public:

	Hospital();
	Hospital(int nc, int speed1, int sc, int speed2,int ID);
	~Hospital();


	//void setTime(int time);
	void addpatient(Patient* k);
	bool remove_np_patient(Patient*& removed);
	bool remove_sp_patient(Patient*& removed);
	bool remove_ec_patient(Patient*& removed);
	Car* assign_patient();
	void addcar(Car* k);
	void setfree_nc(int v);
	int getfree_nc();
	void setfree_sc(int v);
	int getfree_sc();
	void setno_nc(int n);
	int getno_nc();
	void setno_sc(int n);
	void checkupmovn();
	int getno_sc();
	int getno_scc();
	int GetEP();
	int GetSP();
	int GetNP();
	int getbusytime();
	int gettotalwt();
	int getid();
	CancelQueue Getnc_patients();
	priQueue <Patient*> Getec_patients();
	LinkedQueue <Patient*> Getsc_patients();
	bool cancelrequest(int id);
	void detructcar();
	void setfail();
	bool getfail();
	void print();
};
