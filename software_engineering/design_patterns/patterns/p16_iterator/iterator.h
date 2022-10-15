//
// Created by Shuyang Sun on 10/15/22.
//

#ifndef DESIGN_PATTERNS_PATTERNS_P16_ITERATOR_ITERATOR_H_
#define DESIGN_PATTERNS_PATTERNS_P16_ITERATOR_ITERATOR_H_

#include "absl/status/statusor.h"

namespace pattern {

template<class Item>
class IIterator {
 public:
  virtual void First() = 0;
  virtual void Next() = 0;
  [[nodiscard]] virtual bool IsDone() const = 0;
  [[nodiscard]] virtual absl::StatusOr<Item> CurrentItem() const = 0;
};

} // pattern

#endif //DESIGN_PATTERNS_PATTERNS_P16_ITERATOR_ITERATOR_H_
