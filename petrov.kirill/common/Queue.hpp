namespace petrov {
  template<class T>
  class Queue
  {
    public:
      Queue();
      Queue(Queue&& a);
      Queue(const Queue& a);
      ~Queue();
      void push(T rhs);
      push(const T& val);
      push(T&& value);
      void pop();
      T& front();
      T& back();
      bool empty();
      size_t size();
      T drop();
    private:
      petrov::List<T> dat;
  }
}
