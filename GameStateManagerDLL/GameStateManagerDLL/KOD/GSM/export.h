#pragma once

#ifdef KOD_GSM_EXPORT
#define KOD_GSM_DLL __declspec(dllexport)
#else
#define KOD_GSM_DLL __declspec(dllimport)
#endif