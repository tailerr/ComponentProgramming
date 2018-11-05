myproject_src = files([
'main.cc' # список исходных файлов
])
thread_dep = dependency('threads')
doxyfile = configuration_data()
doxyfile.set('OUTPUT_DIRECTORY', meson.build_root())
configure_file(input: 'Doxyfile', output: 'Doxyfile',
	configuration: doxyfile)
doxygen = find_program('doxygen')
if doxygen.found()
	run_target('doc', command: [doxygen,
		join_paths(meson.build_root(), 'Doxyfile')])
endif
executable(
'Task08', # название исполняемого файла
include_directories: src, # где ищутся заголовочные файлы
sources: myproject_src, # список исходный файлов
dependencies: thread_dep, # зависимости проекта (если имеются)
c_args: ['-Wl','--no-as-needed'],
install: true # устанавливать ли файл
)
