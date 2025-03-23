#ifndef NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_PRINTABLE_API_PRINTABLE_API_H_
#define NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_PRINTABLE_API_PRINTABLE_API_H_

namespace printable_api {

class IPrintable {
 public:
  virtual void Print() const = 0;
  virtual ~IPrintable() = default;
};

}  // namespace printable_api

#endif  // NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_PRINTABLE_API_PRINTABLE_API_H_
