#define _MEH_USE_CPP17_FEATURES
#include "Utils\Factory.hpp"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch\catch.hpp"

#include <type_traits>

class BaseClass {
public:
	virtual ~BaseClass() = default;
	virtual std::string toString() const = 0;
};

class DerivedClass : public BaseClass {
public:
	std::string toString() const override {
		return std::string(typeid(DerivedClass).name());
	}
};


TEST_CASE("Create instance", "[core]")
{
	meh::utils::Factory<BaseClass> testFactory;

	REQUIRE(testFactory.empty());
	REQUIRE(testFactory.size() == 0);
	REQUIRE(testFactory.getCurrentFactorList().size() == 0);


	SECTION("Add derived class to factory") {
		testFactory.addFacturer<DerivedClass>();

		REQUIRE_FALSE(testFactory.empty());
		REQUIRE(testFactory.size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().front() == "DerivedClass");

	}

	SECTION("Add custom name derived class") {
		testFactory.addFacturer<DerivedClass>("CustomNameDerivedClass");

		REQUIRE_FALSE(testFactory.empty());
		REQUIRE(testFactory.size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().front() == "CustomNameDerivedClass");
	}

	SECTION("Factor instance of derived class") {
		testFactory.addFacturer<DerivedClass>();
		auto derivedClass = testFactory.factorClass("DerivedClass");

		REQUIRE(derivedClass.has_value());
		REQUIRE_NOTHROW(derivedClass.value());
		REQUIRE_FALSE(derivedClass.value() == nullptr);
		REQUIRE(derivedClass.value()->toString() == typeid(DerivedClass).name());
	}

	SECTION("Factor nonexisting class") {
		auto derivedClass = testFactory.factorClass("NotExistingClass");

		REQUIRE_FALSE(derivedClass.has_value());
		REQUIRE_THROWS_AS(derivedClass.value(), std::bad_optional_access);
	}

	SECTION("Erase element") {
		testFactory.addFacturer<DerivedClass>();

		REQUIRE_FALSE(testFactory.empty());
		REQUIRE(testFactory.size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().size() == 1);
		REQUIRE(testFactory.getCurrentFactorList().front() == "DerivedClass");

		testFactory.erase("DerivedClass");

		REQUIRE(testFactory.empty());
		REQUIRE(testFactory.size() == 0);
		REQUIRE(testFactory.getCurrentFactorList().size() == 0);

	}

}
