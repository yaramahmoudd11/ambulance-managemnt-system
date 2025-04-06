#include "PriCancelQueue.h"

Car* PriCancelQueue::cancel(int id) {

    bool ff = true;  // Assume success
    priNode<Car*>* deletePtr = nullptr;

    if (isEmpty()) {
        ff = false;
        return nullptr;  // If queue is empty, return false
    }

    priNode<Car*>* nodeToCancelPtr = head;
    priNode<Car*>* previous = nullptr;

    while (nodeToCancelPtr != nullptr) {
        // Check if the current node's item matches the item to cancel
        int pri;
        if (nodeToCancelPtr->getItem(pri)->getPatient()->getID() == id) {
            // If node to delete is at the front
            if (nodeToCancelPtr == head) {
                head = head->getNext();
                //if (frontPtr == nullptr) {  // If the queue is now empty
                //    backPtr = nullptr;
                //}
            }
            else {
                // If node to delete is in the middle or end
                previous->setNext(nodeToCancelPtr->getNext());
                if (nodeToCancelPtr->getNext() == nullptr) {
                    nodeToCancelPtr = previous;  // Update back pointer if necessary
                }
            }

            // Cleanup
            return nodeToCancelPtr->getItem(pri);
            //return ff;  // Successfully cancelled
        }

        // Move to the next node
        previous = nodeToCancelPtr;
        nodeToCancelPtr = nodeToCancelPtr->getNext();
    }
    int pri;
    // If no matching item was found
    ff = false;
    return nodeToCancelPtr->getItem(pri);
}