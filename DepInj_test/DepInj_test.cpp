// DepInj_test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Factory.hpp"

class BaseClass : public stringable {
public:
	virtual const std::string toString() const = 0;
};


class DeliverClass : public BaseClass {
public:
	const std::string toString() const {
		return std::string("DeliverClass");
	}
};

const char* DeliverClass::className = "DeliverClass";

class AnotherClass {
public:
	const std::string toString() const {
		return std::string("AnotherClass");
	}
};

int main()
{
	Factory<BaseClass> newFactory;

	newFactory.addFactorer<DeliverClass>();
	
	//Static assert will give an error
	//newFactory.addFactorer<AnotherClass>();

	auto DelClass = newFactory.factorClass("DeliverClass");
	
	//You will get nullptr from this factor
	//auto BadClass = newFactory.factorClass("AnotherClass");

	if (DelClass != nullptr) {
		std::cout << DelClass->toString() << std::endl;
	}
	else {
		std::cout << "Cannot factor given class" << std::endl;
	}
	
	std::cin.ignore();

    return 0;
}

