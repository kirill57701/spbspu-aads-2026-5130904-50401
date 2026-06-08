#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <utility>

namespace detail
{
  template< class T >
  struct Node
  {
    T val;
    Node<T>* next;
    Node<T>* prev;
    Node(const T& v, Node< T >* n = nullptr, Node< T >* p = nullptr);
    Node(T&& v, Node<T>* n = nullptr, Node<T>* p = nullptr);
  };
  template< class T >
  Node<T>::Node(const T& v, Node<T>* n, Node<T>* p):
    val(v),
    next(n),
    prev(p)
  {}

  template< class T >
  Node<T>::Node(T&& v, Node<T>* n, Node<T>* p):
    val(std::forward<T>(v)),
    next(n),
    prev(p)
  {}
};

namespace petrov
{
  template<class T>
  class LIter;

  template<class T>
  class LCIter;

  template<class T>
  class List
  {
  public:
    List();
    List(const List<T>& l);
    List(List<T>&& l) noexcept;
    List(size_t s, const T& init);
    ~List();

    List<T>& operator=(List<T>&& l) noexcept;
    List<T>& operator=(List<T> l);

    bool empty() const noexcept;
    size_t size() const noexcept;
    LIter<T> begin() noexcept;
    LIter<T> end() noexcept;
    LCIter<T> begin() const noexcept;
    LCIter<T> end() const noexcept;

    void push_back(const T& d);
    void push_back(T&& d);

    void push_front(const T& d);
    void push_front(T&& d);

    void swap(List<T>& d) noexcept;
    void pop_back();
    void pop_front();
    void clear();
  private:
    detail::Node<T>* h;
    detail::Node<T>* t;
    size_t s;
  };

  template<class T>
  class LIter
  {
  public:
    LIter() : cur(nullptr) {}
    LIter(detail::Node<T>* n) : cur(n) {}
    bool operator==(const LIter<T>& i) const;
    bool operator!=(const LIter<T>& i) const;
    T& operator*();
    LIter<T>& operator++();
    LIter<T>& operator++(int);
    LIter<T>& operator--();
    LIter<T>& operator--(int);
    T* operator->();
  private:
    friend class List<T>;
    detail::Node<T>* cur;
  };

  template<class T>
  class LCIter
  {
  public:
    LCIter() : cur(nullptr) {}
    LCIter(detail::Node<T>* n) : cur(n) {}
    bool operator==(const LCIter<T>& i) const;
    bool operator!=(const LCIter<T>& i) const;
    const T& operator*() const;
    LCIter<T>& operator++();
    LCIter<T>& operator--();
    const T* operator->() const;
  private:
    friend class List<T>;
    const detail::Node<T>* cur;
};
  template<class T>
  List<T>::List():
    h(nullptr),
    t(nullptr),
    s(0)
  {}

  template<class T>
  void List<T>::clear()
  {
    if (h != nullptr)
    {
      while (h->next != nullptr)
      {
        detail::Node<T>* promej = h->next;
        delete h;
        h = promej;
      }
      delete h;
    }
    h = nullptr;
    t = nullptr;
    s = 0;
  }

  template<class T>
  List<T>::~List()
  {
    clear();
  }

  template<class T>
  void List<T>::pop_front()
  {
    if (!empty())
    {
      detail::Node<T>* new_h = h->next;
      delete h;
      h = new_h;
      if (h == nullptr)
      {
        t = nullptr;
        s = 0;
        return;
      }
      h->prev = nullptr;
      s--;
    }
  }

  template<class T>
  void List<T>::swap(List<T>& d) noexcept
  {
    std::swap(h, d.h);
    std::swap(t, d.t);
    std::swap(s, d.s);
  }

  template<class T>
  void List<T>::pop_back()
  {
    if (!empty())
    {
      detail::Node<T>* new_t = t->prev;
      delete t;
      t = new_t;
      if (t == nullptr)
      {
        h = nullptr;
        s = 0;
        return;
      }
      t->next = nullptr;
      s--;
    }
  }

  template<class T>
  bool List<T>::empty() const noexcept
  {
    return (!s || h == nullptr);
  }

  template<class T>
  size_t List<T>::size() const noexcept
  {
    return s;
  }

  template<class T>
  void List<T>::push_back(const T& d)
  {
    if (empty())
    {
      h = new detail::Node<T>(d);
      h->next = nullptr;
      h->prev = nullptr;
      t = h;
      s = 1;
      return;
    }
    t->next = new detail::Node<T>(d);
    t->next->prev = t;
    t = t->next;
    t->next = nullptr;
    s++;
  }

