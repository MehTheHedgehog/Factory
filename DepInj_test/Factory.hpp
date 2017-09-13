#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <memory>
#include <string>
#include <map>
#include <functional>

class stringable {
public:
	const static char* className;
};

template<class BaseClass>
class Factory {
	static_assert(std::is_base_of<stringable, BaseClass>::value, "Your Base Class need to be stringable (implement toString function)");

	private:
		std::map<std::string, std::function<std::unique_ptr<BaseClass>()>> functionMap;
	public:
		template <class Templater>
		void addFactorer() {
			static_assert(std::is_base_of<BaseClass, Templater>::value, "Given Class is not child of the factor BaseClass");

			auto funcMake = std::make_pair(Templater::className, []() {
				return std::make_unique<Templater>(Templater());
			});
			functionMap.insert(funcMake);
		}

		std::unique_ptr<BaseClass> factorClass(std::string className) {
			try {
				return functionMap[className]();
			}catch (...) {
				return nullptr;
			}
		}



};

#endif // !FACTORY_HPP


#pragma once
