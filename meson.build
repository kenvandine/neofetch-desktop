project('neofetch-desktop', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

i18n = import('i18n')

bin_name = 'neofetch-desktop'
prefix = get_option('prefix')
bindir = prefix / get_option('bindir')
datadir = prefix / get_option('datadir')
pkgdatadir = datadir / bin_name

config_h = configuration_data()
config_h.set_quoted('DATA_DIR', pkgdatadir)
configure_file(output: 'config.h', configuration: config_h)

executable('neofetch-desktop',
           'src/neofetch-desktop.c',
           include_directories : include_directories('.'),
           dependencies : [
              dependency('vte-2.91-gtk4'),
              dependency('gtk4')],
           install : true)

conf = configuration_data()
conf.set('BIN_DIR', prefix / bindir)
conf.set('BIN_NAME', bin_name)
subdir('data')
