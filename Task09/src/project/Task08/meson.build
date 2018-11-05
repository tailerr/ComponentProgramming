myproject_src = files([
'main.cc' # список исходных файлов
])
thread_dep = dependency('threads')
executable(
'Task08', # название исполняемого файла
include_directories: src, # где ищутся заголовочные файлы
sources: myproject_src, # список исходный файлов
dependencies: thread_dep, # зависимости проекта (если имеются)
c_args: ['-Wl','--no-as-needed'],
install: true # устанавливать ли файл
)
