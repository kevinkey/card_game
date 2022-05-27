require "fileutils"



paths = []

Dir["**/*.h"].each do |header|
    paths << File.dirname(header)
end

paths.uniq!

objects = []

Dir["**/*.cpp"].each do |src|
  o = "Build/obj/#{File.basename(src, ".cpp")}.o"
  objects << o

  FileUtils.mkdir_p(File.dirname(o))
  compile = ["g++", "-c"] + paths.map {|p| "-I#{p}"} + [src, "-o", o]

  system(*compile)
end

system(*(["g++", "-o", "test"] + objects))

