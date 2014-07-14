#pragma once

#include "question.h"

namespace tasks_generator {

class theme_t {
  size_t theme_id, parent_id;
  size_t difficulty_min, difficulty_max;

 public:
  theme_t(size_t tid, size_t pid, size_t dmin, size_t dmax) :
      theme_id(tid),
      parent_id(pid),
      difficulty_min(dmin),
      difficulty_max(dmax) {
  }

  theme_t(theme_t const &th) :
      theme_id(th.theme_id),
      parent_id(th.parent_id),
      difficulty_min(th.difficulty_min),
      difficulty_max(th.difficulty_max) {
  }

  size_t get_theme_id() const {
    return theme_id;
  }

  size_t get_difficulty_min() const {
    return difficulty_min;
  }

  size_t get_difficulty_max() const {
    return difficulty_max;
  }

  size_t get_parent_id() const {
    return parent_id;
  }

  bool operator == (theme_t const &t) const {
    return theme_id == t.theme_id &&
      parent_id == t.parent_id &&
      difficulty_min == t.difficulty_min &&
      difficulty_max == t.difficulty_max;
  }
};

}
