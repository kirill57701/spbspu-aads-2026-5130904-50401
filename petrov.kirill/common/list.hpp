#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <utility>

namespace detail
{
  template< class T >
  struct Node
  {
    T val_;
    Node< T >* next_;
    Node< T >* prev_;
    Node(const T& v, Node< T >* n = nullptr, Node< T >* p = nullptr);
    Node(T&& v, Node< T >* n = nullptr, Node< T >* p = nullptr);
  };

  template< class T >
  Node< T >::Node(const T& v, Node< T >* n, Node< T >* p):
    val_(v),
    next_(n),
    prev_(p)
  {}

  template< class T >
  Node< T >::Node(T&& v, Node< T >* n, Node< T >* p):
    val_(std::forward< T >(v)),
    next_(n),
    prev_(p)
  {}
};

namespace petrov
{
  template< class T >
  class LIter;

  template< class T >
  class LCIter;

  template< class T >
  class List
  {
  public:
    List();
    List(const List< T >& l);
    List(List< T >&& l) noexcept;
    List(size_t s, const T& init);
    ~List();

    List< T >& operator=(List< T >&& l) noexcept;
    List< T >& operator=(List< T > l);

    bool empty() const noexcept;
    size_t size() const noexcept;
    LIter< T > begin() noexcept;
    LIter< T > end() noexcept;
    LCIter< T > begin() const noexcept;
    LCIter< T > end() const noexcept;

    void push_back(const T& d);
    void push_back(T&& d);

    void push_front(const T& d);
    void push_front(T&& d);

    void swap(List< T >& d) noexcept;
    void pop_back();
    void pop_front();
    void clear();
  private:
    detail::Node< T >* h_;
    detail::Node< T >* t_;
    size_t s_;
  };

  template< class T >
  class LIter
  {
  public:
    LIter();
    LIter(detail::Node< T >* n);
    bool operator==(const LIter< T >& i) const;
    bool operator!=(const LIter< T >& i) const;
    T& operator*();
    LIter< T >& operator++();
    LIter< T >& operator++(int);
    LIter< T >& operator--();
    LIter< T >& operator--(int);
    T* operator->();
  private:
    friend class List< T >;
    detail::Node< T >* cur_;
  };

  template< class T >
  LIter< T >::LIter():
    cur_(nullptr)
  {}

  template< class T >
  LIter< T >::LIter(detail::Node< T >* n):
    cur_(n)
  {}

  template< class T >
  class LCIter
  {
  public:
    LCIter();
    LCIter(detail::Node< T >* n);
    bool operator==(const LCIter< T >& i) const;
    bool operator!=(const LCIter< T >& i) const;
    const T& operator*() const;
    LCIter< T >& operator++();
    LCIter< T >& operator--();
    const T* operator->() const;
  private:
    friend class List< T >;
    const detail::Node< T >* cur_;
  };

  template< class T >
  LCIter< T >::LCIter():
    cur_(nullptr)
  {}

  template< class T >
  LCIter< T >::LCIter(detail::Node< T >* n):
    cur_(n)
  {}

  template< class T >
  List< T >::List():
    h_(nullptr),
    t_(nullptr),
    s_(0)
  {}

