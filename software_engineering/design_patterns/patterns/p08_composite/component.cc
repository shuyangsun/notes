#include "patterns/p08_composite/component.h"

#include <utility>

[[nodiscard]] absl::Status pattern::IComponent::Add(std::unique_ptr<IComponent> component) {
  return this->Add(std::move(component), nullptr);
}

[[nodiscard]] absl::Status pattern::IComponent::Add(std::unique_ptr<IComponent> component, uint64_t* component_id) {
  return absl::AbortedError("Cannot add component to leaf component.");
}
