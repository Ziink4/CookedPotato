#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <array>
#include <map>
#include <cstring>
#include <regex>

enum class EToken
{
	eof,
	undefined,

	functionDefinition,
	externalImport,

	identifier,
	integerValue,
	floatingPointValue,
	specialChar,
};

static constexpr unsigned int kMaxBufferSize = 64;

static int integer;
static double floatingPoint;
static std::array<char, kMaxBufferSize> buffer;


struct charStringCompare { 
    bool operator () (const char *a, const char *b) const 
    {
        return std::strncmp(a, b, kMaxBufferSize) < 0;
    } 
};

static std::map<const char *, EToken, charStringCompare> kStringToToken = {
	{"def", EToken::functionDefinition},
	{"import", EToken::externalImport}
};

enum class EErrorCode
{
	identifierTooLong,
	unknown
};


/*
static EToken getToken()
{
	std::cin.exceptions(std::istream::failbit);
	static unsigned char lastCharacter = kSpaceCharacter;

	// Skips all whitespaces
	while (std::isspace(lastCharacter))
	{
		std::cin >> lastCharacter;
	}

	// Reads identifier
	if(std::isalpha(lastCharacter))
	{
		std::stringstream identifier;

		do
		{
			identifier << lastCharacter;

			std::cin >> lastCharacter;
		}
		while (std::isalnum(lastCharacter));

		auto it = kStringToToken.find(identifier.str());
		if (it != kStringToToken.end())
		{
			return it->second;
		}
		else
		{
			return EToken::identifier;
		}
	}

	if (std::isdigit(lastCharacter))
	{
		static const std::regex doubleRegex{ R"((?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+\-]?\d+)?)" };
		static const std::regex intRegex{ R"(\d+)" };
		std::stringstream number;

		do
		{
			number << lastCharacter;
			std::cin >> lastCharacter;
		}
		while (std::isdigit(lastCharacter) ||
		       lastCharacter == kFloatingPointSeparator ||
		       lastCharacter == kPlusSign ||
		       lastCharacter == kMinusSign);

		if (std::regex_match(number.str(), intRegex))
		{
			number >> integer;
			return EToken::integerValue;
		}
		else if (std::regex_match(number.str(), doubleRegex))
		{
			number >> floatingPoint;
			return EToken::floatingPointValue;
		}
		else
		{
			throw std::runtime_error("Could not parse number");
		}
	}

	if (lastCharacter == kCommentPrefix)
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), kLineDelimiter);

		if(!std::cin.eof())
		{
			return getToken();
		}
	}

	if(std::cin.eof())
	{
		return EToken::eof;
	}

	std::cin >> lastCharacter;
	return EToken::undefined;
}

*/

enum class EState
{
	start,
	skipSpace,
	error,
	end,
	readWord,
	integerNumber,
	floatingPointNumber,
	checkForKeyword,
	specialName,
	ignoreComment,
	returnEof,
	returnKeyword,
	returnIdentifier,
	returnNextToken,
	returnSpecialChar,
	returnInteger
};

static void readCharFromStream(std::istream& stream, unsigned char& character)
{
	stream.get(reinterpret_cast<char&>(character));
	std::cout << "  Popped char : " << character << std::endl;
}

static void unreadCharFromStream(std::istream& stream)
{
	stream.unget();
	std::cout << "  Rewinded char " << std::endl;
}

static EToken getTokenDFSM(std::istream& stream)
{
	// Stream initialization
	//stream.exceptions(std::istream::failbit);

	// Default state
	EState current_state = EState::start;
	EState next_state = EState::start;

	// Static vars
	static constexpr unsigned char kCommentPrefix = '#';
	static constexpr unsigned char kLineDelimiter = '\n';
	

	unsigned int index = 0;
	auto keywordIterator = kStringToToken.end();

	unsigned char character;
	readCharFromStream(stream, character);

	while(current_state != EState::error && current_state != EState::end)
	{
		// COMPUTE NEXT STATE
		switch (current_state)
		{
			case EState::start:
			case EState::skipSpace:
				if (stream.eof()) { next_state = EState::returnEof; }
				else if (std::isspace(character)) { next_state = EState::skipSpace; }
				else if (std::isalpha(character)) { next_state = EState::readWord; }
				else if (std::isdigit(character)) { next_state = EState::integerNumber; }
				else if (character == kCommentPrefix) { next_state = EState::ignoreComment; } 
				else { next_state = EState::returnSpecialChar; }
				break;
			case EState::readWord:
				if (std::isalnum(character)) { next_state = current_state; }
				else { next_state = EState::checkForKeyword; }
				break;
			case EState::checkForKeyword:
				if (keywordIterator != kStringToToken.end()) { next_state = EState::returnKeyword; }
				else { next_state = EState::returnIdentifier; }
				break;
			case EState::integerNumber:
				if (std::isdigit(character) || character == 'e' || character == 'E') { next_state = EState::integerNumber; }
				else if (character == '.') { next_state = EState::floatingPointNumber; }
				else { next_state = EState::returnInteger; }
				//Do stuff for integer nubers etc..
				break;
			case EState::floatingPointNumber:
				//Do stuff for FP
				break;
			case EState::ignoreComment:
				if (character == kLineDelimiter) { next_state = EState::returnNextToken; }
				else { next_state = current_state; }
				break;
			default:
				next_state = EState::end;
				break;
		}

		// GO TO NEXT STATE
		current_state = next_state;

		// DO ACTIONS
		switch (current_state)
		{
			case EState::start:
				std::cout << "  Do nothing" << std::endl;
				break;
			case EState::skipSpace:
				std::cout << "  Skipping space (" << character << ")" << std::endl;
				readCharFromStream(stream, character);
				break;
			case EState::readWord:
			case EState::integerNumber:
				if (index + 1 == kMaxBufferSize) { throw EErrorCode::identifierTooLong; }
				buffer[index] = character;
				buffer[index + 1] = 0;
				index++;
				std::cout << "  Reading char : " << character << "(" << std::string(reinterpret_cast<const char *>(buffer.data())) << ")" << std::endl;
				readCharFromStream(stream, character);
				break;
			case EState::checkForKeyword:
				index = 0;
				std::cout << "  Checking for keyword" << std::endl;
				keywordIterator = kStringToToken.find(reinterpret_cast<const char *>(buffer.data()));
				break;
			case EState::returnKeyword:
				std::cout << "  Returning keyword" << std::endl;
				unreadCharFromStream(stream);
				return keywordIterator->second;
			case EState::returnNextToken:
				return getTokenDFSM(stream);
			case EState::returnEof:
				return EToken::eof;
			case EState::returnIdentifier:
				std::cout << "  Returning identifier" << std::endl;
				unreadCharFromStream(stream);
				return EToken::identifier;
			case EState::returnInteger:
				floatingPoint = std::strtod(buffer.data(), nullptr);
				return EToken::integerValue;
			case EState::returnSpecialChar:
				std::cout << "  Returning special char : " << character << std::endl;
				return EToken::specialChar;
		}
	}
	// SET OUTPUT
	return EToken::eof;

}

int main()
{
	std::ifstream codeFile("code.raw");

	while (getTokenDFSM(codeFile) != EToken::eof && codeFile.good())
	{
		std::cout << integer << std::endl;
		std::cout << floatingPoint << std::endl;
		std::cout << std::string(std::begin(buffer), std::end(buffer)) << std::endl;

	}
}
