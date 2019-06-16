#include "InitStringBuilder.hpp"

InitStringBuilder::InitStringBuilder(unsigned int factorySize,
        unsigned int linkSize) : factorySize(factorySize), linkSize(linkSize) {
}

void InitStringBuilder::AddLink(const LinkConstPtr &link) {
    linkStream << link->GetOne()->GetId() << " " << link->GetTwo()->GetId() << " " << link->GetDistance() / 800 << "\n";
}

std::string InitStringBuilder::Build() const {
    return std::to_string(factorySize) + "\n" + std::to_string(linkSize) + "\n" + linkStream.str();
}