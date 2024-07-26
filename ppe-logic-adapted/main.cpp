/*
   g++ main.cpp -std=c++14 -o exe -g
   g++ main.cpp -std=c++14 -Wextra -Wall -pedantic-errors -o exe
   g++ main.cpp -std=c++17 -Wextra -Wall -pedantic-errors -o exe
   core dump file --> /var/lib/apport/coredump (before, $ ulimit -c unlimited)
*/

#include <cassert>
#include <variant>

//#include "implicite_spec/sm_games_shown.hpp"
#include "explicit_spec/sm_games_shown.hpp"
#include "tfsml/iterate.hpp"
#include "tfsml/overloaded.hpp"

struct OutputDataEx : OutputData 
{
    OutputDataEx& operator=(GamesShownState& games_shown_state)
    {
        std::visit(
            tfsml::cpp14::make_overloaded(
                 [&](initial& s)        { }
                ,[&](CarOn_FirstP& s)   { feature_state = s.feature_state; }
                ,[&](CarOn_noP& s)      { feature_state = s.feature_state; }
                ,[&](CarOn_P& s)        { feature_state = s.feature_state; }
                ,[&](CarOff_P& s)       { feature_state = s.feature_state; }
                ,[&](CarOff_noP& s)     { feature_state = s.feature_state; }
            )
            ,games_shown_state
        );

        return *this;
    }
};

void test_initial()
{
    OutputDataEx expected{};
    GamesShownState games_shown_state{};
    assert(std::holds_alternative<initial>(games_shown_state));

  
    {
        auto in = InputData{ true, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_FirstP>(modified));
        assert(std::get<CarOn_FirstP>(modified).feature_state==EFeatureState::On);
        assert(expected.feature_state==EFeatureState::On);
    }

    {
        auto in = InputData{ true, false };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_noP>(modified));
        assert(std::get<CarOn_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ false, false };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOff_noP>(modified));
        assert(std::get<CarOff_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ false, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOff_P>(modified));
        assert(std::get<CarOff_P>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }
}

void test_CarOn_FirstP()
{
    OutputDataEx expected{};
    GamesShownState games_shown_state{CarOn_FirstP{}};
    assert(std::holds_alternative<CarOn_FirstP>(games_shown_state));
    assert(std::get<CarOn_FirstP>(games_shown_state).feature_state==EFeatureState::Off);
    std::get<CarOn_FirstP>(games_shown_state).feature_state = EFeatureState::On;
    expected = games_shown_state;
    assert(expected.feature_state==EFeatureState::On);

    {
        auto in = InputData{ false, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOff_P>(modified));
        assert(std::get<CarOff_P>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ true, false };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_noP>(modified));
        assert(std::get<CarOn_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ true, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_FirstP>(modified));
        assert(std::get<CarOn_FirstP>(modified).feature_state==EFeatureState::On);
        assert(expected.feature_state==EFeatureState::On);
    }
}

void test_CarOn_noP()
{
    OutputDataEx expected{};
    GamesShownState games_shown_state{CarOn_noP{}};
    assert(std::holds_alternative<CarOn_noP>(games_shown_state));
    assert(std::get<CarOn_noP>(games_shown_state).feature_state==EFeatureState::Off);
    expected = games_shown_state;
    assert(expected.feature_state==EFeatureState::Off);

    {
        auto in = InputData{ false, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOff_noP>(modified));
        assert(std::get<CarOff_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ true, true };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_P>(modified));
        assert(std::get<CarOn_P>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ true, false };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOn_noP>(modified));
        assert(std::get<CarOn_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }

    {
        auto in = InputData{ false, false };
        auto modified = tfsml::iterate(in, games_shown_state);
        expected = modified;
        assert(std::holds_alternative<CarOff_noP>(modified));
        assert(std::get<CarOff_noP>(modified).feature_state==EFeatureState::Off);
        assert(expected.feature_state==EFeatureState::Off);
    }
}

void test_CarOn_P()
{

}

void test_CarOff_P()
{

}

void test_CarOff_noP()
{

}

int main()
{
    test_initial();
    test_CarOn_FirstP();

    test_CarOn_noP();

    test_CarOn_P();
    test_CarOff_P();
    test_CarOff_noP();

    return 0;
}
