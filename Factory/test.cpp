// DepInj_test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Factory.hpp"

class BaseClass {
public:
	virtual const std::string toString() const = 0;
};


class DerivedClass : public BaseClass {
public:
	const std::string toString() const override {
		return std::string(typeid(DerivedClass).name());
	}
};

class Derived2Class : public BaseClass {
public:
	const std::string toString() const {
		return std::string(typeid(Derived2Class).name());
	}
};

int main()
{
	meh::utils::Factory<BaseClass> newFactory;

	newFactory.addFacturer<Derived2Class>("DerivedClass");
	newFactory.addFacturer<DerivedClass>();
	
	auto DelClass = newFactory.factorClass("DerivedClass");
	
	std::cout << DelClass.value()->toString() << std::endl;
	
	std::cin.ignore();

    return 0;
}

