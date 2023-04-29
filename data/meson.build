src_datadir = meson.current_source_dir()

desktop_utils = find_program('desktop-file-validate', required: false)

desktop_filename = 'neofetch-desktop.desktop.in.in'
icon_filename = 'neofetch-desktop.png'

desktop_file = i18n.merge_file(
            input: configure_file(
                           input: desktop_filename,
                           output: '@BASENAME@',
                           configuration: conf
                   ),
           output: 'neofetch-desktop.desktop',
             type: 'desktop',
           po_dir: '../po',
          install: true,
      install_dir: datadir / 'applications'
)

if desktop_utils.found()
  test('Validate desktop file', desktop_utils,
    args: [desktop_file]
  )
endif

install_data(icon_filename,
     install_dir: datadir / 'icons/hicolor/scalable/apps',
)
