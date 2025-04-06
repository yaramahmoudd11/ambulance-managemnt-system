#include "CancelQueue.h"

bool CancelQueue::cancel(int id)
{

    bool ff = true;
    Node<Patient*>* deleteptr = nullptr;

    if (frontPtr==nullptr) {
        ff = false;
        return ff;
    }

    Node<Patient*>* nodeToCancelPtr = frontPtr;
    Node<Patient*>* previous = nullptr;

    while (nodeToCancelPtr != nullptr) {
        if (nodeToCancelPtr->getItem()->getID() == id) {
            if (nodeToCancelPtr == frontPtr) {
                frontPtr = frontPtr->getNext();
                if (frontPtr == nullptr) {
                    backPtr = nullptr;
                }
            }
            else {
                previous->setNext(nodeToCancelPtr->getNext());
                if (nodeToCancelPtr == backPtr) {
                    backPtr = previous;
                }
            }

            //k = nodeToCancelPtr->getItem();
            delete nodeToCancelPtr;
            deleteptr = nullptr;
            return ff;
        }

        previous = nodeToCancelPtr;
        nodeToCancelPtr = nodeToCancelPtr->getNext();
    }
    ff = false;
    return ff;
}
