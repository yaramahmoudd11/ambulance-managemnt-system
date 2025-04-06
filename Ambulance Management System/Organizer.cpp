#include "Organizer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>


using namespace std;

Organizer::Organizer()
{
}
Organizer::~Organizer() {
	//if (MatHospitals != nullptr) {
	//	for (int i = 0; i < no_Hospitals; ++i) {
	//		delete[] MatHospitals[i];
	//	}
	//	delete[] MatHospitals;
	//}

	if (AllHospitals != nullptr) {
		delete[] AllHospitals;
	}

	Patient* patient;
	while (AllPatients.dequeue(patient)) {
		delete patient;
	}

	while (CancellationList.dequeue(patient)) {
		delete patient;
	}

	while (FinishedList.dequeue(patient)) {
		delete patient;
	}

	Car* car;
	int pri;
	while (BackCars.dequeue(car, pri)) {
		delete car;
	}

	while (OutCars.dequeue(car, pri)) {
		delete car;
	}
}
void Organizer::failbackcar() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomValue = rand() % 100;

	if (randomValue < backcarfail || randomValue == backcarfail)
	{
		if (BC - nooffailedcars == 0)
		{
			return;
		}
		std::srand(static_cast<unsigned int>(std::time(0)));
		int randomValue2 = rand() % (BC - nooffailedcars);
		Car* c;
		int pri;
		int count = 0;
		priQueue<Car*> BackCars2;
		while (BackCars.dequeue(c, pri))
		{
			if (!c->Gatfailure())
			{
				count++;
				if (count == randomValue2)
				{
					nooffailedcars++;
					failureactionBC(c);
				}
				else
				{
					BackCars2.enqueue(c, pri);
				}
			}
			else
			{
				BackCars2.enqueue(c, pri);
			}
		}
		while (BackCars2.dequeue(c, pri))
		{
			BackCars.enqueue(c, pri);
		}
	}

	
}
void Organizer::failoutcar() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomValue = rand() % 100 + 1;
	if (randomValue < backcarfail || randomValue == backcarfail)
	{
		if (OC == 0)
		{
			return;
		}
		std::srand(static_cast<unsigned int>(std::time(0)));
		int randomValue2 = rand() % OC + 1;
			Car* c;
			int pri;
			int count = 0;
			PriCancelQueue OutCars2;
			while (OutCars.dequeue(c, pri))
			{
				count++;
				if (count == randomValue2)
				{
					nooffailedcars++;
					failureactionOC(c);
					OC--;
				}
				else
				{
					OutCars2.enqueue(c, pri);
				}
			}
			while (OutCars2.dequeue(c, pri))
			{
				OutCars.enqueue(c, pri);
			}
	}
}
void Organizer::SetUp()
{
	// Taking number of hospitals

	ifstream InputFile("InputFile.txt");
	string line;
	getline(InputFile, line);
	no_Hospitals = stoi(line);


	// get speed of the cars

	getline(InputFile, line);
	istringstream stream1(line);
	stream1 >> Speed_SC >> Speed_NC;


	// hospital distance matrix

	MatHospitals = new int* [no_Hospitals];
	for (int i = 0; i < no_Hospitals; i++)
	{
		MatHospitals[i] = new int[no_Hospitals];
	}
	for (int i = 0; i < no_Hospitals; i++)
	{
		getline(InputFile, line);
		istringstream stream2(line);
		for (int j = 0; j < no_Hospitals; j++)
		{
			stream2 >> MatHospitals[i][j];
		}
	}


	// creating hospitals

	AllHospitals = new Hospital * [no_Hospitals];
	for (int i = 0; i < no_Hospitals; i++)
	{
		getline(InputFile, line);
		istringstream stream3(line);
		int SC, NC;
		stream3 >> SC >> NC;
		AllHospitals[i] = new Hospital(NC, Speed_NC, SC, Speed_SC,i);
	}


	// taking requests

	getline(InputFile, line);
	istringstream stream4(line);
	int Requests;
	stream4 >> Requests;
	for (int i = 0; i < Requests; i++)
	{
		Patient* P;
		getline(InputFile, line);
		istringstream stream5(line);
		string type;
		int QT, PID, HID, DST, SVR;
		stream5 >> type;
		if (type == "NP")
		{
			stream5 >> QT >> PID >> HID >> DST;
			P = new Patient(1, QT, PID, HID, DST, 0);
		}
		if (type == "SP")
		{
			stream5 >> QT >> PID >> HID >> DST;
			P = new Patient(2, QT, PID, HID, DST, 0);
		}
		if (type == "EP")
		{
			stream5 >> QT >> PID >> HID >> DST>>SVR;
			P = new Patient(3, QT, PID, HID, DST, SVR);+
			ep_count++;
		}
		AllPatients.enqueue(P);
	}


	// taking cancels

	getline(InputFile, line);
	istringstream stream6(line);
	int Cancels;
	stream6 >> Cancels;
	for (int i = 0; i < Cancels; i++)
	{
		Patient* P;
		getline(InputFile, line);
		istringstream stream7(line);
		int PID, HID, CT;
		stream7 >> PID >> HID >> CT;
		P = new Patient(PID, HID, CT);
		CancellationList.enqueue(P);
	}

	getline(InputFile, line);
	istringstream stream8(line);
	stream8 >> hospitalfail;

	getline(InputFile, line);
	istringstream stream9(line);
	stream9 >> backcarfail;

	getline(InputFile, line);
	istringstream stream10(line);
	stream10 >> outcarfail;

	getline(InputFile, line);
	istringstream stream11(line);
	stream11 >> CT;



}

