#pragma once
#include "LinkedQueue.h"
#include "Patient.h"
#include "Hospital.h"
#include "Car.h"
#include "priQueue.h"
#include "CancelQueue.h"
#include "Time.h"
#include "PriCancelQueue.h"
#include "UI.h"



class Organizer
{
private:
	//int TimeStep = 0;
	int** MatHospitals;
	Hospital** AllHospitals;
	int no_Hospitals;
	LinkedQueue<Patient*> AllPatients;
	LinkedQueue<Patient*> CancellationList;
	int Speed_NC;
	int Speed_SC;
	priQueue<Car*> BackCars;
	int BC = 0;
	PriCancelQueue OutCars;
	int OC = 0;
	LinkedQueue<Patient*> FinishedList;
	int FL = 0;
	UI UserInter;
	int countoutep = 0;
	int nooffailedcars=0;
	int nooffailedhosp=0;
	int carseservice=0;
	int hospitalfail;
	int backcarfail;
	int outcarfail;
	int CT;
	int ep_count=0;
public:
	Organizer();
	void SetUp();
	void failhosp();
	void failbackcar();
	void failoutcar();
	void SendPatients();
	void AssignPatients();
	//void GetOutCars();
	void CheckCancel();
	void SetBackCars();
	void FinishPatients();
	bool CheckEnd();
	void Simulate();
	int countNP();
	int countSP();
	int countEP();
	int countSC();
	int countNC();
	int counttotalp();
	int counttotalc();
	void outputfile();
	int avgwaittime();
	int avgbusytime();
	int avgutilization();

	int get_nearest_hospital(int f);
	void failureaction(int k);
	void failureactionBC(Car* BC);
	void failureactionOC(Car* OC);

	~Organizer();
};

