#include "Callable.h"

KOD::GUI::Callable::~Callable() {}

KOD::GUI::Callable::Callable(KOD::GUI::CallableFunc&& callable) { this->m_callable = std::move(callable); }

void KOD::GUI::Callable::execute()
{
	if (m_callable) {
		m_callable();
	}
}
