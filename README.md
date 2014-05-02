# TasksGenerator

Test tasks generator for AI lab MEPhI

## Installation

Add this line to your application's Gemfile:

    gem 'tasks_generator'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install tasks_generator

## Usage

### TasksGenerator::Config
Config for configure Generator
* life_time - iterations count for genetic algorithm (default: 1000)
* mutation_chance - mutation chance (default: 0.05)
* population_size - starting population (default: 1000)
* tasks - tasks count
* themes - array of Theme

### TasksGenerator::Theme
Theme class for config.themes  
* theme_id
* difficulty_min
* difficulty_max

### TasksGenerator::Question
Question class for questions in Generator constructor
* question_id
* theme_id
* difficulty

### TasksGenerator::Generator
Test tasks generator
* generate() - this method returns array of questions

## Contributing

1. Fork it ( https://github.com/Abitella/tasks_generator/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request
