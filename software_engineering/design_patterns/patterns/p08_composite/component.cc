#include "patterns/p08_composite/component.h"

#include <utility>
#include <sstream>

[[nodiscard]] absl::Status pattern::IComponent::Add(std::unique_ptr<IComponent> component) {
  uint64_t tmp;
  return this->Add(std::move(component), tmp);
}

[[nodiscard]] absl::Status pattern::IComponent::Add(std::unique_ptr<IComponent> component, uint64_t& component_id) {
  return absl::AbortedError("Cannot add component to leaf component.");
}

absl::Status pattern::IComponent::RemoveById(uint64_t component_id) {
  return absl::AbortedError("Cannot remove component to leaf component.");
}

absl::Status pattern::IComponent::RemoveByFilter(std::function<bool(const IComponent &)> predicate) {
  return absl::AbortedError("Cannot remove component to leaf component.");
}
