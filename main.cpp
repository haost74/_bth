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
 #include "src/alexs.hpp"

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

namespace nm
{

  template<class T,
           class Traits = std::char_traits<T>,
           class Allocator = std::allocator<T>>
  class b_string{
    public:
    T *data;
    size_t size;
    union{
      size_t capacity;
      enum{SZ = (sizeof(data) + 2*sizeof(size_t) + 31)/32};
      T small_str[SZ];
    } sso;

  };
}

struct ci_char_traits : public std::char_traits<char>{
   static char to_upper(char ch){
    return std::toupper((unsigned char) ch);
   }

   static bool eq(char c1, char c2){
    return to_upper(c1) == to_upper(c2);
   }
};

#pragma endregion

#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)
#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __LINE__)
#endif

namespace tmp
{
  enum class ScopeGuardOnExit {};
  template<class Fun>
  class ScopeGuard
  {
    Fun fn;
    public:
    ScopeGuard(Fun &fn):fn(fn){}
    ScopeGuard(Fun &&fn):fn(std::move(fn)){}
    ~ScopeGuard(){fn();}
  };

  template <typename Fun>
	auto operator+(ScopeGuardOnExit, Fun &&fn)
	{
		return ScopeGuard<Fun>(std::forward<Fun>(fn));
	}

}

#define SCOPE_EXIT auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = ::tmp::ScopeGuardOnExit() + [&]() noexcept


int main(int argc, char* argv[])
{
  
// copy_faile();

{
 SCOPE_EXIT{ cout << 1024 << '\n'; };
}
 
    return 0;
}