void Organizer::failhosp()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomValue = rand() % 100;
	if (randomValue <= hospitalfail && randomValue != 0)
	{
		if (no_Hospitals - nooffailedhosp == 0)
		{
			return;
		}
		while (true)
		{
			std::srand(static_cast<unsigned int>(std::time(0)));
			int randomValue2 = rand() % (no_Hospitals);
			if (AllHospitals[randomValue2]->getfail() == 0)
			{
				hospitalfail++;
				failureaction(randomValue2);
				break;
			}
		}



	}

}
int Organizer::countNP()
{
	int countNP = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		countNP += AllHospitals[i]->GetNP();
	}
	return countNP;
}
int Organizer::countSP()
{
	int countNP = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		countNP += AllHospitals[i]->GetSP();
	}
	return countNP;

}
int Organizer::countEP()
{
	int countNP = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		countNP += AllHospitals[i]->GetEP();
	}
	return countNP;

}
int Organizer::countSC()
{
	int count = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		count += AllHospitals[i]->getno_scc();
	}
	return count;

}
int Organizer::countNC()
{
	int count = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		count += AllHospitals[i]->getno_nc();
	}
	return count;

}
int Organizer:: avgbusytime()
{
	int count = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		count += AllHospitals[i]->getbusytime();
	}
	return ((count / counttotalc()) * 100);
}
int Organizer::avgutilization()
{
	return ((avgbusytime() / (TimeStep* counttotalc())) * 100);
}
/* wt*/
int Organizer::avgwaittime()
{
	int count = 0;
	for (int i = 0; i < no_Hospitals;i++)
	{
		count += AllHospitals[i]->gettotalwt();
	}
	return (count / TimeStep);
}

void Organizer::outputfile()
{
	int totalwt=0;
	int EPCount = 0;
	int NPCount = 0;
	int SPCount = 0;
	int pat_count = 0;
	ofstream outFile("output.txt");
	if (outFile) {
		
		outFile <<"FT         PID         QT        WT" << endl;
		Patient* pp;
		while (FinishedList.dequeue(pp))
		{
			outFile << pp->getFinishTime() << "         " << pp->getID() << "         " << pp->getRequestTime() << "         " << pp->getWaitingTime() << endl;
			totalwt += pp->getWaitingTime();
			pat_count++;
			if (pp->getPatientType() == 1) { NPCount++; }
			if (pp->getPatientType() == 2) { SPCount++; }
			if (pp->getPatientType() == 3) { EPCount++; }
		}
		outFile <<"..........................................................." << endl;
		outFile << "patients:" << NPCount + SPCount + EPCount << "    [NP:" << NPCount << ", SP :" << SPCount << " , EP :" << EPCount << "]" << endl;
		outFile << "Hospitals = "<< no_Hospitals << endl;
		outFile << "cars:" << counttotalc() << "        [SCar:" << countSC() << ", NCar:" << countNC() << " ]" << endl;
		outFile << "Avg wait time = "<<(totalwt/ pat_count) << endl;
		outFile << "Percentage of EP =" << ((EPCount * 100 / (NPCount + SPCount + EPCount))) << "%" << endl;
		int avgbusyt = avgbusytime() / counttotalc();
		outFile << "Avg busy time = "<< avgbusyt << endl;
		outFile << "Avg utilization = " << (avgbusyt / (TimeStep)) <<"%"<< endl;
		outFile << "no of failed cars = " << nooffailedcars << "   " << (nooffailedcars*100 / counttotalc())<<" %" << endl;
		outFile << "Number of failed hospitals= " << nooffailedhosp << "   " <<(nooffailedhosp*100/ no_Hospitals)<<" %" << endl;
		outFile << "Number of cars went out of eservice due to hospital failure=" << carseservice << endl;
	}

	outFile.close();

}
int Organizer::counttotalp()
{
	int count = 0;
	return count += countEP() + countNP() + countSP();
}
int Organizer::counttotalc()
{
	return countNC() + countSC() ;
}