  template< class T >
  void List< T >::clear()
  {
    if (h_ != nullptr)
    {
      while (h_->next_ != nullptr)
      {
        detail::Node< T >* promej_ = h_->next_;
        delete h_;
        h_ = promej_;
      }
      delete h_;
    }
    h_ = nullptr;
    t_ = nullptr;
    s_ = 0;
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  void List< T >::pop_front()
  {
    if (!empty())
    {
      detail::Node< T >* new_h_ = h_->next_;
      delete h_;
      h_ = new_h_;
      if (h_ == nullptr)
      {
        t_ = nullptr;
        s_ = 0;
        return;
      }
      h_->prev_ = nullptr;
      s_--;
    }
  }

  template< class T >
  void List< T >::swap(List< T >& d) noexcept
  {
    std::swap(h_, d.h_);
    std::swap(t_, d.t_);
    std::swap(s_, d.s_);
  }

  template< class T >
  void List< T >::pop_back()
  {
    if (!empty())
    {
      detail::Node< T >* new_t_ = t_->prev_;
      delete t_;
      t_ = new_t_;
      if (t_ == nullptr)
      {
        h_ = nullptr;
        s_ = 0;
        return;
      }
      t_->next_ = nullptr;
      s_--;
    }
  }

  template< class T >
  bool List< T >::empty() const noexcept
  {
    return (!s_ || h_ == nullptr);
  }

  template< class T >
  size_t List< T >::size() const noexcept
  {
    return s_;
  }

  template< class T >
  void List< T >::push_back(const T& d)
  {
    if (empty())
    {
      h_ = new detail::Node< T >(d);
      h_->next_ = nullptr;
      h_->prev_ = nullptr;
      t_ = h_;
      s_ = 1;
      return;
    }
    t_->next_ = new detail::Node< T >(d);
    t_->next_->prev_ = t_;
    t_ = t_->next_;
    t_->next_ = nullptr;
    s_++;
  }

  template< class T >
  void List< T >::push_front(const T& d)
  {
    if (empty())
    {
      h_ = new detail::Node< T >(d);
      h_->next_ = nullptr;
      h_->prev_ = nullptr;
      t_ = h_;
      s_ = 1;
      return;
    }
    h_->prev_ = new detail::Node< T >(d);
    h_->prev_->next_ = h_;
    h_ = h_->prev_;
    h_->prev_ = nullptr;
    s_++;
  }

  template< class T >
  void List< T >::push_back(T&& d)
  {
    if (empty())
    {
      h_ = new detail::Node< T >(std::forward< T >(d));
      h_->next_ = nullptr;
      h_->prev_ = nullptr;
      t_ = h_;
      s_ = 1;
      return;
    }
    t_->next_ = new detail::Node< T >(std::forward< T >(d));
    t_->next_->prev_ = t_;
    t_ = t_->next_;
    t_->next_ = nullptr;
    s_++;
  }

  template< class T >
  void List< T >::push_front(T&& d)
  {
    if (empty())
    {
      h_ = new detail::Node< T >(std::forward< T >(d));
      h_->next_ = nullptr;
      h_->prev_ = nullptr;
      t_ = h_;
      s_ = 1;
      return;
    }
    h_->prev_ = new detail::Node< T >(std::forward< T >(d));
    h_->prev_->next_ = h_;
    h_ = h_->prev_;
    h_->prev_ = nullptr;
    s_++;
  }

  template< class T >
  List< T >::List(const List< T >& l):
    h_(nullptr),
    t_(nullptr),
    s_(0)
  {
    try
    {
      detail::Node< T >* nod_ = l.h_;
      while (nod_ != nullptr)
      {
        push_back(nod_->val_);
        nod_ = nod_->next_;
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< class T >
  List< T >& List< T >::operator=(List< T > l)
  {
    swap(l);
    return *this;
  }

  template< class T >
  List< T >::List(List< T >&& l) noexcept:
    h_(std::exchange(l.h_, nullptr)),
    t_(std::exchange(l.t_, nullptr)),
    s_(std::exchange(l.s_, 0))
  {}

  template< class T >
  List< T >& List< T >::operator=(List< T >&& l) noexcept
  {
    swap(l);
    return *this;
  }

  template< class T >
  List< T >::List(size_t s, const T& init):
    h_(nullptr),
    t_(nullptr),
    s_(0)
  {
    for (size_t i_ = 0; i_ < s; ++i_)
    {
      push_back(init);
    }
  }

  template< class T >
  LIter< T > List< T >::begin() noexcept
  {
    return LIter< T >(h_);
  }

  template< class T >
  LIter< T > List< T >::end() noexcept
  {
    return LIter< T >(nullptr);
  }

  template< class T >
  LIter< T >& LIter< T >::operator++()
  {
    if (cur_ != nullptr)
    {
      cur_ = cur_->next_;
    }
    return *this;
  }

  template< class T >
  LIter< T >& LIter< T >::operator++(int)
  {
    LIter< T > d_ = *this;
    ++(*this);
    return d_;
  }

  template< class T >
  LIter< T >& LIter< T >::operator--(int)
  {
    LIter< T > d_ = *this;
    --(*this);
    return d_;
  }

  template< class T >
  LIter< T >& LIter< T >::operator--()
  {
    if (cur_ != nullptr)
    {
      cur_ = cur_->prev_;
    }
    return *this;
  }

  template< class T >
  T& LIter< T >::operator*()
  {
    return cur_->val_;
  }

  template< class T >
  T* LIter< T >::operator->()
  {
    return &(cur_->val_);
  }

  template< class T >
  bool LIter< T >::operator==(const LIter< T >& i) const
  {
    return !(cur_ != i.cur_);
  }

  template< class T >
  bool LIter< T >::operator!=(const LIter< T >& i) const
  {
    return cur_ != i.cur_;
  }

  template< class T >
  bool LCIter< T >::operator==(const LCIter< T >& i) const
  {
    return !(cur_ != i.cur_);
  }

  template< class T >
  bool LCIter< T >::operator!=(const LCIter< T >& i) const
  {
    return cur_ != i.cur_;
  }

  template< class T >
  const T& LCIter< T >::operator*() const
  {
    return cur_->val_;
  }

  template< class T >
  const T* LCIter< T >::operator->() const
  {
    return std::addressof(cur_->val_);
  }

  template< class T >
  LCIter< T >& LCIter< T >::operator++()
  {
    if (cur_ != nullptr)
    {
      cur_ = cur_->next_;
    }
    return *this;
  }

  template< class T >
  LCIter< T >& LCIter< T >::operator--()
  {
    if (cur_ != nullptr)
    {
      cur_ = cur_->prev_;
    }
    return *this;
  }

  template< class T >
  LCIter< T > List< T >::begin() const noexcept
  {
    return LCIter< T >(h_);
  }

  template< class T >
  LCIter< T > List< T >::end() const noexcept
  {
    return LCIter< T >(nullptr);
  }
};

#endif
