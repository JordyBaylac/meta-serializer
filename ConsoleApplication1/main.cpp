// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "serializer.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace boost::fusion;

namespace schemas {
	namespace ndc {
		namespace ordercreate {
		}
	}
}

namespace schemas::ndc::ordercreate {

	struct version {
		constexpr static char name[] = "Version";

		std::string value;
	};
	struct lang {
		constexpr static char name[] = "Language";

		std::string value;
	};
	struct payload {
		constexpr static char name[] = "Payload";
		using element_list_t = set<lang, version>;
		using attribute_list_t = set<lang>;

		element_list_t elements;
		attribute_list_t attributes;
	};
}

template<typename Element, typename Parent>
Element get(const Parent& parent) {
	return 
		//has_key<Element>(parent.elements)
		//? 
		at_key<Element>(parent.elements)
		//: at_key<Element>(parent.attributes)
		;
}

template<typename Element, typename Parent>
void mutate(const Parent& parent, const Element& element) {
	//at_key<Element>(parent.elements,
}

int main()
{
	using namespace schemas::ndc::ordercreate;

	std::ostringstream stream;
	//payload p{ version{"19.1"}, lang{ "espanglish"} };
	payload p { payload::element_list_t( lang{"espanitish"}, version{"18_1"} ) };
    /*std::cout<< p.m_lang.language << std::endl;
	std::cout<< p.m_version.value << std::endl;*/

	serializer::xml::process(p, stream);
	stream << "--------------------------------" << std::endl;
	//serializer::xml::process(at_key<lang>(p.elements), std::cout);
	serializer::json::process(p, stream);
	stream << "--------------------------------" << std::endl;

	auto language = get<lang>(p);
	stream << "language: " << language.value << std::endl;

	mutate<version>(p, {"19.5"});

	auto v = get<version>(p);
	stream << "version: " << v.value << std::endl;

	stream << "--------------------------------" << std::endl;
	std::string s = stream.str();
	std::cout << s;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
