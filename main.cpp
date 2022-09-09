
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

int main(int argc, char* argv[])
{
    str s = "hello, world!";
    str & rf = s;
    rf.replace_all("", "8");
    return 0;
}