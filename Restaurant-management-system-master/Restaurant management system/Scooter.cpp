#include "Scooter.h"
std::ostream& operator<<(std::ostream& os, const Scooter* s) {
    if (s != nullptr) {
        os << s->getID();
    }
    return os;
}
