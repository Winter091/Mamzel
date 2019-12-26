#pragma once

void clearErrors();
void printErrors(const char* funcName, const char* fileName, int line);

#ifdef _DEBUG
#define HANDLE_ERROR(x) clearErrors(); x ;printErrors(#x, __FILE__, __LINE__)
#else
#define HANDLE_ERROR(x) x
#endif