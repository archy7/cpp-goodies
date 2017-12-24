#pragma once

#include <stdint.h>
#include <string>

/*
	This class provides a more efficient way to handle intenal strings that are only visible to the programmer.
	This class works with the premise that integer comparison is faster that string comparison.

	You can use HashString given following preconditions:
		The hashed string is constant (therefore every string literal).
		The hashed string serves as an identity of some sort and is solely used for comparisons (like IDs stored as strings).

	Therefore, HashString is also handy for building hash maps which would normally feature a string-type key.
*/
class HashString {
public:

	// Constructor for c-strings
	explicit HashString(const char* pHashedString) :
		m_uiHashOfString(HashString::PerformHash(pHashedString))
	{

	}

	// Constructor for std::strings
	explicit HashString(const std::string& rHashedString) :
		m_uiHashOfString(HashString::PerformHash(rHashedString.c_str()))
	{

	}

	// Copy Constructor
	HashString(const HashString& rOtherHashString) :
		m_uiHashOfString(rOtherHashString.m_uiHashOfString)
	{

	}

	// Assignment operator deleted. Assigning to instances of HashString would undermine class design.
	HashString& operator= (const HashString& rOtherHashString) = delete;

	bool operator== (const char* pOtherString) const
	{
		return m_uiHashOfString == HashString::PerformHash(pOtherString);
	}

	bool operator== (const std::string& rOtherString) const
	{
		return m_uiHashOfString == HashString::PerformHash(rOtherString.c_str());
	}

	bool operator== (const HashString& rOtherHashString) const
	{
		return m_uiHashOfString == rOtherHashString.m_uiHashOfString;
	}

	bool operator!= (const char* pOtherString) const
	{
		return !operator==(pOtherString);
	}

	bool operator!= (const std::string& rOtherString) const
	{
		return !operator==(rOtherString.c_str());
	}

	bool operator!= (const HashString& rOtherHashString) const
	{
		return !operator==(rOtherHashString);
	}

	static bool operator== (const char* pString, const HashString& rHashString)
	{
		return rHashString.operator==(pString);
	}

	static bool operator== (const std::string rString, const HashString& rHashString)
	{
		return rHashString.operator==(rString);
	}

	static bool operator!= (const char* pString, const HashString& rHashString)
	{
		return !rHashString.operator==(pString);
	}

	static bool operator!= (const std::string rString, const HashString& rHashString)
	{
		return !rHashString.operator==(rString);
	}
private:
	//Members
	const uint64_t m_uiHashOfString;	// The hash value of the given string

	//Methods

	/*
		Takes a C-String and returns its hashed value as 64-bit unsigned integer.
	*/

	static uint64_t PerformHash(const char* pHashedString)
	{
		// see: https://stackoverflow.com/questions/2535284/how-can-i-hash-a-string-to-an-int-using-c

		uint64_t uiHashValue = 5381u;
		uint32_t uiCharacter;

		while (uiCharacter = *pHashedString++) {
			uiHashValue = uiHashValue * 33u + uiCharacter;
		}

		return uiHashValue;
	}
};