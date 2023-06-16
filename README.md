# object_mother
Get more readable tests by creating objects in a way that shows what's important.
A good introduction to the Object Mother pattern is *Working Effectively with Unit Tests* by *Jay Fields* (available on Leanpub and elsewhere).


## Example test

Following J.Fields, namespace A:: is used for test classes.

Let's assume that we wish to do some tests on the class `Task` that has a title, can be complete (or not) and a priority (integer). 
<code>
class Task{
  public:
    Task(std::string title, bool completed, int priority);
};
</code>

...

## Prepare A::Task "manually"
...

## Perpare A::Task with this library
If all constructor arguments are of different types things are really simple:
...


## If all constructor arguments have different types
A file has a size (integer), name (std::string) 


