project('neofetch-desktop', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

executable('neofetch-desktop',
           'src/neofetch-desktop.c',
           dependencies : [
              dependency('vte-2.91-gtk4'),
              dependency('gtk4')],
           install : true)
