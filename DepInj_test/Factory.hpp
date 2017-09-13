#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <memory>
#include <string>
#include <map>
#include <functional>

template<class BaseClass>
class Factory {
	private:
		std::map<std::string, std::function<std::unique_ptr<BaseClass>()>> functionMap;
	public:
		template <class Templater>
		void addFactorer(std::string className) {
			static_assert(std::is_base_of<BaseClass, Templater>::value, "Given Class is not child of the factor BaseClass");

			auto funcMake = std::make_pair(className, []() {
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
