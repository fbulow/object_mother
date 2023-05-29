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


TEST(ctor, multiple_int_arg)
{
  struct Ret{
    int val;
    Ret( int i, int j ):val(10*i+j){}
  };

  auto Foo = []()
  {
    struct Foo_ : ObjectMother<Foo_, Ret, int, int>
    {
      auto wFirst(int first)
      {
	return w<0>(first);
      }
      auto wSecond(int first)
      {
	return w<1>(first);
      }
    } ret;
    return ret.wFirst(1).wSecond(2);
  };


  auto sut = Foo();

  EXPECT_EQ(sut.get().val, 12);
  //EXPECT_EQ(sut.w(5).get().val, 52); //Should not compile since there are several int arguments
  EXPECT_EQ(sut.w<0>(5).get().val, 52);
  EXPECT_EQ(sut.w<1>(5).get().val, 15);

  EXPECT_EQ(sut.wFirst(5).get().val, 52);//Named argument

}

TEST(ctor, multiple_int_and_something_that_not_an_int)
{
  struct Ret{
    int val;
    Ret( int i, int j, bool addFive):val(10*i+j + (addFive?5:0)){}
  };

  auto Foo = []()
  {
    struct Foo_ : ObjectMother<Foo_, Ret, int, int, bool>
    {
      auto wFirst(int first)
      {
	return w<0>(first);
      }
      auto wSecond(int first)
      {
	return w<1>(first);
      }
    } ret;
    return ret.wFirst(0).wSecond(0).w(false);
  };


  auto sut = Foo();

  EXPECT_EQ(sut.w(true).get().val, 5);
  EXPECT_EQ(sut.w(false).get().val, 0);

}

TEST(automatic_conversion, get_not_needed)
{
  struct Ret{
    Ret() = default;
  };

  struct Foo : ObjectMother<Foo, Ret>
  {
  } foo;

  auto f = [](Ret){};
  f(foo); // should compile because foo is automatically converted to Ret;
}

TEST(ctor, default_arguments_with_form_tuple)
{
  struct Ret{
    int val;
    Ret( int i, int j ):val(10*i+j){}
  };

  auto Foo = []()
  {
    struct Foo_ : ObjectMother<Foo_, Ret, int, int>
    {
      auto wFirst(int first)
      {
	return w<0>(first);
      }
      auto wSecond(int first)
      {
	return w<1>(first);
      }
    };
    return Foo_::defaultValues(1,2);
  };

  auto sut = Foo();

  EXPECT_EQ(sut.get().val, 12);
  EXPECT_EQ(sut.w<0>(5).get().val, 52);
  EXPECT_EQ(sut.w<1>(5).get().val, 15);

  EXPECT_EQ(sut.wFirst(5).get().val, 52);//Named argument
}
