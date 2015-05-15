#pragma once

#include <string>

namespace ailab {

class question_t {
  size_t question_id, topic_id, difficulty, second_level_topic_id, parent_topic_id;
  std::string text;

 public:
  question_t(size_t question_id, size_t topic_id, size_t difficulty, std::string const text = "") noexcept :
      question_id(question_id),
      topic_id(topic_id),
      difficulty(difficulty),
      second_level_topic_id(0),
      parent_topic_id(0),
      text(text) {
  }

  void set_second_level_topic_id(size_t x) noexcept {
    second_level_topic_id = x;
  }

  size_t get_second_level_topic_id() const noexcept {
    return second_level_topic_id;
  }

  void set_parent_topic_id(size_t x) noexcept {
    parent_topic_id = x;
  }

  size_t get_parent_topic_id() const noexcept {
    return parent_topic_id;
  }

  size_t get_question_id() const noexcept {
    return question_id;
  }

  size_t get_topic_id() const noexcept {
    return topic_id;
  }

  size_t get_difficulty() const noexcept {
    return difficulty;
  }

  std::string const &get_text() const noexcept {
    return text;
  }
};

}
