#include "APM_Practica17.h"
#include <stdio.h>
#include <string.h>
#include <cassert>

//Apartado 1 (con implementacion de enums del apartado 2)
#define STRING_TO_ENUM(_STR)\
if(strcmp(#_STR, _sEnum) == 0)\
{\
	return Enum::_STR;\
}
#define ENUM_TO_STRING(_ENUM)\
if(_eValue == Enum::_ENUM)\
{\
	return #_ENUM;\
}


//Apartado 2
#define DECLARE_ENUM_VALUE(_ENUM) _ENUM, 

#define DECLARE_ENUM(_NAME, _LIST)\
struct _NAME\
{\
	enum Enum\
	{\
		Invalid,\
		_LIST(DECLARE_ENUM_VALUE)\
	};\
\
	static Enum ToEnum(const char* _sEnum)\
	{\
		_LIST(STRING_TO_ENUM)\
		assert(false);\
		return Enum::Invalid;\
	};\
\
	static const char* ToStr(Enum _eValue)\
	{\
		_LIST(ENUM_TO_STRING)\
		assert(false);\
		return "Invalid";\
	};\
};

#define ENUM_LIST(_ACTION)\
	_ACTION(Val1)\
	_ACTION(Val2)


DECLARE_ENUM(SPrueba, ENUM_LIST)

int main() 
{
	SPrueba::Enum eEnum = SPrueba::ToEnum("Val1");
	
	printf("%s\n", SPrueba::ToStr(SPrueba::Val1));
	return 0;
}
