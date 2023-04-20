<h1 align="center">
  <img src="https://avatars1.githubusercontent.com/u/29598503?v=3&s=256" alt="[Project]">
  <br />
  ch32v00x SDK
</h1>

<p align="center"><b>This is the snap for the ch32v00x SDK</b>, <i>“All the tools to build an embedded app on wch chipsets”</i>. It works on Ubuntu, Fedora, Debian, and other major Linux distributions.</p>

<!-- Uncomment and modify this when you are provided a build status badge
<p align="center">
<a href="https://snapcraft.io/ch32v00x">
  <img alt="enpass" src="https://snapcraft.io/ch32v00x/badge.svg" />
</a>
<a href="https://snapcraft.io/ch32v00x">
  <img alt="enpass" src="https://snapcraft.io/ch32v00x/trending.svg?name=0" />
</a>
</p>
-->

<!-- Uncomment and modify this when you have a screenshot
![ch32v00x](screenshot.png?raw=true "ch32v00x")
-->

<p align="center">Published for <img src="https://raw.githubusercontent.com/anythingcodes/slack-emoji-for-techies/gh-pages/emoji/tux.png" align="top" width="24" /> with 💝 by Snapcrafters</p>

<!-- Uncomment and modify this when your snap is available on the store
[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-white.svg)](https://snapcraft.io/ch32v00x)
-->

([Don't have snapd installed?](https://snapcraft.io/docs/core/install))

## Install

    sudo snap install ch32v00x

The snap requires the following permissions (interfaces):

 - `home` to access the source to be compiled and copy the output there;
 - `network-bind` to bind a socket for GDB (openocd only);
 - `hardware-observe` and `raw-usb` to access the WCHLink hardware (openocd only).

Once installed, all the compilation works out-of-the-box. To use openocd, however, the snap need to be granted access to `hardware-observe` and `raw-usb` as those interfaces are not connected by default. It can be achieved by running:

```bash
snap connect ch32v00x:hardware-observe
snap connect ch32v00x:raw-usb
```

Moreover, to allow access to the WCHLink hardware without superuser permissions, it is necessary to setup `udev` rules.

This can be achieved through the convenience script `ch32v00x.setup-udev` like:

```bash
ch32v00x.setup-udev | sudo sh -
```

Please, **review** the output of `ch32v00x.setup-udev` before runnnig it through a  priviledged shell.

As a last note, snap apparently doesn't support names containing a `+` character (!?) so `c++`, `c++filt` and `g++` have been renamed respectively `cplusplus`, `cplusplusfilt` and
`gplusplus`.

### WCH library

This snap includes a library (`libwch`) and a link script to remove the complexity of rebuilding every time the library. 

The library has been reworked both to improve few obscure points and to make it possible to package all the functionality. It also comes with all the requried `syscall` implementations, so that it is not necessary anymore to link against `libgloss` or `libnosys`. There are plans to port some of those changes to newlib to remove some overhead.

Some headers changed name (`misc.h -> nvic.h` and `debug.h -> sysclk.h`) to a little bit more semantic one. Moreover, all headers can be found in the `ch32v00x` folder, to avoid possible name clashes.

#### LTO support

`libwch` is built with LTO support. This allows to shrink the size of a binary, simply adding the `-flto` flag to the compilation/linking commands. It should be noted that this is independent from the usual `-fdata-sections -ffunction-sections`/`--gc-sections`.

### Examples

This snaps includes a command to explore the examples found in the original SDK: `ch32v00x.example`.

`ch32v00x.example` has mainly two modes:

 - source output (`ch32v00x.example <example-name>`) which just outputs the source code;
 - compilation (`ch32v00x.example -c <example-name> [-o <output-name>]`) which will compile the example.

`ch32v00x.example` includes a comp script to easily list/complete the different example names.

All examples are reworked to comply with the changes made to the original WCH library (mainly for packagin purposes).

### Convenience specs

The compilation suggested by WCH (and distributed with MRS) is rather complex, requires a rather big `Makefile` and forces recompilation of the SDK on every build.

While it is possible to do that with this snap as well, the latter contains a pre-built SDK and a spec file that takes care of all those details.

It is enough for most purposes to run

```bash
ch32v00x.gcc my-source.c --specs=ch32v00x.specs -o my-binary.elf
```

to obtain the same result as the Makefile.

## Remaining tasks
<!-- Uncomment and modify this when you have a screenshot
![ch32v00x](screenshot.png?raw=true "ch32v00x")
-->

Snapcrafters ([join us](https://forum.snapcraft.io/t/snapcrafters-reboot/24625)) are working to land snap install documentation and the [snapcraft.yaml](https://github.com/snapcrafters/fork-and-rename-me/blob/master/snap/snapcraft.yaml) upstream so [Project] can authoritatively publish future releases.

  - [x] Click the green "Use this template" button above to create a new repository based on this template
  - [x] Give the newly created repository a sensible name, like `godzilla` if you're snapping the Godzilla software (*Note: Do not use `snap` in this name.*)
  - [x] Update the description of the repository to `Unofficial snap for [Project]`
  - [x] Update logos and references to `[Project]` and `[my-snap-name]`
  - [x] Create a snap that runs in `devmode`
  - [x] Convert the snap to `strict` confinement, or `classic` confinement if it qualifies
  - [x] Register the snap in the store, **using the preferred upstream name**
  - [ ] Add a screenshot to this `README.md`
  - [ ] Add install instructions to this `README.md`
  - [ ] Update snap store metadata, icons and screenshots
  - [ ] Publish the confined snap in the Snap store beta channel
  - [ ] Update the install instructions in this `README.md`
  - [ ] Post a call for testing in the Snapcraft Forum ["Snapcrafters" category](https://forum.snapcraft.io/c/snapcrafters/23) - [link]()
  - [ ] Add the Snapcraft store account (snap-advocacy@canonical.com) as a collaborator to your snap in the [Dashboard](https://dashboard.snapcraft.io) and ask a [Snapcrafters admin](https://github.com/orgs/snapcrafters/people?query=%20role%3Aowner) to accept this request
  - [ ] Fix all important issues found during testing
  - [ ] Make a post in the Snapcraft Forum ["store-requests" category](https://forum.snapcraft.io/c/store-requests/19) asking for a transfer of the snap name from you to Snapcrafters - [link]()
  - [ ] Ask a [Snapcrafters admin](https://github.com/orgs/snapcrafters/people?query=%20role%3Aowner) to fork your repo into github.com/snapcrafters, and configure the repo for automatic publishing into edge on commit
  - [ ] Add the provided Snapcraft build badge to this `README.md`
  - [ ] Publish the snap in the Snap store stable channel
  - [ ] Update the install instructions in this `README.md`
  - [ ] Post an announcement in the Snapcraft Forum ["Snapcrafters" category](https://forum.snapcraft.io/c/snapcrafters/23) - [link]()
  - [ ] Ask the Snap Advocacy team to celebrate the snap - [link]()
  - [ ] Submit a pull request or patch upstream that adds snap install documentation - [link]()
  - [ ] Ask upstream if they are interested in maintaining the Snap. If they are:
    - [ ] Fork the upstream project, add the snap build files and required assets/launchers to that repo and submit a pull request or patch - [link]()
    - [ ] Add upstream contact information to the `README.md`
    - If upstream accept the PR:
      - [ ] Request upstream create a Snap store account
      - [ ] Add upstream account as a collaborator on the snap
      - [ ] Contact the Snap Advocacy team to request the snap be transferred to upstream

If you have any questions, [post in the Snapcraft forum](https://forum.snapcraft.io).


<!--
## The Snapcrafters

| [![Your Name](https://gravatar.com/avatar/bc0bced65e963eb5c3a16cab8b004431/?s=128)](https://github.com/yourname/) |
| :---: |
| [Your Name](https://github.com/yourname/) |
--> 

<!-- Uncomment and modify this when you have upstream contacts
## Upstream

| [![Upstream Name](https://gravatar.com/avatar/bc0bced65e963eb5c3a16cab8b004431?s=128)](https://github.com/upstreamname) |
| :---: |
| [Upstream Name](https://github.com/upstreamname) |
-->
