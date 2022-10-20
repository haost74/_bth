#include <iostream>
using std::cout;
#include <string>
#include <cstring>
using std::string;
#include "boost/filesystem.hpp"
#include "boost/regex.hpp"
#include "boost/thread.hpp"

#include <boost/type_index.hpp>
#include <boost/coroutine2/all.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
using boost::thread;
namespace bf = boost::filesystem;
// #include "src/scopr.hpp"
 #include "alexs.hpp"

#pragma region 
template<class T>
void print(T obj)
{
    cout << boost::typeindex::type_id_with_cvr<std::remove_pointer_t<decltype(obj)>>().pretty_name() << '\n';
    cout << boost::typeindex::type_id_with_cvr<std::remove_pointer_t<T>>().pretty_name() << '\n';
}

class str
{
  #pragma region 
   char* rft = nullptr;
   size_t size = 0;
   size_t capacity = 5;
   public:
   
   str()
   {
     rft = new char[capacity];
   }

   str(const str& s)
   {
     string sd(s.get());
     *this = sd;
   }

  str(const char* s)
   {
      string sd(s);
     *this = sd;
   }
   str(const string s)
   {
     *this = s;
   }

   ~str()
   {
     delete[] rft;
   }
    
  const size_t length() const { return size != 0 ? size - 1 : size; }
  const char* get() const { return rft;}
  #pragma endregion

   int replace_all(const str& from, const str& to)
   {

    if(length() == 0 || from.length() == 0 || to.length() == 0) return 0;    

     int i = 0;
     for(; i < length(); ++i){
       
     }

     return 0;
   }

    str& operator=(const string& s)
    {
        if(s == "") return *this;
        
        string sd(s);
        sd += std::string(1, '\0');

         if(sd.length() >= capacity)
         {
            capacity = sd.length() + sd.length()/3 + 1;
         }

        delete[] rft;
        size = sd.length();
        rft = new char[capacity];

        int i = 0;
        for(; i < sd.length(); ++i)
        {
            rft[i] = s[i];
        }

        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const str& s)
{
  return out << s.get();
}

void print(string str){
    SetConsoleOutputCP(CP_UTF8);
    std::cout << str << '\n';
}

void print_cin(string str){
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
    std::cout << str << '\n';
}



class Mallocator {  };

struct Blk {
    void* ptr;
    size_t size;
};

 template <class P, class F>
 class FallbackAllocator : private P, private F{
  public:
    Blk  allocate(size_t n){
      Blk r = P::allocate(n);
      if(!r.ptr) r = F::allocate(n);
      return r;
    }
    void deallocate(Blk b){
      if(P::owns(b)) P::deallocate(b);
      else F::deallocate(b);
    }

    bool owns(Blk b){
      return P::owns(b) || F::owns(b);
    }
 };

 template <size_t s> 
class StackAllocator{
   char d_[s];
   char* p_;
   StackAllocator():p_(d_){}
   Blk allocate(size_t n){
    auto n1 = roundToAligned(n);
    if(n1 > (d_ + s) - p_){
      return {nullptr, 0};
    }
    Blk result = {p_, n};
    p_ += n1;
    return result;
   }

   void deallocate(Blk b){
    if(b.ptr + roundToAligned(n) == p_){
      p_ = b.ptr;
    }
   }

   bool owns(Blk b){
    return b.ptr >= d_ && b.ptr < d_ + s;
   }

   void deallocateAll(){
    p_ = d_;
   }

   size_t roundToAligned(size_t n){
    return n;
   }
};



using Loalloc = FallbackAllocator<StackAllocator<16384>,
                  Mallocator>();

template<size_t s>
class allocStack
{
     char d_[s];
     char* p_;
     size_t roundToAligned(size_t n){return n;}
  public:
      allocStack():p_(d_){}
      Blk allocate(size_t n){
        auto n1 = roundToAligned(n);
        if(n1 > (d_ + s) - p_){
          return {nullptr, 0};
        }
        Blk result = {p_, n};
        p_ += n1;
        return result;
      }
};

template<class P, class F>
class back : private P, private F
{
  public:
   Blk allocate(size_t n) { 
    Blk r = P::allocate(n); 
    if (!r.ptr) r = F::allocate(n); 
   
        return r; 
    }

    void deallocate(Blk b){
      if(owns(b)) P:deallocate(b);
      else F::deallocate(b);
    }

    bool owns(Blk b) { 
       return P::owns(b) || F::owns(b); 
    }
};

template<size_t s>
struct pn
{
  char* p_;
  char d_[s];
  Blk allocate(size_t n)
  {
    std::cout << "pn\n";
    Blk k;
    k.ptr = nullptr;

    return k;
  }

  bool owns(Blk b) {
    return d_ <= b.ptr && b.ptr < d_ + s;
  }

  void deallocate(Blk b)
  {

  }
};

struct fn
{
  Blk allocate(size_t n)
  {
    cout << "fn\n";
    Blk k;
    k.ptr = nullptr;
    return k;
  }

  void deallocate(Blk b)
  {

  }
};

int main(int argc, char* argv[])
{
   // 109.110.0.0
   // 95.68.127.255
    back<pn<16384>,fn> bk;
    bk.allocate(10);
    
   
    return 0;
}