#pragma once

#include <algorithm>
#include <vector>

#include "config.h"
#include "question.h"
#include "types.h"

namespace tasks_generator {

population_t generate_population(config_t const &config, std::vector<question_t> const &questions);

individual_t best(population_t &population);

void selection(config_t const &config, population_t &population);

void recombination(config_t const &config, population_t &population);

void mutation(config_t const &config, population_t &population);

}
