#pragma once

#ifdef KOD_GUI_EXPORT
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif