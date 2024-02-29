#pragma once
#include "../include/ClassExample.h"

#include <iostream>

ClassExample::ClassExample() : m_n(10) {};

void ClassExample::print()
{
	std::cout << "n: " << m_n << std::endl;
}

void ClassExample::setAndPrint(int n)
{
	m_n = n;
	std::cout << "n: " << m_n << std::endl;
}

void ClassExample::set(int n)
{
	m_n = n;
}
