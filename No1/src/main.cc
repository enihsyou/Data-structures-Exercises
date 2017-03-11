#include <iostream>
#include "../include/sequential_list.h"
#include "../include/linked_list.h"
int main() {
  std::cout << "|||Sequential list demo|||" << std::endl;
  auto s_list = sequential_list<int>();
  /*Empty test*/
  s_list.print();

  /*Insert range integers*/
  int items_limit;
  std::cout << "Generate number range from 0 to ";
  std::cin >> items_limit;
  for (auto i = 0; i < items_limit; ++i) {
    s_list.put(i);
  }
  s_list.print();

  /*Manually insert*/
  std::cout << "Type number to insert (-1 to stop)";
  std::cin >> items_limit;
  while (items_limit != -1) {
    s_list.put(items_limit);
    s_list.print();
    std::cin >> items_limit;
  }

  /*Remove the specified item*/
  int index;
  std::cout << "Item place to remove: ";
  std::cin >> index;
  s_list.del(index);
  s_list.print();

  /*Search for number 98*/
  int search_for;
  std::cout << "Search for number: ";
  std::cin >> search_for;
  const int result1 = s_list.search(search_for);
  if (result1 == -1) {
    std::cout << "Number " << search_for << " not found" << std::endl;
  } else {
    std::cout << "number " << search_for << " is on " << result1 << std::endl;
  }

  /*Insert item*/
  int item_to_insert;
  std::cout << "Item to insert: ";
  std::cin >> item_to_insert;
  s_list.put(item_to_insert);
  s_list.print();

  std::cout << "|||Linked list demo|||" << std::endl;

  auto l_list = linked_list<int>();
  /*Empty test*/
  l_list.print();

  /*Insert range integers*/
  std::cout << "Generate number range from 0 to ";
  std::cin >> items_limit;
  for (auto i = items_limit - 1; i >= 0; --i) {
    l_list.insert(i);
  }
  l_list.print();

  /*Manually insert*/
  std::cout << "Type number to insert (-1 to stop): ";
  std::cin >> items_limit;
  while (items_limit != -1) {
    l_list.insert(items_limit);
    l_list.print();
    std::cin >> items_limit;
  }
  std::cout << "Specified lower bound and uper bound to remove: ";
  std::cin >> index >> items_limit;
  l_list.remove(index, items_limit);
  l_list.print();

  /*Remove the specified item*/
  std::cout << "Item place to remove: ";
  std::cin >> index;
  l_list.remove(index);
  l_list.print();

  /*Insert number to the head*/
  int number_to_insert;
  std::cout << "Number inserted to head: ";
  std::cin >> number_to_insert;
  l_list.insert(number_to_insert);
  l_list.print();

  /*Remove items from head*/
  int num;
  std::cout << "How many items should be removed: ";
  std::cin >> num;
  for (auto i = 0; i < num; ++i) {
    l_list.remove();
  }
  l_list.print();

  /*Insert number, away from tail*/
  int new_num, offset;
  std::cout << "Input a number and offset away from tail: ";
  std::cin >> new_num >> offset;
  l_list.insert(new_num, l_list.size() - offset);
  l_list.print();

  /*Search for number*/
  std::cout << "Search for number: ";
  std::cin >> search_for;
  const int result2 = l_list.where(search_for);
  if (result2 == -1) {
    std::cout << "Number " << search_for << " not found" << std::endl;
  } else {
    std::cout << "number " << search_for << " is on " << result2 << std::endl;
  }

  /*Inplace reverse*/
  std::cout << "Inplace reverse list" << std::endl;
  l_list.reverse();
  l_list.print();

  /*Merge to list*/
  std::cout << "Merge two list" << std::endl;
  linked_list<int> one = linked_list<int>();
  linked_list<int> two = linked_list<int>();
  std::cout << "List one: ";
  for (int j = 20; j >= 10; j -= 2) {
    one.insert(j);
  }
  one.print();
  std::cout << "List two: ";
  for (int k = 17; k >= 7; k -= 2) {
    two.insert(k);
  }
  two.print();
  linked_list<int> three = linked_list<int>(one, two);
  std::cout << "List three (from merging): ";
  three.print();
  std::cout << "List three (reversed): ";
  three.reverse();
  three.print();

  return 0;
}



