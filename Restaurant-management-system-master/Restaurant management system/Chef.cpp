#include "Chef.h"
std::ostream& operator<<(std::ostream& os, const Chef* c) {
	if (c != nullptr) {
		os << "" << c->getID();
	}
	return os;
}