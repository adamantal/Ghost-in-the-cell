#include "InitStringBuilder.hpp"

InitStringBuilder::InitStringBuilder(unsigned int factorySize,
        unsigned int linkSize) : factorySize(factorySize), linkSize(linkSize) {
}

void InitStringBuilder::addLink(const LinkConstPtr& link) {
    linkStream << link->getOne()->getId() << " " << link->getTwo()->getId() << " " << link->getDistance() / 800 << "\n";
}

std::string InitStringBuilder::build() const {
    return std::to_string(factorySize) + "\n" + std::to_string(linkSize) + "\n" + linkStream.str();
}