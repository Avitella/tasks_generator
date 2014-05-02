#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Object.hpp"

#include "config.h"
#include "generator.h"
#include "question.h"
#include "theme.h"

using namespace tasks_generator;

template<>
question_t from_ruby<question_t>(Rice::Object obj) {
  size_t qid = from_ruby<size_t>(obj.call("question_id"));
  size_t tid = from_ruby<size_t>(obj.call("theme_id"));
  size_t d = from_ruby<size_t>(obj.call("difficulty"));

  return question_t(qid, tid, d);
}

template<>
Rice::Object to_ruby(question_t const &q) {
  return Rice::Data_Object<question_t>(new question_t(q));
}

template<>
std::vector<question_t> from_ruby<std::vector<question_t>>(Rice::Object obj) {
  Rice::Array arr(obj);

  std::vector<question_t> res;
  res.reserve(arr.size());

  for (Rice::Object o : arr)
    res.push_back(from_ruby<question_t>(o));

  return res;
}

template<>
Rice::Object to_ruby(std::vector<question_t> const &questions) {
  Rice::Array arr;
  for (question_t const &q : questions)
    arr.push(to_ruby(q));
  return arr;
}

template<>
theme_t from_ruby<theme_t>(Rice::Object obj) {
  size_t id = from_ruby<size_t>(obj.call("theme_id"));
  size_t dmin = from_ruby<size_t>(obj.call("difficulty_min"));
  size_t dmax = from_ruby<size_t>(obj.call("difficulty_max"));

  return theme_t(id, dmin, dmax);
}

template<>
Rice::Object to_ruby<theme_t>(theme_t const &th) {
  return Rice::Data_Object<theme_t>(new theme_t(th)); 
}

template<>
std::vector<theme_t> from_ruby<std::vector<theme_t>>(Rice::Object obj) {
  Rice::Array arr(obj);

  std::vector<theme_t> themes;
  themes.reserve(arr.size());

  for (Rice::Object obj : arr)
    themes.push_back(from_ruby<theme_t>(obj));

  return themes;
}

void set_life_time(Rice::Object obj, size_t life_time) {
  Rice::Data_Object<config_t>(obj)->life_time = life_time;
}

size_t get_life_time(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->life_time; 
}

void set_mutation_chance(Rice::Object obj, double mutation_chance) {
  Rice::Data_Object<config_t>(obj)->mutation_chance = mutation_chance;
}

double get_mutation_chance(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->mutation_chance;
}

void set_population_size(Rice::Object obj, size_t population_size) {
  Rice::Data_Object<config_t>(obj)->population_size = population_size;
}

size_t get_population_size(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->population_size;
}

void set_tasks(Rice::Object obj, size_t tasks) {
  Rice::Data_Object<config_t>(obj)->tasks = tasks;
}

size_t get_tasks(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->tasks;
}

void set_themes(Rice::Object obj, Rice::Array themes) {
  std::vector<theme_t> th = from_ruby<std::vector<theme_t>>(themes);
  Rice::Data_Object<config_t>(obj)->themes = std::move(th);
}

Rice::Array get_themes(Rice::Object obj) {
  std::vector<theme_t> const &themes = Rice::Data_Object<config_t>(obj)->themes;

  Rice::Array arr;
  for (theme_t const &t : themes)
    arr.push(to_ruby<theme_t>(t));

  return arr;
}

template<>
config_t from_ruby<config_t>(Rice::Object obj) {
  config_t result;
  
  result.life_time = from_ruby<size_t>(obj.call("life_time"));
  result.mutation_chance = from_ruby<double>(obj.call("mutation_chance"));
  result.population_size = from_ruby<size_t>(obj.call("population_size"));
  result.tasks = from_ruby<size_t>(obj.call("tasks"));
  result.themes = from_ruby<std::vector<theme_t>>(obj.call("themes"));

  return result;
}

template<>
Rice::Object to_ruby<config_t>(config_t const &cnf) {
  return Rice::Data_Object<config_t>(new config_t(cnf));
}

template<>
generator_t from_ruby<generator_t>(Rice::Object obj) {
  config_t config = from_ruby<config_t>(obj.call("config"));
  std::vector<question_t> questions = from_ruby<std::vector<question_t>>(obj.call("questions"));

  return generator_t(std::move(config), std::move(questions));
}

template<>
Rice::Object to_ruby(generator_t const &t) {
  return Rice::Data_Object<generator_t>(new generator_t(t));
}

template<>
Rice::Object to_ruby<generator_t::answer_t>(generator_t::answer_t const &ans) {
  Rice::Array result;
  for (std::vector<question_t> const &arr : ans) {
    Rice::Array buffer;
    for (question_t const &q : arr)
      buffer.push(to_ruby<question_t>(q));
    result.push(buffer);
  }
  return result;
}

extern "C" void Init_tasks_generator() {
  Rice::Module rb_mTasksGenerator = Rice::define_module("TasksGenerator");

  Rice::Data_Type<config_t> rb_cConfig = Rice::define_class_under<config_t>(rb_mTasksGenerator, "Config")
    .define_constructor(Rice::Constructor<config_t, size_t>(), Rice::Arg("tasks") = 0)
    .define_method("life_time=", &set_life_time)
    .define_method("mutation_chance=", &set_mutation_chance)
    .define_method("population_size=", &set_population_size)
    .define_method("tasks=", &set_tasks)
    .define_method("life_time", &get_life_time)
    .define_method("mutation_chance", &get_mutation_chance)
    .define_method("population_size", &get_population_size)
    .define_method("tasks", &get_tasks)
    .define_method("themes", &get_themes)
    .define_method("themes=", &set_themes);

  Rice::Data_Type<theme_t> rb_cTheme = Rice::define_class_under<theme_t>(rb_mTasksGenerator, "Theme")
    .define_constructor(Rice::Constructor<theme_t, size_t, size_t, size_t>(),
      (Rice::Arg("id"), Rice::Arg("dmin"), Rice::Arg("dmax")))
    .define_method("theme_id", &theme_t::get_theme_id)
    .define_method("difficulty_min", &theme_t::get_difficulty_min)
    .define_method("difficulty_max", &theme_t::get_difficulty_max);

  Rice::Data_Type<question_t> rb_cQuestion = Rice::define_class_under<question_t>(rb_mTasksGenerator, "Question")
    .define_constructor(Rice::Constructor<question_t, size_t, size_t, size_t>(),
      (Rice::Arg("id"), Rice::Arg("tid"), Rice::Arg("difficulty")))
    .define_method("question_id", &question_t::get_question_id)
    .define_method("theme_id", &question_t::get_theme_id)
    .define_method("difficulty", &question_t::get_difficulty);

  Rice::Data_Type<generator_t> rb_cGenerator = Rice::define_class_under<generator_t>(rb_mTasksGenerator, "Generator")
    .define_constructor(Rice::Constructor<generator_t, config_t, std::vector<question_t>>(),
      (Rice::Arg("cnf"), Rice::Arg("questions")))
    .define_method("config", &generator_t::get_config)
    .define_method("questions", &generator_t::get_questions)
    .define_method("generate", &generator_t::generate);
}
