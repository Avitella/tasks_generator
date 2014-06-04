#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cassert>
#include <cstdlib>

#include "function.h"
#include "question.h"

namespace tasks_generator {

population_t generate_population(config_t const &config, std::vector<question_t> const &questions) {

  std::unordered_map<theme_id_t, std::vector<question_t>> all_questions;
  for (question_t const &question : questions)
    all_questions[question.get_theme_id()].push_back(question);
  for (std::pair<theme_id_t const, std::vector<question_t>> &q : all_questions)
    std::sort(q.second.begin(), q.second.end(), question_t::difficulty_cmp);

  population_t population(config.population_size);

  srand((unsigned int)time(0));

  for (individual_t &individual : population) {
    individual = individual_t(config.tasks, task_t(config.themes.size()));

    for (task_t &task : individual) {
      task = task_t(config.themes.size());

      std::unordered_set<question_id_t> used;

      for (size_t i = 0; i < task.size(); ++i) {
        std::vector<question_t> const &candidates = all_questions[config.themes[i].get_theme_id()];

        std::vector<question_t>::const_iterator lower = std::lower_bound(
          candidates.begin(),
          candidates.end(),
          config.themes[i].get_difficulty_min(),
          question_t::difficulty_size_t_cmp
        );

        size_t unused_count = 0;
        std::vector<question_t>::const_iterator it = lower;
        while (it != candidates.end() && it->get_difficulty() <= config.themes[i].get_difficulty_max()) {
          if (used.find(it->get_question_id()) == used.end())
            ++unused_count;
          ++it;
        }

        if (unused_count == 0)
          throw std::logic_error("hasn't questions for generate test");

        size_t pos = rand() % unused_count;

        it = lower;
        while (pos > 0 || used.find(it->get_question_id()) != used.end()) {
          if (used.find(it->get_question_id()) == used.end())
            --pos;
          ++it;
        }

        task[i] = *it;
        used.insert(it->get_question_id());
      }
    }
  }

  return population;
}

static double fitness(individual_t const &individual) {
  double s = 0, sqrs = 0;
  for (task_t const &task : individual) {
    double avg = 0;
    for (question_t const &question : task)
      avg += question.get_difficulty();
    avg /= task.size();
    s += avg;
    sqrs += avg * avg;
  }
  double d = (sqrs - s * s / individual.size()) / individual.size();
  double metric_one = (d > 0 ? 1.0 / d + 1.0 : 2);

  std::unordered_set<size_t> uniqs;
  for (task_t const &task : individual)
    for (question_t const &question : task)
      uniqs.insert(question.get_question_id());

  return metric_one * uniqs.size(); // FIXME: add diff metric
}

static individual_t crossover(individual_t const &a, individual_t const &b) {
  // FIXME: change this crossover
  assert(a.size() == b.size());
  individual_t res;
  size_t to = rand() % a.size();
  for (size_t i = 0; i < to; ++i)
    res.push_back(a[i]);
  for (size_t i = to; i < b.size(); ++i)
    res.push_back(b[i]);
  return res;
}

static void sort_by_fitness(population_t &population) {
  std::vector<std::pair<double, size_t>> buf(population.size());
  for (size_t i = 0; i < population.size(); ++i) {
    buf[i].first = fitness(population[i]);
    buf[i].second = i;
  }
  std::sort(buf.begin(), buf.end());
  for (size_t i = 0; i < population.size(); ++i)
    std::swap(population[i], population[buf[i].second]);
}

individual_t best(population_t &population) {
  assert(!population.empty());
  sort_by_fitness(population);
  return population.front();
}

void selection(config_t const &config, population_t &population) {
  // FIXME: make selection better
  sort_by_fitness(population);
  population.resize(config.population_size);
}

void recombination(config_t const &config, population_t &population) {
  if (population.empty())
    throw std::logic_error("population is empty");
  std::vector<individual_t> newbies;
  for (size_t i = 0; i < population.size(); ++i) {
    size_t pos = i + rand() % (population.size() - i);
    std::swap(population[i], population[pos]);
  }
  for (size_t i = 0; i < population.size(); i += 2) {
    newbies.push_back(crossover(population[i], population[i + 1]));
  }
  for (size_t i = 0; i < newbies.size(); ++i)
    population.emplace_back(std::move(newbies[i]));
}

void mutation(config_t const &, population_t &) {
}

}
