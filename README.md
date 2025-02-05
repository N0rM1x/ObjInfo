# ObjInfo
The mod were made using Geode SDK and CLion for C++.

<img src="logo.png" width="150" alt="ObjInfo logo" />

## For what
This mod was made mostly for creators, it provides useful information like:
- Total level`s objects count, shows you how much objects in total level has 
- Total level`s triggers count, shows you how much triggers level has
- Active objects, shows you how much objects being rendered at the time
- Active particles, shows you how much single particles being rendered at the time

And all that being displayed while you playing, directly on the level`s overlay

Also, you could manage some overlay's settings, like parameter's opacity, font size for it or y-position in overlay. All that in mod's Settings.

# Source code and build
## Getting started
I recommend heading over to [the getting started section on Geode docs](https://docs.geode-sdk.org/getting-started/) for useful info on what to do with it.

## Build instructions
For more info, see [Geode docs](https://docs.geode-sdk.org/getting-started/create-mod#build)

This mod has NO INCLUDED build folder cozof its size, you could just drop your newly created mod's build folder into project's directory.

Just open CMD, PowerShell or your terminal in mod`s directory and run this command:
```sh
# Assuming you have the Geode CLI set up already
geode build
```

**WARNING:** Geode SDK on MacOS doesn't support some stuff, which I'm using. KEEP IN MIND, IT WILL NOT BUILD. But I guess, the MOD itself will still work on MacOS.. Sorry for inconvenience...

# Resources
* [Geode SDK Documentation](https://docs.geode-sdk.org/)
* [Geode SDK Source Code](https://github.com/geode-sdk/geode/)
* [Geode CLI](https://github.com/geode-sdk/cli)
* [Bindings](https://github.com/geode-sdk/bindings/)
* [Dev Tools](https://github.com/geode-sdk/DevTools)
* [CLion by JetBrains](https://www.jetbrains.com/clion/)
