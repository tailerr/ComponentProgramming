myproject_src = files([
'client.cc' # список исходных файлов
])
executable(
'Client', # название исполняемого файла
include_directories: src, # где ищутся заголовочные файлы
sources: myproject_src, # список исходный файлов
dependencies: [], # зависимости проекта (если имеются)
install: true # устанавливать ли файл
)
myproject_src1 = files([
'server.cc' # список исходных файлов
])
executable(
'Server', # название исполняемого файла
include_directories: src, # где ищутся заголовочные файлы
sources: myproject_src1, # список исходный файлов
dependencies: [], # зависимости проекта (если имеются)
install: true # устанавливать ли файл
)

myproject_src2 = files([
'block_server.cc' # список исходных файлов
])
executable(
'Block_Server', # название исполняемого файла
include_directories: src, # где ищутся заголовочные файлы
sources: myproject_src2, # список исходный файлов
dependencies: [], # зависимости проекта (если имеются)
install: true # устанавливать ли файл
)
