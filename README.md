# state-machine-light
Our intention is to reflect UML statechart notation as directly as possible into the code, like as

![UML statechart, example](./test/4-states/statecharts.png)

```cpp
struct Start {
    using Transition = OneOf<Start, Idle>;
};

struct Idle {
    using Transition = OneOf<Start, Showing, Idle>;

    std::uint32_t request_id;
};

struct Showing {
    using Transition = OneOf<Showing, Stop>;

    std::uint32_t duration;
    std::string text;
};

struct Stop {
    using Transition = OneOf<Start>;

    std::uint32_t error_code;
    double  result;
};

using StateType = OneOf<Start, Idle, Showing, Stop>;
```

## Further informations
* [fsmpp2](https://github.com/lukaszgemborowski/fsmpp2) by Łukasz Gemborowski
* [Finite State Machine with `std::variant`](https://www.cppstories.com/2023/finite-state-machines-variant-cpp) by Bartlomiej Filipek
* [Space Game: A `std::variant`-Based State Machine by Example](https://www.cppstories.com/2019/06/fsm-variant-game/) by Nikolai Wuttke

## Related links
* [State Machine implemented by means `std::variant`](https://github.com/nikolaAV/Modern-Cpp/tree/master/variant/state_machine)

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Microsoft (R) C/C++ Compiler 19.14 
