#ifndef PYTHONIC_SHARED_REF_H
#define PYTHONIC_SHARED_REF_H
#include <memory>
#ifdef _OPENMP
#include <atomic>
#endif

namespace pythonic {

#ifdef _OPENMP
    typedef std::atomic_size_t atomic_size_t;
#else
    typedef size_t atomic_size_t;
#endif

    namespace impl {
        struct no_memory{};

        template <class T>
            class shared_ref
            {
                private:
                    struct memory {
                        T ptr;
                        atomic_size_t count;
                        template<class... Types>
                            memory(Types&&... args) : ptr(args...),count(1) {}
                    } *mem;
                public:
                    shared_ref(no_memory const&) noexcept
                        : mem(nullptr)
                    {}
                    shared_ref(shared_ref<T>&& p) noexcept
                        : mem(p.mem)
                    {p.mem=nullptr;}
                    shared_ref(shared_ref<T> const& p) noexcept
                        : mem(p.mem)
                    {if(mem) acquire();}

                    template<class... Types>
                        shared_ref(Types... args) : mem(new memory(args...)) {}

                    ~shared_ref() noexcept
                    {dispose();}

                    shared_ref<T>& operator=(shared_ref<T> const & p) noexcept
                    {
                        if(mem != p.mem){
                            dispose();
                            mem=p.mem;
                            acquire();
                        }
                        return *this;
                    }
                    shared_ref<T>& operator=(shared_ref<T> && p) noexcept
                    {
                        if(mem != p.mem){
                            dispose();
                            mem=std::move(p.mem);
                            p.mem=nullptr;
                        }
                        return *this;
                    }

                    T& operator*() const noexcept
                    {return mem->ptr;}

                    T* operator->() const noexcept
                    {return &mem->ptr;}

                    bool operator!=(shared_ref<T> const & other) const {
                        return this->mem != other.mem;
                    }

                    void external() {
                        ++mem->count;
                    }

                    T* forget() {
                        T *ptr = &mem->ptr;
                        mem = nullptr;
                        return ptr;
                    }

                 private:
                    void dispose()
                    {
                        if(mem and --mem->count == 0)
                        {
                            delete mem;
                            mem = nullptr;
                        }
                    }
                    void acquire() {
                        ++mem->count;
                    }
            };

    }
}

#endif
