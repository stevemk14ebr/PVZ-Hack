#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <sstream>
#define INLINE __forceinline

/*32 bit FNV_prime = 224 + 28 + 0x93 = 16777619
64 bit FNV_prime = 240 + 28 + 0xb3 = 1099511628211
128 bit FNV_prime = 288 + 28 + 0x3b = 309485009821345068724781371

32 bit offset_basis = 2166136261
64 bit offset_basis = 14695981039346656037
128 bit offset_basis = 144066263297769815596495629667062367629*/
#undef snprintf
#define snprintf c99_snprintf
inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
	int count = -1;

	if (size != 0)
		count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
	if (count == -1)
		count = _vscprintf(format, ap);

	return count;
}
inline int c99_snprintf(char* str, size_t size, const char* format, ...)
{
	int count;
	va_list ap;

	va_start(ap, format);
	count = c99_vsnprintf(str, size, format, ap);
	va_end(ap);

	return count;
}

template <typename HashFunction>
class StringCrypt
{
public:
	template <std::size_t N>
	INLINE StringCrypt(const char(&value)[N])
		: _hash(HashFunction::hash<N>(value))
	{ }

	INLINE std::uint32_t getHash() { return _hash; }
	operator const std::uint32_t&() const {
		return m_hash;
	}
private:
	std::uint32_t _hash;
};

struct HashFNV1a
{
	template <std::size_t N>
	INLINE static std::uint32_t hash(const char(&value)[N])
	{
		return (hash<N - 1>((const char(&)[N - 1])value) ^ value[N - 1]) * 16777619u;
	}

	template <>
	INLINE static std::uint32_t hash<1>(const char(&value)[1])
	{
		return (2166136261u ^ value[0]) * 16777619u;
	}
};
typedef StringCrypt<HashFNV1a> FNV1Crypt;


//Just waiting for VS to support constexpr here *COME ON MICROSOFT!!!*
//#define SEED ((__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10  + \
//	(__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 + \
//	(__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000)
//
//template <uint32_t Const> struct vxCplConstantify { enum { Value = Const }; };
//
//constexpr uint32_t vxCplRandom(uint32_t Id)
//{
//	return (1013904223 + 1664525 * ((Id > 0) ? (vxCplRandom(Id - 1)) : (SEED))) & 0xFFFFFFFF;
//}
//
//// Compile-time random macros, can be used to randomize execution  
//// path for separate builds, or compile-time trash code generation
//#define RAND()           (vxCplConstantify<vxCplRandom(__COUNTER__ + 1)>::Value)
//#define RANDOM(Min, Max) (Min + (RAND() % (Max - Min + 1)))
std::vector<std::string> Strings;
void Seperate(std::string str, std::vector<std::string> &Strings)
{
	std::istringstream ss(str);
	std::string tempstring;
	while (std::getline(ss, tempstring, ',')) //break input into lines seperated by new line character \n
	{
		Strings.push_back(tempstring); //add to vector
	}
}

__forceinline std::string HexEncodeString(std::string in)
{
	std::string ret;
	char buf[5];

	unsigned long len = in.length();
	for (int i = 0; i < len; i++)
	{
		snprintf(buf, sizeof(buf), "0x%02x", (unsigned char)in[i]);
		ret += buf;
		if (i < len - 1)
			ret += ",";
	}
	return ret;
}
std::string SXor(std::string value, std::string key)
{
	std::string ret(value);
	unsigned long klen = key.length();
	unsigned long vlen = value.length();
	unsigned long keyIndex = 0;
	unsigned long valIndex = 0;
	for (; valIndex < vlen; valIndex++) {
		ret[valIndex] = value[valIndex] ^ key[keyIndex];
		if (!(keyIndex++ < klen))
			keyIndex = 0;
	}
	return ret;
}
std::string HexDecrypt(std::string in, std::string key)
{
	std::vector<std::string> Vec;
	Seperate(in, Vec);
	std::stringstream ss;
	for (auto i : Vec)
	{
		ss << (char)std::stoul(i, nullptr, 16);
	}
	return SXor(ss.str(), key);
}