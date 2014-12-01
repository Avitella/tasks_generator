#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Object.hpp"

#include "config.h"
#include "generator.h"
#include "question.h"
#include "topic.h"

using namespace ailab;

template<>
question_t from_ruby<question_t>(Rice::Object obj) {
  size_t qid = from_ruby<size_t>(obj.call("question_id"));
  size_t tid = from_ruby<size_t>(obj.call("topic_id"));
  size_t d = from_ruby<size_t>(obj.call("difficulty"));
  std::string t = from_ruby<std::string>(obj.call("text"));

  return question_t(qid, tid, d, t);
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
topic_t from_ruby<topic_t>(Rice::Object obj) {
  size_t id = from_ruby<size_t>(obj.call("topic_id"));
  size_t pid = from_ruby<size_t>(obj.call("parent_id"));
  std::string text = from_ruby<std::string>(obj.call("text"));

  return topic_t(id, pid, text);
}

template<>
Rice::Object to_ruby<topic_t>(topic_t const &th) {
  return Rice::Data_Object<topic_t>(new topic_t(th)); 
}

template<>
std::vector<topic_t> from_ruby<std::vector<topic_t>>(Rice::Object obj) {
  Rice::Array arr(obj);

  std::vector<topic_t> topics;
  topics.reserve(arr.size());

  for (Rice::Object obj : arr)
    topics.push_back(from_ruby<topic_t>(obj));

  return topics;
}

template<>
Rice::Object to_ruby<std::vector<size_t>>(std::vector<size_t> const &v) {
  return Rice::Data_Object<std::vector<size_t>>(new std::vector<size_t>(v));
}

template<>
std::vector<size_t> from_ruby<std::vector<size_t>>(Rice::Object obj) {
  Rice::Array arr(obj);

  std::vector<size_t> result;
  result.reserve(arr.size());

  for (Rice::Object obj : arr)
    result.push_back(from_ruby<size_t>(obj));

  return result;
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

void set_variants_count(Rice::Object obj, size_t variants_count) {
  Rice::Data_Object<config_t>(obj)->variants_count = variants_count;
}

size_t get_variants_count(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->variants_count;
}

void set_questions_count(Rice::Object obj, size_t questions_count) {
  Rice::Data_Object<config_t>(obj)->questions_count = questions_count;
}

size_t get_questions_count(Rice::Object obj) {
  return Rice::Data_Object<config_t>(obj)->questions_count;
}

void set_topics(Rice::Object obj, Rice::Array topics) {
  std::vector<size_t> th = from_ruby<std::vector<size_t>>(topics);
  Rice::Data_Object<config_t>(obj)->topics = std::move(th);
}

Rice::Array get_topics(Rice::Object obj) {
  std::vector<size_t> const &topics = Rice::Data_Object<config_t>(obj)->topics;

  Rice::Array arr;
  for (size_t t : topics)
    arr.push(to_ruby<size_t>(t));

  return arr;
}

template<>
config_t from_ruby<config_t>(Rice::Object obj) {
  config_t result;
  
  result.life_time = from_ruby<size_t>(obj.call("life_time"));
  result.mutation_chance = from_ruby<double>(obj.call("mutation_chance"));
  result.population_size = from_ruby<size_t>(obj.call("population_size"));
  result.variants_count = from_ruby<size_t>(obj.call("variants_count"));
  result.questions_count = from_ruby<size_t>(obj.call("questions_count"));
  result.topics = from_ruby<std::vector<size_t>>(obj.call("topics"));

  return result;
}

template<>
Rice::Object to_ruby<config_t>(config_t const &cnf) {
  return Rice::Data_Object<config_t>(new config_t(cnf));
}

template<>
generator_t from_ruby<generator_t>(Rice::Object obj) {
  config_t config = from_ruby<config_t>(obj.call("config"));
  std::vector<topic_t> topics = from_ruby<std::vector<topic_t>>(obj.call("topics"));
  std::vector<question_t> questions = from_ruby<std::vector<question_t>>(obj.call("questions"));

  return generator_t(std::move(config), std::move(topics), std::move(questions));
}

template<>
Rice::Object to_ruby(generator_t const &t) {
  return Rice::Data_Object<generator_t>(new generator_t(t));
}

template<>
Rice::Object to_ruby<variants_t>(variants_t const &ans) {
  std::vector<std::vector<question_t>> const &questions = ans.get_questions();
  Rice::Array result;
  for (std::vector<question_t> const &arr : questions) {
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
    .define_constructor(Rice::Constructor<config_t, size_t, size_t>(),
      (Rice::Arg("variants_count") = 8, Rice::Arg("questions_count") = 8))
    .define_method("life_time=", &set_life_time)
    .define_method("mutation_chance=", &set_mutation_chance)
    .define_method("population_size=", &set_population_size)
    .define_method("variants_count=", &set_variants_count)
    .define_method("questions_count=", &set_questions_count)
    .define_method("life_time", &get_life_time)
    .define_method("mutation_chance", &get_mutation_chance)
    .define_method("population_size", &get_population_size)
    .define_method("variants_count", &get_variants_count)
    .define_method("questions_count", &get_questions_count)
    .define_method("topics", &get_topics)
    .define_method("topics=", &set_topics);

  Rice::Data_Type<topic_t> rb_ctopic = Rice::define_class_under<topic_t>(rb_mTasksGenerator, "Topic")
    .define_constructor(Rice::Constructor<topic_t, size_t, size_t, std::string>(),
      (Rice::Arg("id"), Rice::Arg("pid"), Rice::Arg("text")))
    .define_method("topic_id", &topic_t::get_topic_id)
    .define_method("parent_id", &topic_t::get_parent_id)
    .define_method("text", &topic_t::get_text);

  Rice::Data_Type<question_t> rb_cQuestion = Rice::define_class_under<question_t>(rb_mTasksGenerator, "Question")
    .define_constructor(Rice::Constructor<question_t, size_t, size_t, size_t, std::string>(),
      (Rice::Arg("id"), Rice::Arg("tid"), Rice::Arg("difficulty"), Rice::Arg("text")))
    .define_method("question_id", &question_t::get_question_id)
    .define_method("topic_id", &question_t::get_topic_id)
    .define_method("difficulty", &question_t::get_difficulty)
    .define_method("text", &question_t::get_text);

  Rice::Data_Type<generator_t> rb_cGenerator = Rice::define_class_under<generator_t>(rb_mTasksGenerator, "Generator")
    .define_constructor(Rice::Constructor<generator_t, config_t, std::vector<topic_t>, std::vector<question_t>>(),
      (Rice::Arg("cnf"), Rice::Arg("topics"), Rice::Arg("questions")))
    .define_method("generate", &generator_t::generate);
}
