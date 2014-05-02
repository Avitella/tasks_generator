#pragma once

#include "function.h"
#include "question.h"
#include "types.h"

namespace tasks_generator {

class generator_t {
  config_t config;
  std::vector<question_t> questions;

public:
  typedef std::vector<std::vector<question_t>> answer_t;

  generator_t(generator_t const &t) :
      config(t.config),
      questions(t.questions) {
  }

  generator_t(config_t const &config, std::vector<question_t> const &questions) :
      config(config),
      questions(questions) {
  }

  generator_t(config_t &&config, std::vector<question_t> &&questions) :
      config(config),
      questions(std::move(questions)) {
  }

  config_t get_config() const {
    return config;
  }

  std::vector<question_t> const &get_questions() const {
    return questions;
  }

  answer_t generate() const;
};

}
