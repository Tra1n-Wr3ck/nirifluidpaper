# Maintainer: Your Name <your.email@example.com>
pkgname=nirifluidpaper
pkgver=0.1.0
pkgrel=1
pkgdesc="Interactive WebGL fluid wallpaper for Niri Wayland compositor"
arch=('x86_64')
url="https://github.com/yourusername/nirifluidpaper"
license=('MIT')
depends=('gtk4' 'gtk4-layer-shell' 'webkitgtk-6.0')
makedepends=('meson' 'ninja' 'gcc')
source=("$pkgname-$pkgver.tar.gz::$url/archive/v$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$pkgname-$pkgver"
    arch-meson build
    ninja -C build
}

package() {
    cd "$pkgname-$pkgver"
    DESTDIR="$pkgdir" ninja -C build install
    install -Dm644 README.md "$pkgdir/usr/share/doc/$pkgname/README.md"
}
