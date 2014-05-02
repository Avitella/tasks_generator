#include <vector>

#include "generator.h"

#include "function.h"
#include "question.h"
#include "types.h"

namespace tasks_generator {

generator_t::answer_t generator_t::generate() const {
  population_t population = generate_population(config, questions);

  for (size_t current_time = 0; current_time < config.life_time; ++current_time) {
    selection(config, population);
    recombination(config, population);
    mutation(config, population);
  }

  return best(population);
}

}
