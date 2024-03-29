require 'open3'
require 'fileutils'

env = {
    BUILD_DIR: "build",
    CC: "gcc",
    LDFLAGS: [],
    CPPPATH: [],
    SRC: [],
    OBJ: [],
}

stdout, stderr, status = Open3.capture3("pkg-config --libs glew")
env[:LDFLAGS] += stdout.split(" ")

stdout, stderr, status = Open3.capture3("pkg-config --libs freetype2")
env[:LDFLAGS] += stdout.split(" ")

env[:LDFLAGS] << "-lglut"

env[:CPPPATH] = [
    "src/",
    "src/card",
    "src/cardset",
    "src/deck",
    "src/solitaire",
    "src/suit"
]

stdout, stderr, status = Open3.capture3("pkg-config --cflags freetype2")
env[:CPPPATH] += stdout.gsub("-I", "").split(" ")

env[:SRC] = [
    "src/main.c",
    "src/card/card.c",
    "src/cardset/cardset.c",
    "src/deck/deck.c",
    "src/solitaire/solitaire.c",
    "src/suit/suit.c"
]

FileUtils.rm_rf(env[:BUILD_DIR])

env[:SRC].each do |src|
  obj = File.join(env[:BUILD_DIR], src.sub(/\.c$/, ".o"))
  env[:OBJ] << obj

  cmd = [
    env[:CC],
    env[:CPPPATH].map {|p| "-I#{p}"},
    "-c",
    src,
    "-o",
    obj
  ]

  FileUtils.mkdir_p(File.dirname(obj))
  system(*cmd.flatten)
end

cmd = [
    env[:CC],
    env[:OBJ],
    env[:LDFLAGS],
    "-o",
    File.join(env[:BUILD_DIR], "card_game")
]
system(*cmd.flatten)