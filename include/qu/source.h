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

struct source_cache_line
{
	using clock_t = std::chrono::high_resolution_clock;
	using time_point_t = clock_t::time_point;
	
	static constexpr auto log_line_size = (std::size_t)(12);
	static constexpr auto line_size = (std::size_t)(1) << log_line_size;
	static constexpr auto line_number_mask = (std::size_t)(-1) << log_line_size;
	
	time_point_t touched;
	char data[line_size];
};

auto touch(
	source_cache_line &line)
-> source_cache_line::time_point_t
{
	line.touched
		 = source_cache_line::clock_t::now();

	return line.touched;
}

constexpr auto line_number_of_offset(
	std::size_t offset)
noexcept -> std::size_t
{
	return offset
		 & source_cache_line::line_number_mask;
}

struct source_cache_map
{
	using lines_t = std::vector<source_cache_line>;

	std::size_t line_number;
	lines_t::iterator line_it;
};

auto line_before = [](
	const source_cache_map &l,
	const source_cache_map &r)
{
	return l.line_number
		 < r.line_number;
};

using line_before_t = decltype(line_before);

auto touched_after = [](
	const source_cache_map &l,
	const source_cache_map &r)
{
	return l.line_it->touched
		 < r.line_it->touched;
};

using touched_after_t = decltype(touched_after);

struct source_cache
{
	using maps_t = std::set<
		source_cache_map,
		line_before_t>;

	using chronology_container = std::vector<maps_t::iterator>;

	using chronology_t = std::priority_queue<
		maps_t::iterator,
		chronology_container,
		touched_after_t>;
	
	source_cache_map::lines_t lines;

	maps_t maps;
	chronology_t chronology;
};

struct source_file
{
	std::filesystem::path path;
	std::ifstream in;
	source_cache cache;
};

void fetch_source_cache_line(
	source_file &source,
	source_cache_map &map)
{
	source.in.seekg(
		map.line_number);

	source.in.read(
		map.line_it->data,
		source_cache_line::line_size);
}

auto insert_source_cache_line(
	source_file &source,
	std::size_t line_number)
-> source_cache_map
{
	auto &lines = source.cache.lines;
	auto &maps = source.cache.maps;

	lines.emplace_back();
	
	auto line_it = end(lines) - 1;

	auto map = source_cache_map
	{
		line_number,
		line_it
	};

	maps.insert(
		map);

	fetch_source_cache_line(
		source,
		map);

	return map;
}

auto query_source_cache_line(
	source_file &source,
	std::size_t line_number)
-> source_cache_map
{
	auto &maps = source.cache.maps;

	auto map_it = std::lower_bound(
		begin(maps),
		end(maps),
		source_cache_map{ },
		line_before);

	if (map_it == end(maps))
	{
		auto map = insert_source_cache_line(
			source,
			line_number);
		
		return map;
	}
	else
	{
		return *map_it;
	}
}

struct source_cache_iterator
{
	source_file *file;
	source_cache_map map;
	std::size_t offset;
};

auto offset_in_cache_line(
	std::size_t offset)
-> std::size_t
{
	return offset & ~source_cache_line::line_number_mask;
}

auto offset_in_cache_line(
	source_cache_iterator it)
-> std::size_t
{
	return offset_in_cache_line(it.offset);
}

auto operator *(
	const source_cache_iterator &it)
noexcept
-> char
{	
	auto &line = *it.map.line_it;

	touch(line);
	
	auto offset_in_line = offset_in_cache_line(it.offset);

	return line.data[offset_in_line];
}

auto operator++(
	source_cache_iterator &it)
noexcept -> source_cache_iterator &
{
	++it.offset;

	auto offset_in_line = offset_in_cache_line(it.offset);

	if (0 == offset_in_line)
	{
		auto line_number = line_number_of_offset(
			it.offset);

		query_source_cache_line(
			*it.file,
			line_number);
	}

	return it;
}

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

int main()
{
	poi::source_file f;
	f.in.open("a.c", std::ios_base::in);
	if(!f.in)
	{
		return 1;
	}
	auto it = poi::query_source_cache_line(
		f,
		0);
	std::cout << *it;

	auto r = poi::bench<std::chrono::high_resolution_clock>([]()
	{
			std::cout << "12345";
			return 5;
	});

	auto i = "let bob[]:int ;lian4$$";
	auto begin = i + 4;
	auto end = begin;
	poi::skip_object_declarator(end);
	std::cout << std::string(begin, end);
}