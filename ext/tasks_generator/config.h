#pragma once

#include "theme.h"
#include "types.h"

namespace tasks_generator {

struct config_t {
  size_t life_time;
  double mutation_chance;
  size_t population_size;

  size_t tasks;

  std::vector<theme_t> themes;

  config_t(config_t const &cnf) :
      life_time(cnf.life_time),
      mutation_chance(cnf.mutation_chance),
      population_size(cnf.population_size),
      tasks(cnf.tasks),
      themes(cnf.themes) {
  }

  explicit config_t(size_t tasks = 0) :
      life_time(1000),
      mutation_chance(0.05),
      population_size(1000),
      tasks(tasks),
      themes() {
  }

  config_t &operator = (config_t const &cnf) {
    life_time = cnf.life_time;
    mutation_chance = cnf.mutation_chance;
    population_size = cnf.population_size;
    tasks = cnf.tasks;
    themes = cnf.themes;
    return *this;
  }
};

}
