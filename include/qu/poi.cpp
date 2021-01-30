#include <cstddef>
#include <variant>
#include <memory>
#include <string_view>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <deque>
#include <set>
#include <forward_list>
#include <algorithm>
#include <fstream>
#include <queue>
#include <cmath>
#include <filesystem>

namespace poi
{

struct entity
{
	virtual ~entity() = default;
	
	const char *locus;
};

struct named_entity : entity
{
	const char *name;
};

struct namespace_ : named_entity
{

};

struct alias : named_entity
{
	const char *aliased;
};

enum struct fixity_kind
{
	prefix,
	postfix,
	infix
};

struct udo : named_entity
{ };

struct infix_udo : udo
{
	std::vector<udo *> before;
	std::vector<udo *> after;
};

struct prefix_udo : udo
{ };

struct postfix_udo : udo
{ };

struct object : entity
{ };

using scope = std::vector<std::unique_ptr<entity>>;

constexpr auto is_id_nondigit_char(
	const char *s)
{
	return
		*s >= 'a' && *s <= 'z'
		|| *s >= 'A' && *s <= 'Z'
		|| *s == '_';
}

constexpr auto is_id_char(
	const char *s)
{
	return
		is_id_nondigit_char(s)
		|| *s >= '0' && *s <= '9';
}

constexpr auto is_array_type(
	const char *s)
-> bool
{
	return *s == '[';
}

constexpr auto is_pointer_type(
	const char *s)
-> bool
{
	return *s == '@';
}

constexpr auto is_compound_type(
	const char *s)
-> bool
{
	return 
		is_pointer_type(s)
		|| is_array_type(s);
}

constexpr auto is_ws(
	const char *s)
-> bool
{
	return *s == ' '
		|| *s == '\t'
		|| *s == '\n';
}

constexpr void skip_ws(
	const char *&s)
{
	while(is_ws(s)) ++s;
}

constexpr void skip_array(
	const char *&s)
{
	while(*s++ != ']');
}

constexpr void skip_pointer(
	const char *&s)
{
	s++;
}

constexpr void skip_compound(
	const char *&s)
{
	return (is_array_type(s) ? skip_array : skip_pointer)(s);
}

constexpr auto try_skip_compound(
	const char *&s)
-> bool
{
	if(is_compound_type(s))
	{
		skip_compound(s);
		return true;
	}
	else
	{
		return false;
	}
}
constexpr auto skip_all_compounds(
	const char *&s)
{
	while(try_skip_compound(s)) skip_ws(s);
}

constexpr auto is_object_declaration(
	const char *s)
{
	return *s != '&';
}

constexpr auto is_reference_declaration(
	const char *s)
{
	return *s == '&';
}

constexpr auto ends_decl_id(
	const char *s)
-> bool
{
	return *s == ' '
		|| is_pointer_type(s)
		|| is_array_type(s)
		|| *s == '=';
}

constexpr auto ends_decl_primary(
	const char *s)
-> bool
{
	return *s == ' '
		|| *s == '\n'
		|| *s == '=' 
		|| *s == ';';
}
constexpr void skip_decl_primary(
	const char *&s)
{
	while(!ends_decl_primary(s)) ++s;
}

constexpr void skip_decl_typename(
	const char *&s)
{
	skip_all_compounds(s);
	skip_decl_primary(s);
}

constexpr void skip_decl_id(
	const char *&s)
{
	while(!ends_decl_id(s)) ++s;
}

std::string copy_typename(
	const char *&s)
{
	auto begin = s;
	skip_decl_typename(s);
	return std::string(begin, s);
}

constexpr void skip_object_declarator(
	const char *&s)
{
	skip_decl_id(s);
	skip_ws(s);
	skip_decl_typename(s);
}
}