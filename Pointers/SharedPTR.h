// The simplest realization of Shared Pointer

#pragma once

#ifndef SHARED_PTR // todo remove
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

    SharedPTR(nullptr_t nptr)
      : m_ptr(nullptr), m_counter(new int(0))
      {
      }

    explicit SharedPTR(T* ptr)
      : m_ptr(ptr), m_counter(new int(1))
      {
      }

    SharedPTR(const SharedPTR& ptr)
      : m_ptr(ptr.m_ptr), m_counter(ptr.m_counter)
      { 
      if (*m_counter > 0)
        ++*m_counter;
      }

    SharedPTR(SharedPTR&& ptr) noexcept
      : m_ptr(ptr.m_ptr), m_counter(ptr.m_counter)
      {
      ptr.m_ptr = nullptr;
      ptr.m_counter = new int(0);
      }

    ~SharedPTR()
      {

        if (*m_counter > 0)
          {
          --*m_counter;
          }

        if (*m_counter < 1)
          {
          delete m_ptr;
          m_ptr = nullptr;
          }

      }

    SharedPTR<T>& operator=(SharedPTR&& ptr) noexcept
      {
      m_ptr = ptr.m_ptr;
      m_counter = ptr.m_counter;
      ptr.m_ptr = nullptr;
      ptr.m_counter = new int(0);
      return *this;
      }

    SharedPTR<T>& operator=(const SharedPTR& ptr)
      {
      m_ptr = ptr.m_ptr;
      m_counter = ptr.m_counter;
      if (*m_counter > 0) 
        { 
        ++*m_counter;
        }
      return *this;
      }

    T& operator*()
      {
      return *m_ptr;
      }

    T* operator->()
      {
      return m_ptr;
      }

    operator bool() const
      {
      return m_ptr != nullptr;
      }

    const int use_count() const
      {
      return *m_counter;
      }

    T* get() const
      {
      return m_ptr;
      }

    void reset()
      {
      m_ptr = nullptr;
      if (m_counter > 0) // todo test this
        {
        --* m_counter;
        }
      m_counter = new int(0);
      }

    void reset(T* ptr)
      {
      m_ptr = ptr;
      if (m_counter > 0) // todo test this
        {
        --* m_counter;
        }
      if (ptr != nullptr)
        {
        m_counter = new int(1);
        return;
        }
      m_counter = new int(0);
      }

  };

#endif // !SHARED_PTR