#pragma once
#include "LinkedQueue.h"
#include "Patient.h"

class CancelQueue : public LinkedQueue<Patient*>
{
public:
	bool cancel(int id);
};