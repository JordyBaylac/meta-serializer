// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <boost/fusion/container/set.hpp>
#include <boost/fusion/include/set.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/include/set_fwd.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>

template <class T>
constexpr std::string_view type_name()
{
	using namespace std;
#ifdef __clang__
	string_view p = __PRETTY_FUNCTION__;
	return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
	string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
	return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
	return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
	string_view p = __FUNCSIG__;
	return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

#endif //PCH_H
