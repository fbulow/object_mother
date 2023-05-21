#pragma once
#include <tuple>

template<class AA, class RET, class ... ARG>
struct ObjectMother
{
  using Arguments = std::tuple<ARG...>;
  Arguments arg;

  RET get() const
  {
    return std::make_from_tuple<RET>(arg);
  }

  AA clone() const
  {
    AA ret;
    ret.arg = arg;
    return ret;
  }
  
  template<class TO_SET>
  AA w(TO_SET const & newValue) const
  {
    auto ret = clone();
    std::get<TO_SET>(ret.arg) = newValue;
    return ret;
  }

  template<int INDEX, class TO_SET>
  AA w(TO_SET const & newValue) const
  {
    auto ret = clone();
    std::get<INDEX>(ret.arg) = newValue;
    return ret;
  }

  operator RET () const
  {return get();}
};
