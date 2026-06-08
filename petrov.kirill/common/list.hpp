#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <utility>
#include <memory>

namespace detail
{
  template<class T>
  struct Node
  {
    T val_;
    Node<T>* next_;
    Node<T>* prev_;
    Node(const T& v, Node<T>* n = nullptr, Node<T>* p = nullptr);
    Node(T&& v, Node<T>* n = nullptr, Node<T>* p = nullptr);
  };

  template<class T>
  Node<T>::Node(const T& v, Node<T>* n, Node<T>* p) :
    val_(v),
    next_(n),
    prev_(p)
  {}

  template<class T>
  Node<T>::Node(T&& v, Node<T>* n, Node<T>* p) :
    val_(std::forward<T>(v)),
    next_(n),
    prev_(p)
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
    List<T>& operator=(const List<T>& l);

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
    detail::Node<T>* m_h;
    detail::Node<T>* m_t;
    size_t m_s;
  };

  template<class T>
  class LIter
  {
  public:
    LIter();
    LIter(detail::Node<T>* n);
    bool operator==(const LIter<T>& i) const;
    bool operator!=(const LIter<T>& i) const;
    T& operator*();
    LIter<T>& operator++();
    LIter<T> operator++(int);
    LIter<T>& operator--();
    LIter<T> operator--(int);
    T* operator->();
  private:
    friend class List<T>;
    detail::Node<T>* m_cur;
  };

  template<class T>
  LIter<T>::LIter() :
    m_cur(nullptr)
  {}

  template<class T>
  LIter<T>::LIter(detail::Node<T>* n) :
    m_cur(n)
  {}

  template<class T>
  class LCIter
  {
  public:
    LCIter();
    LCIter(const detail::Node<T>* n);
    bool operator==(const LCIter<T>& i) const;
    bool operator!=(const LCIter<T>& i) const;
    const T& operator*() const;
    LCIter<T>& operator++();
    LCIter<T>& operator--();
    const T* operator->() const;
  private:
    friend class List<T>;
    const detail::Node<T>* m_cur;
  };

  template<class T>
  LCIter<T>::LCIter() :
    m_cur(nullptr)
  {}

  template<class T>
  LCIter<T>::LCIter(const detail::Node<T>* n) :
    m_cur(n)
  {}

  template<class T>
  List<T>::List() :
    m_h(nullptr),
    m_t(nullptr),
    m_s(0)
  {}

  template<class T>
  void List<T>::clear()
  {
    while (m_h != nullptr)
    {
      detail::Node<T>* next_ = m_h->next_;
      delete m_h;
      m_h = next_;
    }
    m_t = nullptr;
    m_s = 0;
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
      detail::Node<T>* new_h_ = m_h->next_;
      delete m_h;
      m_h = new_h_;
      if (m_h == nullptr)
      {
        m_t = nullptr;
      }
      else
      {
        m_h->prev_ = nullptr;
      }
      m_s--;
    }
  }

  template<class T>
  void List<T>::swap(List<T>& d) noexcept
  {
    std::swap(m_h, d.m_h);
    std::swap(m_t, d.m_t);
    std::swap(m_s, d.m_s);
  }

  template<class T>
  void List<T>::pop_back()
  {
    if (!empty())
    {
      detail::Node<T>* new_t_ = m_t->prev_;
      delete m_t;
      m_t = new_t_;
      if (m_t == nullptr)
      {
        m_h = nullptr;
      }
      else
      {
        m_t->next_ = nullptr;
      }
      m_s--;
    }
  }

  template<class T>
  bool List<T>::empty() const noexcept
  {
    return m_s == 0;
  }

  template<class T>
  size_t List<T>::size() const noexcept
  {
    return m_s;
  }

  template<class T>
  void List<T>::push_back(const T& d)
  {
    detail::Node<T>* new_node = new detail::Node<T>(d, nullptr, m_t);
    if (empty())
    {
      m_h = new_node;
    }
    else
    {
      m_t->next_ = new_node;
    }
    m_t = new_node;
    m_s++;
  }

  template<class T>
  void List<T>::push_front(const T& d)
  {
    detail::Node<T>* new_node = new detail::Node<T>(d, m_h, nullptr);
    if (empty())
    {
      m_t = new_node;
    }
    else
    {
      m_h->prev_ = new_node;
    }
    m_h = new_node;
    m_s++;
  }

  template<class T>
  void List<T>::push_back(T&& d)
  {
    detail::Node<T>* new_node = new detail::Node<T>(std::forward<T>(d), nullptr, m_t);
    if (empty())
    {
      m_h = new_node;
    }
    else
    {
      m_t->next_ = new_node;
    }
    m_t = new_node;
    m_s++;
  }

  template<class T>
  void List<T>::push_front(T&& d)
  {
    detail::Node<T>* new_node = new detail::Node<T>(std::forward<T>(d), m_h, nullptr);
    if (empty())
    {
      m_t = new_node;
    }
    else
    {
      m_h->prev_ = new_node;
    }
    m_h = new_node;
    m_s++;
  }

  template<class T>
  List<T>::List(const List<T>& l) :
    m_h(nullptr),
    m_t(nullptr),
    m_s(0)
  {
    detail::Node<T>* nod_ = l.m_h;
    while (nod_ != nullptr)
    {
      push_back(nod_->val_);
      nod_ = nod_->next_;
    }
  }

  template<class T>
  List<T>& List<T>::operator=(const List<T>& l)
  {
    if (this != &l)
    {
      List<T> temp(l);
      swap(temp);
    }
    return *this;
  }

  template<class T>
  List<T>::List(List<T>&& l) noexcept :
    m_h(std::exchange(l.m_h, nullptr)),
    m_t(std::exchange(l.m_t, nullptr)),
    m_s(std::exchange(l.m_s, 0))
  {}

  template<class T>
  List<T>& List<T>::operator=(List<T>&& l) noexcept
  {
    swap(l);
    return *this;
  }

  template<class T>
  List<T>::List(size_t s, const T& init) :
    m_h(nullptr),
    m_t(nullptr),
    m_s(0)
  {
    for (size_t i_ = 0; i_ < s; ++i_)
    {
      push_back(init);
    }
  }

  template<class T>
  LIter<T> List<T>::begin() noexcept
  {
    return LIter<T>(m_h);
  }

  template<class T>
  LIter<T> List<T>::end() noexcept
  {
    return LIter<T>(nullptr);
  }

  template<class T>
  LIter<T>& LIter<T>::operator++()
  {
    if (m_cur)
    {
      m_cur = m_cur->next_;
    }
    return *this;
  }

  template<class T>
  LIter<T> LIter<T>::operator++(int)
  {
    LIter<T> d_ = *this;
    ++(*this);
    return d_;
  }

  template<class T>
  LIter<T> LIter<T>::operator--(int)
  {
    LIter<T> d_ = *this;
    --(*this);
    return d_;
  }

  template<class T>
  LIter<T>& LIter<T>::operator--()
  {
    if (m_cur)
    {
      m_cur = m_cur->prev_;
    }
    return *this;
  }

  template<class T>
  T& LIter<T>::operator*()
  {
    return m_cur->val_;
  }

  template<class T>
  T* LIter<T>::operator->()
  {
    return &(m_cur->val_);
  }

  template<class T>
  bool LIter<T>::operator==(const LIter<T>& i) const
  {
    return m_cur == i.m_cur;
  }

  template<class T>
  bool LIter<T>::operator!=(const LIter<T>& i) const
  {
    return m_cur != i.m_cur;
  }

  template<class T>
  bool LCIter<T>::operator==(const LCIter<T>& i) const
  {
    return m_cur == i.m_cur;
  }

  template<class T>
  bool LCIter<T>::operator!=(const LCIter<T>& i) const
  {
    return m_cur != i.m_cur;
  }

  template<class T>
  const T& LCIter<T>::operator*() const
  {
    return m_cur->val_;
  }

  template<class T>
  const T* LCIter<T>::operator->() const
  {
    return std::addressof(m_cur->val_);
  }

  template<class T>
  LCIter<T>& LCIter<T>::operator++()
  {
    if (m_cur)
    {
      m_cur = m_cur->next_;
    }
    return *this;
  }

  template<class T>
  LCIter<T>& LCIter<T>::operator--()
  {
    if (m_cur)
    {
      m_cur = m_cur->prev_;
    }
    return *this;
  }

  template<class T>
  LCIter<T> List<T>::begin() const noexcept
  {
    return LCIter<T>(m_h);
  }

  template<class T>
  LCIter<T> List<T>::end() const noexcept
  {
    return LCIter<T>(nullptr);
  }
};

#endif
