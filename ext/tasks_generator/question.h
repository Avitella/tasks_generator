#pragma once

#include <string>

namespace tasks_generator {

class question_t {
  size_t question_id, theme_id, difficulty;

public:
  question_t() :
      question_id(0),
      theme_id(0),
      difficulty(0) {
  }

  question_t(size_t qid, size_t tid, size_t difficulty) :
      question_id(qid),
      theme_id(tid),
      difficulty(difficulty) {
  }

  size_t get_difficulty() const {
    return difficulty;
  }

  size_t get_question_id() const {
    return question_id;
  }

  size_t get_theme_id() const {
    return theme_id;
  }

  bool operator == (question_t const &q) const {
    return question_id == q.question_id;
  }

  static bool theme_id_cmp(question_t const &a, question_t const &b) {
    return a.theme_id < b.theme_id;
  }

  static bool difficulty_cmp(question_t const &a, question_t const &b) {
    return a.difficulty < b.difficulty;
  }

  static bool difficulty_size_t_cmp(question_t const &a, size_t d) {
    return a.difficulty < d;
  }
};

}
