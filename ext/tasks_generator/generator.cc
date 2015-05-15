#include "generator.h"

#include <unordered_map>
#include <vector>

namespace ailab {

void generator_t::mark_questions(std::vector<question_t> &questions, std::vector<topic_t> const &topics) noexcept {
  std::unordered_map<size_t, size_t> topic_id_to_index;
  std::unordered_map<size_t, size_t> topic_index_to_parent_index;
  for (size_t i = 0; i < topics.size(); ++i)
    topic_id_to_index[topics[i].get_topic_id()] = i;
  for (size_t i = 0; i < topics.size(); ++i)
    if (topic_id_to_index.find(topics[i].get_parent_id()) != topic_id_to_index.end())
      topic_index_to_parent_index[i] = topic_id_to_index[topics[i].get_parent_id()];
  for (question_t &q : questions) {
    size_t topic_id = q.get_topic_id();
    if (topic_id_to_index.find(topic_id) != topic_id_to_index.end()) {
      size_t topic_index = topic_id_to_index[topic_id];
      while (true) {
        if (topic_index_to_parent_index.find(topic_index) == topic_index_to_parent_index.end())
          break;
        size_t parent_index = topic_index_to_parent_index[topic_index];
        if (topic_index_to_parent_index.find(parent_index) == topic_index_to_parent_index.end())
          break;
        topic_index = parent_index;
      }
      q.set_second_level_topic_id(topics[topic_index].get_topic_id());
    }
  }
  for (question_t &q : questions) {
    size_t topic_id = q.get_topic_id();
    if (topic_id_to_index.find(topic_id) != topic_id_to_index.end()) {
      size_t topic_index = topic_id_to_index[topic_id];
      size_t parent_topic_id = topics[topic_index].get_parent_id();
      q.set_parent_topic_id(parent_topic_id);
    }
  }
}

}
