#include "Resource.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace gameengine {

int Resource::resourceCount = 0;

Resource::Resource(const std::string& resName, const std::string& resType, int size)
    : name(resName), type(resType), sizeBytes(size), loaded(true) {
    if (size <= 0) {
        throw std::invalid_argument("Size must be positive");
    }
    resourceCount++;
    std::cout << "Resource loaded: " << name << " (" << type << ", " << sizeBytes << " bytes)\n";
}

Resource::~Resource() {
    resourceCount--;
    loaded = false;
    std::cout << "Resource unloaded: " << name << "\n";
}

std::shared_ptr<Resource> Resource::create(const std::string& name, const std::string& type, int sizeBytes) {
    // Use regular new because the constructor is private, so std::make_shared cannot access it
    return std::shared_ptr<Resource>(new Resource(name, type, sizeBytes));
}

int Resource::getResourceCount() {
    return resourceCount;
}

std::string Resource::getName() const { return name; }
std::string Resource::getType() const { return type; }
int Resource::getSizeBytes() const { return sizeBytes; }
bool Resource::isLoaded() const { return loaded; }

std::string Resource::toString() const {
    std::ostringstream oss;
    oss << name << " (" << type << ", " << sizeBytes << " bytes)";
    return oss.str();
}

} // namespace gameengine