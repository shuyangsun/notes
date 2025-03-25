#include <iostream>

#include "contact.pb.h"

int main() {
  phonebook::Contact contact;
  contact.set_name("Shuyang");
  contact.set_email("shuyang1010@gmail.com");
  contact.set_phone("+1 (123) 456-7890");
  std::cout << contact.DebugString() << std::endl;
  return 0;
}
