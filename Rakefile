# coding: utf-8

require 'bundler/gem_tasks'
require 'rake/extensiontask'

spec = Gem::Specification.load("tasks_generator.gemspec")

Rake::ExtensionTask.new("tasks_generator", spec) do |ext|
  ext.lib_dir = "lib/tasks_generator"
end
