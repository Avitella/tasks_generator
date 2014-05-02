#pragma once

#include <vector>

#include "question.h"

#define __unsed __attribute__((unused))

namespace tasks_generator {

typedef std::vector<question_t> task_t;
typedef std::vector<task_t> individual_t;
typedef std::vector<individual_t> population_t;

typedef size_t theme_id_t;
typedef size_t question_id_t;

}
