#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

namespace petrov
{
  template<class Key, class Value, class Equal>
  class HashTable
  {
    public:
      void add (Key k, Value v);
      Value drop (Key k);
      bool has (Kay k);
      void rehash (size_t slots);
  };

}
#endif