int Organizer::get_nearest_hospital(int f)
{
	/*int k;
	int n;
	for (int i = 0; i < no_Hospitals; i++)
	{
		if (AllHospitals[i] == f)
		{
			k = MatHospitals[0][i];
			n = i;
		}
	}*/

	int m = 0;
	int least = MatHospitals[f][0];
	for (int i = 0; i < no_Hospitals; i++)
	{
		//int k = MatHospitals[f][f];
		//least = MatHospitals[f][f];
		if (MatHospitals[f][i] < least && i != f)
		{
			least = MatHospitals[f][i];
			m = i;
		}
	}
	return m;
}

void Organizer::failureactionBC(Car* BC) 
{
	BC->SetServiseTime(CT);
	BC->BackCarFail();
	LinkedQueue<Patient*> tempAllPatients;
	Patient* P;
	while (!AllPatients.isEmpty())
	{
		AllPatients.dequeue(P);
		tempAllPatients.enqueue(P);
	}
	AllPatients.enqueue(BC->getPatient());
	BC->setPatient(nullptr);
	while (!tempAllPatients.isEmpty())
	{
		tempAllPatients.dequeue(P);
		AllPatients.enqueue(P);
	}
	BackCars.enqueue(BC, -BC->getFinishTime());

}

void Organizer::failureactionOC(Car* OC) 
{
	OC->SetServiseTime(CT+TimeStep);
	outcarfail++;
	OC->fail();
	BackCars.enqueue(OC, -OC->getFinishTime());
	BC++;
	LinkedQueue<Patient*> tempAllPatients;
	Patient* P;
	while (!AllPatients.isEmpty())
	{
		AllPatients.dequeue(P);
		tempAllPatients.enqueue(P);
	}
	AllPatients.enqueue(OC->getPatient());
	OC->setPatient(nullptr);
	while (!tempAllPatients.isEmpty())
	{
		tempAllPatients.dequeue(P);
		AllPatients.enqueue(P);
	}
}

void Organizer::failureaction(int k)
{
	nooffailedhosp++;
	Patient* removed = nullptr;
	int l= get_nearest_hospital(k);

	for (int i = 0; i < AllHospitals[k]->GetEP(); i++)
	{
		AllHospitals[k]->remove_ec_patient(removed);
		AllHospitals[l]->addpatient(removed);
	}
	for (int i = 0; i < AllHospitals[k]->GetNP(); i++)
	{
		AllHospitals[k]->remove_np_patient(removed);
		AllHospitals[l]->addpatient(removed);
	}
	for (int i = 0; i < AllHospitals[k]->GetSP(); i++)
	{
		AllHospitals[k]->remove_sp_patient(removed);
		AllHospitals[l]->addpatient(removed);
	}

	priQueue <Car*> ccc;
	for (int i = 0; i < OC; i++)
	{
		Car* n = nullptr;
		int mm;
		
		OutCars.dequeue(n, mm);
		if (n->getHospitalID() == AllHospitals[k]->getid())
		{
			failureactionOC(n);
			carseservice++;
			/* LinkedQueue<Patient*> tempAllPatients;
			 Patient* P;
			while (!AllPatients.isEmpty())
			{
				AllPatients.dequeue(P);
				tempAllPatients.enqueue(P);
			}
			AllPatients.enqueue(n->getPatient());
			while (!tempAllPatients.isEmpty())
			{
				tempAllPatients.dequeue(P);
				AllPatients.enqueue(P);
			}*/
		}
		else
		{
			ccc.enqueue(n, mm);
		}
	}

	while (!ccc.isEmpty())
	{
		int car_out;
		Car* y = nullptr;
		ccc.dequeue(y, car_out);
		OutCars.enqueue(y, car_out);
	}

	priQueue <Car*> backcarss;
	for (int i = 0; i < BC; i++)
	{
		Car* n = nullptr;
		int mm;

		BackCars.dequeue(n, mm);
		if (n->getHospitalID() ==AllHospitals[k]->getid())
		{
			
			failureactionBC(n);
			carseservice++;
		}
		else
		{
			backcarss.enqueue(n, mm);
		}
	}
	while (!backcarss.isEmpty())
	{
		int car_back;
		Car* backcarsss = nullptr;
		ccc.dequeue(backcarsss, car_back);
		BackCars.enqueue(backcarsss, car_back);
	}

	AllHospitals[k]->detructcar();

}


