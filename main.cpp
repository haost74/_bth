
#include <iostream>
using std::cout;
#include <string>
#include <cstring>
using std::string;
#include "boost/filesystem.hpp"
#include "boost/regex.hpp"
#include "boost/thread.hpp"

#include <boost/type_index.hpp>

using boost::thread;

template<class T>
void print(T obj)
{
    cout << boost::typeindex::type_id_with_cvr<std::remove_pointer_t<decltype(obj)>>().pretty_name() << '\n';
    cout << boost::typeindex::type_id_with_cvr<std::remove_pointer_t<T>>().pretty_name() << '\n';
}

class str
{
   char* rft = nullptr;
   size_t size = 3;
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
    
  const size_t length() const { return size; }
   const char* get() const { return rft;}

   int replace_all(str& s, const str& from, const str& to)
   {
     auto d = s.get();

     int i = 0;
     for(; i < s.length(); ++i){
       auto n = d[i];
       cout << n << '\n';
     }

     return 0;
   }

    str& operator=(const string& s)
    {
        delete[] rft;
        
        string sd(s);
        sd += std::string(1, '\0');


         if(sd.length() >= capacity)
         {
            capacity = sd.length() + sd.length()/3;
         }

        rft = new char[capacity];

        int i = 0;
        for(; i < sd.length(); ++i)
        {
            rft[i] = s[i];
        }

        size = sd.length();
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const str& s)
{
  return out << s.get();
}

int main(int argc, char* argv[])
{
    str s = "hello, world!";
    str & rf = s;
    rf.replace_all(rf, "", "");

    return 0;
}