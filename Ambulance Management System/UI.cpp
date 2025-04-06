#include "UI.h"
using namespace std;

/*
void UI::interactivemode()
{
	while (count !=org->getno_Hospitals())
	{
		if (simulation == 0)
		{
			cout << "current Timestep: " << TimeStep;
			cout << endl;
			cout << "============    HOSPITAL #" <<getid(count)<< " data    ============\n";
			cout << "EP requests:" << "\n";
			cout << "SP requests:" << "\n";
			cout << "NP requests:" << "\n";
			cout << "Free cars:" <<org->getspeccars(x,y)<<"SCars" << org->getnormalcars(x, y) << "NCars" << "\n";
			cout << "============    HOSPITAL #" << " data  end  ============\n";
			cout << "--------------------------------------------------------------\n";


			cout << "--------------------------------------------------------------\n";


		}
		else if (simulation == 12)
		{
			cout << "Simulation ends,output file created...";

		}
	}
}*/
void UI::interactivemode(Hospital* p)
{
	p->print();
}
void UI::printbackoutfinish(priQueue<Car*>& BackCars, int bck, PriCancelQueue& OutCars, int out, LinkedQueue<Patient*>& FinishedList, int fin)
{
	priQueue<Car*> BackCars2;
	PriCancelQueue OutCars2;
	LinkedQueue<Patient*> FinishedList2;
	Car* c;
	Patient* pat;
	int pri = 0;
	int pri2 = 0;

	cout << "--------------------------------------------------------------\n";
	cout << out << " ==> out cars: ";
	//while (!OutCars.isEmpty())
	//{
	//	OutCars.dequeue(c, pri2);
	//	int type = c->getCarType();
	//	if (type == 1) { cout << "N"; }
	//	if (type == 2) { cout << "S"; }
	//	cout << c->getcarid()<<"_H" << c->getHospitalID()+1 << "_P" << c->getPatient()->getID()<<", ";
	//	OutCars2.enqueue(c, pri2);
	//}
	//while (!OutCars2.isEmpty())
	//{
	//	OutCars2.dequeue(c, pri2);
	//	OutCars.enqueue(c, pri2);
	//}
	OutCars.print();
	cout << endl;
	cout << bck << " <== Back cars: ";
	//while (!BackCars.isEmpty())
	//{
	//	BackCars.dequeue(c, pri);
	//	int type = c->getCarType();
	//	if (type == 1) { cout << "N"; }
	//	if (type == 2) { cout << "S"; }
	//	cout << c->getcarid()<<"_H" << c->getHospitalID()+1 << "_P" << c->getPatient()->getID()<<", ";
	//	BackCars2.enqueue(c, pri);
	//}
	//while (!BackCars2.isEmpty())
	//{
	//	BackCars2.dequeue(c, pri);
	//	BackCars.enqueue(c, pri);
	//}
	BackCars.print();
	cout << endl;
	cout << "--------------------------------------------------------------\n";
	cout << fin << " finished patients:";
	//while (!FinishedList.isEmpty())
	//{
	//	FinishedList.dequeue(pat);
	//	cout << pat->getID() << " ,";
	//	FinishedList2.enqueue(pat);
	//}
	//while (!FinishedList2.isEmpty())
	//{
	//	FinishedList2.dequeue(pat);
	//	FinishedList.enqueue(pat);
	//}
	FinishedList.print();
}

bool UI::choice()
{
	cout << "Select a mode , press 1 for interactive mode and 2 for silent mode: ";
	cin >> mode;
	if (mode == 1)
	{
		return true;
	}
	else if (mode == 2)
	{
		return false;

	}
	else {
		cout << "please enter a valid mode";
		choice();
	}
}
void UI::silent()
{
	if (simulation == 0)
	{
		cout << "Silent mode, Simulation starts...";
		cout << endl;
	}
	else if (simulation == 12)
	{
		cout << "Simulation ends,output file created...";

	}

}
//int UI::getid(int c)
//{
//	if (c %2 == 0) {
//		org->gethosid((c / 2) - 1, (c / 2) - 1);
//	}
//
//}
