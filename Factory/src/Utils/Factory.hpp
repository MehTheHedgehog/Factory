#pragma once

#include <optional>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>

namespace meh {
namespace utils {

	template<typename BaseClass>
	class Factory {
	private:
		std::map<std::string, std::function<std::unique_ptr<BaseClass>()>> factorMap;

		//Function to extract class name from typeid().name()
		//Visual Studio make name of typeid as "class classname" 
		//We need to extract only classname from it
		template<class Derived>
		const static std::string makeName() {
			return std::string(std::string(typeid(Derived).name()), std::string(typeid(Derived).name()).find("class ") + std::strlen("class "));
		}
 
	public:

		//Add class to map of builders
		template <class Derived>
		void addFacturer(const std::string& className = makeName<Derived>(), std::function<std::unique_ptr<BaseClass>()> factorFunc = []() {
			static_assert(std::is_base_of<BaseClass, Derived>::value, "Derived is not child of the factor BaseClass");
			return std::make_unique<Derived>();
		}) {
			static_assert(std::is_base_of<BaseClass, Derived>::value, "Derived is not child of the factor BaseClass");

			factorMap.insert(std::make_pair(className, factorFunc));
		}

		//Return class instance of corresponding name
		std::optional<std::unique_ptr<BaseClass>> factorClass(const std::string& className) {
			try {
				return factorMap.at(className)();
			}
			catch (const std::out_of_range&) {
					return std::optional<std::unique_ptr<BaseClass>>();
			}
		}

		//Make class instance without need to register class
		template<typename Derived> 
		std::optional<std::unique_ptr<BaseClass>> factorClass() {
			static_assert(std::is_base_of<BaseClass, Derived>::value, "Derived is not child of the factor BaseClass");
			return std::make_unique<Derived>();
		}

		//Access to Factory elements

		std::vector<std::string> getCurrentFactorList() const {
			std::vector<std::string> vectorKey;

			for (const auto& funcPair : factorMap)
				vectorKey.push_back(funcPair.first);

			return vectorKey;
		}

		void erase(const std::string& className) {
			factorMap.erase(factorMap.find(className));
		}

		std::size_t size() const {
			return factorMap.size();
		}

		bool empty() const {
			return size() == 0;
		}

	};

}
}