void Organizer::SendPatients()
{
	while (true)
	{
		Patient* P=nullptr;
		AllPatients.peek(P);
		if (P == nullptr)
		{
			break;
		}
		if (P->getRequestTime() > TimeStep)
		{
			break;
		}
		else
		{
			AllPatients.dequeue(P);
			int HID = P->getNearestHospital();
			while (AllHospitals[HID - 1]->getfail())
			{
				HID = get_nearest_hospital(HID - 1);
			}
				if (P->getPatientType() != 3)
				{
					AllHospitals[HID - 1]->addpatient(P);
				}
				else
				{
					if (AllHospitals[HID - 1]->getfree_sc() > 0 || AllHospitals[HID - 1]->getfree_nc() > 0)
					{
						AllHospitals[HID - 1]->addpatient(P);
					}
					else
					{
						countoutep++;
						int least_EP = AllHospitals[HID - 1]->GetEP();
						for (int i = 0; i < no_Hospitals; i++)
						{
							if (AllHospitals[i]->GetEP() < least_EP)
							{
								least_EP = AllHospitals[i]->GetEP();
							}
						}
						int least_dis = MatHospitals[HID - 1][0];
						for (int i = 0; i < no_Hospitals; i++)
						{
							if (AllHospitals[i]->GetEP() ==least_EP&& MatHospitals[HID - 1][i]<least_dis)
							{
								HID = i + 1;
							}
						}
						AllHospitals[HID - 1]->addpatient(P);
					}
				}
			
		}
	}
}

void Organizer::AssignPatients()
{
	for (int i = 0; i < no_Hospitals; i++)
	{
		while (true)
		{
			Car* C = AllHospitals[i]->assign_patient();
			if (C == nullptr)
			{
				break;
			}
			else
			{
				OutCars.enqueue(C, -C->getPickTime());
				OC++;
				
			}
		}
	}
}

void Organizer::CheckCancel()
{
	Patient* P;
	while (CancellationList.peek(P))
	{
		if (P->getCancelTime() > TimeStep) { break; }
		else
		{
			CancellationList.dequeue(P);
			int hid = P->getNearestHospital();
			int id = P->getID();
			if (!AllHospitals[hid-1]->cancelrequest(id))
			{
				OC--;
				Car* C = OutCars.cancel(id);
				if (C)
				{
					C->cancelFT();
					C->setPatient(nullptr);
					BC++;
					BackCars.enqueue(C,C->getFinishTime());
				}
			}
		}
	}
}

void Organizer::SetBackCars()
{
	while (true)
	{
		Car* C = nullptr;
		int PT;
		OutCars.peek(C, PT);
		if (C)
		{
			if (-PT > TimeStep)
			{
				break;
			}
			else
			{
				OutCars.dequeue(C, PT);
				OC--;
				PT = -PT;
				BackCars.enqueue(C, -C->getFinishTime());
				BC++;
			}
		}
		else
		{
			break;
		}
	}
}

void Organizer::FinishPatients()
{
	while (true)
	{
		Car* C;
		int FT;
		if (BackCars.peek(C, FT))
		{
			if (-FT > TimeStep)
			{
				break;
			}
			else
			{
				BackCars.dequeue(C, FT);
				BC--;
				FT = -FT;
				Patient* P = C->getPatient();
				int HID = C->getHospitalID();
				if (P)
				{
					FinishedList.enqueue(P);
					FL++;
				}
				int BusyTime = C->getFinishTime() - C->getAssignTime();
				C->setBusyTime(BusyTime);
				if (!AllHospitals[HID]->getfail())
				{
					AllHospitals[HID]->addcar(C);
				}
			}
		}
		else
		{
			break;
		}

	}
}

bool Organizer::CheckEnd()
{
	if (FinishedList.isEmpty())
	{
		return false;
	}
	else
	{
		if (!AllPatients.isEmpty())
		{
			return false;
		}
		else
		{
			if (!OutCars.isEmpty())
			{
				return false;
			}
			else
			{
				if (!BackCars.isEmpty())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

}

void Organizer::Simulate()
{
	SetUp();
	bool mode = UserInter.choice();
	while (!CheckEnd())
	{
		TimeStep++;
		failbackcar();
		failhosp();
		failoutcar();


		SendPatients();

		//cout << "SendPatients" << endl;

		CheckCancel();

		AssignPatients();

		//cout << "AssignPatients" << endl;

		SetBackCars();

		//cout << "SetBackCars" << endl;

		FinishPatients();

		for (int i = 0; i < no_Hospitals; i++)
		{
			if (!AllHospitals[i]->getfail())
			{
				AllHospitals[i]->checkupmovn();
			}
		}

		if (mode)
		{
			string s;
			for (int i = 0; i < no_Hospitals; i++)
			{
				//getline(cin, s); //just to pause console (output) screen
				UserInter.interactivemode(AllHospitals[i]);
			}
			//getline(cin, s); //just to pause console (output) screen
			UserInter.printbackoutfinish(BackCars, BC, OutCars, OC, FinishedList, FL);
			//getline(cin, s); //just to pause console (output) screen
		}
	}
	string s;
	getline(cin, s); //just to pause console (output) screen
	outputfile();
}