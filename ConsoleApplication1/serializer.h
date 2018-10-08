//// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
#include "pch.h"
#include <iostream>

namespace serializer {}

namespace serializer::xml {

	inline static constexpr char tag_open{ '<' }, tag_close{ '>' };
	inline static constexpr char tag_open_last[3]{ "</" };

	template<typename T>
	struct _implementation {

		static void process(const T &element, std::ostream &stream) {
			stream << tag_open << T::name << tag_close;

			using type = typename T::element_list_t;
			type elements = element.elements;
			for_each(elements, [&stream](auto &child) {
				using child_type = typename std::remove_cv<std::remove_reference<decltype(child)>::type>::type;
				_implementation<child_type>::process_simple(child, stream);
			});

			stream << tag_open_last << T::name << tag_close;
		}

		static void process_simple(const T &element, std::ostream &stream) {
			stream << tag_open << T::name << tag_close;
			stream << element.value;
			stream << tag_open_last << T::name << tag_close;
		}

	};

	template<typename T>
	void process(const T &root, std::ostream &stream = std::cout) {
		_implementation<T>::process(root, stream);
	}

}

namespace serializer::json {

	inline static constexpr char quote = '"';
	inline static constexpr char quote_colon[3]{ "\":" };
	inline static constexpr char comma = ',';
	inline static constexpr char open_array = '[';
	inline static constexpr char end_array = ']';
	inline static constexpr char open_object = '{';
	inline static constexpr char end_object = '}';

	template<typename T>
	struct _implementation {

		static void process(const T &element, std::ostream &stream) {
			stream << quote << T::name << quote_colon;
			stream << open_object;

			using type = typename T::element_list_t;
			type elements = element.elements;
			for_each(elements, [&stream](auto &child) {
				using child_type = typename std::remove_cv<std::remove_reference<decltype(child)>::type>::type;
				_implementation<child_type>::process_simple(child, stream);
				stream << comma;
			});

			stream<< "\b";
			stream << end_object;
		}

		static void process_simple(const T &element, std::ostream &stream) {
			stream << quote << T::name << quote_colon;
			stream << quote << element.value << quote;
		}

	};

	template<typename T>
	void process(const T &root, std::ostream &stream = std::cout) {
		_implementation<T>::process(root, stream);
	}

}
