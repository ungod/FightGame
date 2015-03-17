#pragma once

#define DELETE_VECTOR_PTR(vecType, vec)\
vecType::iterator it;\
for (it = vec.begin(); it != vec.end(); it++)\
{\
	if (NULL != *it)\
	{\
		delete *it;\
	}\
}\

#define RETURN_NULL_IF(expv) if (expv) return NULL
#define RETURN_FALSE_IF(expv) if (expv) return false;

//end