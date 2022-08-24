[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 4](./README.md)

# Item 4: Know how to view deduced types.

Use `boost::typeindex`, [item_1.cpp](../item_1/item_1.cpp) and [item_2.cpp](../item_2/item_2.cpp) both used it extensively. `std::type_info::name` is unreliable.

```c++
int x{1};
boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name(); // int

template<typename T>
void f(T&& param) {
  std::cout << "param: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
  std::cout << "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}
```