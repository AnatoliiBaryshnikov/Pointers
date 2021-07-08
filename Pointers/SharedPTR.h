// The simplest realisation of Shared Pointer

#pragma once

#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPTR
  {
    private:
    T* m_ptr;
    int* m_counter;

    public:
    SharedPTR()
      : m_ptr(nullptr), m_counter(new int(0))
      {
      }

    SharedPTR(T* ptr)
      : m_ptr(ptr), m_counter(new int(1))
      {
      }

    SharedPTR(const SharedPTR& ptr)
      : m_ptr(ptr.m_ptr), m_counter(ptr.m_counter)
      { 
      ++ *m_counter;
      }

    ~SharedPTR()
      {
      -- *m_counter;
      if (*m_counter < 1)
        {
        delete m_ptr;
        }
      }

    T& operator*()
      {
      return *m_ptr;
      }

    T* operator->()
      {
      return m_ptr;
      }

    const int useCount() const
      {
      return *m_counter;
      }

    T* get() const
      {
      return m_ptr;
      }

  };

#endif // !SHARED_PTR