#ifndef TEST_FUNC_RUNS_H
#define TEST_FUNC_RUNS_H
#include "city.hh"
#include "core/logic.hh"

void init_screen(std::shared_ptr<Interface::ICity>);
void addActors(std::shared_ptr<Interface::ICity>);
void read_given_data(std::shared_ptr<CourseSide::Logic>);

#endif // TEST_FUNC_RUNS_H
