#ifndef FACTORY_HPP
#define FACTORY_HPP

#if _HAS_CXX17
	#include <optional>
#endif /* _HAS_CXX17 */

#include <memory>
#include <string>
#include <map>
#include <functional>

namespace meh {
namespace utils {

	template<class BaseClass>
	class Factory {
	private:
		std::map<std::string, std::function<std::unique_ptr<BaseClass>()>> functionMap;

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

			functionMap.insert(std::make_pair(className, factorFunc));
		}

		//Return class instance of corresponding name
		#if _HAS_CXX17
			std::optional<std::unique_ptr<BaseClass>>
		#else
			std::unique_ptr<BaseClass>
		#endif /* _HAS_CXX17 */
		factorClass(const std::string& className) {
			try {
				return functionMap.at(className)();
			}
			catch (const std::out_of_range& exc) {
				if (_HAS_CXX17) 
					throw exc;
				else
					return nullptr;
			}
		}

		//Make class instance without need to register class
		template<typename Derived>
		#if _HAS_CXX17
			std::optional<std::unique_ptr<BaseClass>> factorClass() {
		#else
			std::unique_ptr<BaseClass> factorClass() {
		#endif /* _HAS_CXX17 */
			static_assert(std::is_base_of<BaseClass, Derived>::value, "Derived is not child of the factor BaseClass");
			return std::make_unique<Derived>();
		}

	};

}
}



#endif // !FACTORY_HPP


#pragma once
