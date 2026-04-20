template<class T>
class Queue
{
  public:
    void push(T rhs);
    push(const T& val);
    push(T&& value);
    void pop();
    T* front();
    T* back();
    bool empty();
    size_t size();
    T drop();
}
