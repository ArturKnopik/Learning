#pragma once

#ifdef LOGGER_EXPORT
#define LOGGER_DLL __declspec(dllexport)
#else
#define LOGGER_DLL __declspec(dllimport)
#endif