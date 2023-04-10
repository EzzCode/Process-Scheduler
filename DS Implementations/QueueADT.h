#ifndef QUEUE_ADT_
#define QUEUE_ADT_
#pragma once
#include "../Program Classes/Process.h"
class QueueADT
{
public:
	// Sees whether this queue is empty
	virtual bool isEmpty() const = 0;

	// Adds a new entry to the back of this queue & return whether it was added successfully or not
	virtual bool enqueue(Process* newEntry) = 0;

	// Removes the front item and returns it through the FrontEntry Parameter
	// Returns whether the item it was removed successfully or not
	virtual bool dequeue(Process*& frntEntry) = 0;

	// Returns the front item through the parameter without removing it
	// Returns whether the item was copied or not
	virtual bool peek(Process*& frntEntry) const = 0;
};
#endif