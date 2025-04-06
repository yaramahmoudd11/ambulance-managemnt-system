#pragma once
#include "priQueue.h"
#include "car.h"
#include "Patient.h"

class PriCancelQueue: public priQueue<Car*>
{
public:
	Car* cancel(int id);
};

