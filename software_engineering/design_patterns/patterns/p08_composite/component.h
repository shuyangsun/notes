#ifndef DESIGN_PATTERNS_PATTERNS_P08_COMPOSITE_COMPONENT_H_
#define DESIGN_PATTERNS_PATTERNS_P08_COMPOSITE_COMPONENT_H_

#include <memory>
#include <functional>
#include <cstdint>

#include "absl/status/status.h"

namespace pattern {

class IComponent {
 public:
  virtual ~IComponent() = default;

  [[nodiscard]] virtual absl::Status Add(std::unique_ptr<IComponent> component);
  [[nodiscard]] virtual absl::Status Add(std::unique_ptr<IComponent> component, uint64_t& component_id);
  [[nodiscard]] virtual absl::Status RemoveById(uint64_t component_id);
  [[nodiscard]] virtual absl::Status RemoveByFilter(std::function<bool (const IComponent&)> predicate);
};

}  // namespace pattern

#endif  // DESIGN_PATTERNS_PATTERNS_P08_COMPOSITE_COMPONENT_H_
