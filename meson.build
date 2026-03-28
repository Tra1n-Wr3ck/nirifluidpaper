project('nirifluidpaper', 'c',
    version: '0.1.0',
    default_options: ['warning_level=2', 'werror=false', 'optimization=2']
)

executable('nirifluidpaper',
    'src/main.c',
    dependencies: [
        dependency('gtk4'),
        dependency('gtk4-layer-shell-0'),
        dependency('webkitgtk-6.0'),
    ],
    install: true,
)

install_data('systemd/nirifluidpaper.service', install_dir: get_option('libdir') / 'systemd' / 'user')
