#pragma once
#include <iostream>
#include <string>
//#include "Organizer.h"
#include "LinkedQueue.h"
#include "Patient.h"
#include "Hospital.h"
#include "Car.h"
#include "priQueue.h"
#include "CancelQueue.h"
#include "Time.h"
#include "PriCancelQueue.h"
#include "UI.h"
#include <conio.h> 

using namespace std;
class UI
{
    int count;
    int mode = 0;
    int simulation = 0;
    Hospital* Hp;

public:
    //~UI();
    void interactivemode(Hospital* p);
    bool choice();
    void silent();
    void printbackoutfinish(priQueue<Car*>& BackCars, int bck,
        PriCancelQueue& OutCars, int out,
        LinkedQueue<Patient*>& FinishedList, int fin);


};

