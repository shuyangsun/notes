#include "patterns/p08_composite/component.h"

#include <sstream>
#include <utility>

namespace pattern {

[[nodiscard]] absl::Status IComponent::Add(
    std::unique_ptr<IComponent> component) {
  uint64_t tmp;
  return this->Add(std::move(component), tmp);
}

[[nodiscard]] absl::Status IComponent::Add(
    std::unique_ptr<IComponent> component, uint64_t &component_id) {
  return absl::AbortedError("Cannot add component to leaf component.");
}

absl::Status IComponent::RemoveById(uint64_t component_id) {
  return absl::AbortedError("Cannot remove component to leaf component.");
}

absl::Status IComponent::RemoveByFilter(
    std::function<bool(const IComponent &)> predicate) {
  return absl::AbortedError("Cannot remove component to leaf component.");
}

std::unique_ptr<IIterator<const IComponent &>> IComponent::Iter() {
  return nullptr;
}
std::unique_ptr<IIterator<std::shared_ptr<IComponent>>> IComponent::IterMut() {
  return nullptr;
}

}  // namespace pattern
