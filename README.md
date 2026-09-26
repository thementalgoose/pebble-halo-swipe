# Halo Swipe

<p>
</p>

Simple pebble watchface inspired by the OG Time 2 kickstarter videos

| Codename | Pebble name       | Watchface                                               |
|----------|-------------------|---------------------------------------------------------|
| aplite   | Pebble            | <img src="appstore/basalt/watchface.png" width="120"/>  |
| basalt   | Pebble Time       | <img src="appstore/basalt/watchface.png" width="120"/>  |
| chalk    | Pebble Time Round | <img src="appstore/chalk/watchface.png" width="120"/>   |
| diorite  | Pebble 2          | <img src="appstore/diorite/watchface.png" width="120"/> |
| emery    | Pebble Time 2     | <img src="appstore/emery/watchface.png" width="150"/>   |
| flint    | Pebble 2 Duo      | <img src="appstore/flint/watchface.png" width="120"/>   |
| gabbro   | Pebble Round 2    | <img src="appstore/gabbro/watchface.png" width="150"/>  |

### Currently supported

- [x] Adaptive to all supported pebble sizes
- [x] Configure the color of the background halo
- [x] Configure the color of the minute halo
- [x] Configure the color of the hands individually
- [x] Configure the health line

#### Building

- Python 3.10.x required

```bash
# Booting the emulator
pebble install --emulator flint

# Building
pebble build

# Running
pebble install
pebble install --cloudpebble 
pebble install --emulator flint --logs
```

#### Useful Links

- [Hardware information](https://developer.rebble.io/guides/tools-and-resources/hardware-information/)
- [UI Samples](https://github.com/pebble-examples/ui-patterns/)
- [Modular Architecture](https://github.com/pebble-examples/modular-app-example/blob/master/src/windows/main_window.h)
- [Best Practices](https://developer.rebble.io/guides/best-practices/modular-app-architecture/)