  template<class T>
  void List<T>::push_front(const T& d)
  {
    if (empty())
    {
      h = new detail::Node<T>(d);
      h->next = nullptr;
      h->prev = nullptr;
      t = h;
      s = 1;
      return;
    }
    h->prev = new detail::Node<T>(d);
    h->prev->next = h;
    h = h->prev;
    h->prev = nullptr;
    s++;
  }

  template< class T >
  void List<T>::push_back(T&& d)
  {
    if (empty())
    {
      h = new detail::Node<T>(std::move(d));
      h->next = nullptr;
      h->prev = nullptr;
      t = h;
      s = 1;
      return;
    }
    t->next = new detail::Node<T>(std::move(d));
    t->next->prev = t;
    t = t->next;
    t->next = nullptr;
    s++;
  }

  template< class T >
  void List<T>::push_front(T&& d)
  {
    if (empty())
    {
      h = new detail::Node<T>(std::move(d));
      h->next = nullptr;
      h->prev = nullptr;
      t = h;
      s = 1;
      return;
    }
    h->prev = new detail::Node<T>(std::move(d));
    h->prev->next = h;
    h = h->prev;
    h->prev = nullptr;
    s++;
  }

  template<class T>
  List<T>::List(const List<T>& l):
    h(nullptr),
    t(nullptr),
    s(0)
  {
    detail::Node<T>* nod = l.h;
    while (nod != nullptr)
    {
      push_back(nod->val);
      nod = nod->next;
    }
  }

  template<class T>
  List<T>& List<T>::operator=(List<T> l)
  {
    swap(l);
    return *this;
  }

  template<class T>
  List<T>::List(List<T>&& l) noexcept:
    h(std::exchange(l.h, nullptr)),
    t(std::exchange(l.t, nullptr)),
    s(std::exchange(l.s, 0))
  {}

  template<class T>
  List<T>& List<T>::operator=(List<T>&& l) noexcept
  {
    swap(l);
    return *this;
  }

  template<class T>
  List<T>::List(size_t s, const T& init):
    h(nullptr),
    t(nullptr),
    s(0)
  {
    for (size_t i = 0; i < s; ++i)
    {
      push_back(init);
    }
  }

  template<class T>
  LIter<T> List<T>::begin() noexcept
  {
    return LIter<T>(h);
  }

  template<class T>
  LIter<T> List<T>::end() noexcept
  {
    return LIter<T>(nullptr);
  }

  template<class T>
  LIter<T>& LIter<T>::operator++()
  {
    if (cur != nullptr)
    {
      cur = cur->next;
    }
    return *this;
  }

  template<class T>
  LIter<T>& LIter<T>::operator++(int)
  {
    LIter<T> d = *this;
    ++(*this);
    return d;
  }

  template<class T>
  LIter<T>& LIter<T>::operator--(int)
  {
    LIter<T> d = *this;
    --(*this);
    return d;
  }

  template<class T>
  LIter<T>& LIter<T>::operator--()
  {
    if (cur != nullptr)
    {
      cur = cur->prev;
    }
    return *this;
  }

  template<class T>
  T& LIter<T>::operator*()
  {
    return cur->val;
  }

  template<class T>
  T* LIter<T>::operator->()
  {
    return &(cur->val);
  }

  template<class T>
  bool LIter<T>::operator==(const LIter<T>& i) const
  {
    return !(cur != i.cur);
  }

  template<class T>
  bool LIter<T>::operator!=(const LIter<T>& i) const
  {
    return cur != i.cur;
  }

  template<class T>
  bool LCIter<T>::operator==(const LCIter<T>& i) const
  {
    return !(cur != i.cur);
  }

  template<class T>
  bool LCIter<T>::operator!=(const LCIter<T>& i) const
  {
    return cur != i.cur;
  }

  template<class T>
  const T& LCIter<T>::operator*() const
  {
    return cur->val;
  }

  template<class T>
  const T* LCIter<T>::operator->() const
  {
    return std::addressof(cur->val);
  }

  template<class T>
  LCIter<T>& LCIter<T>::operator++()
  {
    if (cur != nullptr)
    {
      cur = cur->next;
    }
    return *this;
  }

  template<class T>
  LCIter<T>& LCIter<T>::operator--()
  {
    if (cur != nullptr)
    {
      cur = cur->prev;
    }
    return *this;
  }

  template<class T>
  LCIter<T> List<T>::begin() const noexcept
  {
    return LCIter<T>(h);
  }

  template<class T>
  LCIter<T> List<T>::end() const noexcept
  {
    return LCIter<T>(nullptr);
  }
};

#endif
