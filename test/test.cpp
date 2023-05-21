#include <gtest/gtest.h>
#include <object_mother.hpp>

TEST(ctor, empty)
{
  struct Ret{
    Ret() = default;
  };
  
  struct Foo : ObjectMother<Foo, Ret>
  {
  } foo;

  Ret r = foo.get();
}


TEST(ctor, single_int_arg)
{
  struct Ret{
    int val;
    Ret( int i ):val(i){}
  };

  auto Foo = []()
  {
    struct Foo_ : ObjectMother<Foo_, Ret, int>
    {
    } ret;

    std::get<int>(ret.arg) = 2;
    
    return ret;
  };


  auto sut = Foo();

  {
    Ret r = sut.get();
    EXPECT_EQ(r.val, 2);
  }

  {
    EXPECT_EQ(sut.clone().get().val, 2);

  }
  
  {
    Ret r = sut.w(5).get();
    EXPECT_EQ(r.val, 5);
  }
  
}


