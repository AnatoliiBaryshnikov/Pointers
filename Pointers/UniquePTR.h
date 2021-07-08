// The simplest realisation of Unique Pointer

#pragma once

#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePTR
  {
    private:
    T* m_ptr;

    public:
    UniquePTR()
      : m_ptr(nullptr)
      {
      }

    explicit UniquePTR(T* ptr)
      : m_ptr(ptr)
      {
      }

    UniquePTR(const UniquePTR& ptr) = delete;

    UniquePTR(UniquePTR&& ptr)
      : m_ptr(ptr.m_ptr)
      {
      ptr.m_ptr = nullptr;
      }

    ~UniquePTR()
      {
      delete m_ptr;
      }

    UniquePTR<T>& operator=(const UniquePTR& ptr) = delete;

    UniquePTR<T>& operator=(UniquePTR&& ptr) noexcept
      {
      m_ptr = ptr.m_ptr;
      ptr.m_ptr = nullptr;
      return *this;
      }

    T& operator*() const
      {
      return *m_ptr;
      }

    T* operator->() const
      {
      return m_ptr;
      }

    operator bool() const
      {
      return m_ptr != nullptr;
      }

    void reset(T* ptr)
      {
      delete m_ptr;
      m_ptr = nullptr;
      m_ptr = ptr;
      }

    T* release()
      {
      T* tmp_ptr = m_ptr;
      m_ptr = nullptr;
      return tmp_ptr;
      }

  };

#endif // !UNIQUE_PTR
