# coding utf-8

lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

require 'tasks_generator/version'

spec = Gem::Specification.new do |spec|
  spec.name          = "tasks_generator"
  spec.version       = TasksGenerator::VERSION
  spec.authors       = ["Arslan Urtashev"]
  spec.email         = ["urtashev@gmail.com"]
  spec.summary       = %q{Test Tasks Generator}
  spec.description   = %q{Test Tasks Generator for AI lab MEPhI}
  spec.homepage      = 'https://github.com/Avitella/tasks_generator'
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_runtime_dependency "bundler", "~> 1.6"
  spec.add_runtime_dependency "rake"
  spec.add_runtime_dependency "rake-compiler", ">= 0.9.5"
  spec.add_runtime_dependency "rice", ">= 1.7.0"

  spec.platform = Gem::Platform::RUBY
  spec.extensions = %w[ext/tasks_generator/extconf.rb]
end
