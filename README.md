# README

## Introduction

A `dwm` dynameic window manager built by yourself.

## Depends

Install all Depends:

```
$ yay -S st
$ yay -S picom
$ yay -S dmenu
$ yay -S nerd-fonts
```

## Disposition

Edit the `$HOME/.xinitrc` file:

```sh
exec dwm
```
Add the startup script file, `$HOME/.local/share/dwm/autostart.sh`, this is my autostart.sh example:

```sh
#!/bin/bash

# disable touchpad for 0.5s while typing
syndaemon -R -i 0.5 &

# auto screen
if xrandr | grep -wq "DP1 connected"; then
	xrandr --output DP1 --mode 2560x1440 --rate 165 --primary --output eDP1 --off
fi

function if_not_exists_else_running() {
	STATUS=$(ps -C $1 --no-header | wc -l)
	echo $1 $STATUS
	if [ $STATUS -eq 0 ]; then
		$1 &
	fi
}

if_not_exists_else_running picom
if_not_exists_else_running clash
if_not_exists_else_running fcitx5
if_not_exists_else_running slstatus

feh --bg-scale $HOME/.local/share/dwm/wallpaper/jinx.jpg
```

## Some keys

The buttons below are adjusted:

```
modkey                  : Super_L

modkey + o              : open float terminal (st)
modkey + q              : kill client
modkey + +              : increase the spacing
modkey + -              : decrease the spacing
modkey + 0              : resize the spacing
modkey + r              : restart dwm

modkey + return         : open terminal (st)
modkey + shift + 0      : show all tag content
modkey + shift + return : toggles the relative position of the focal point

shift + f1              : toggle the audio switch（pipewire-pulse）
shift + f2              : increase the volume（pipewire-pulse）
shift + f3              : decrease the volume（pipewire-pulse）

shift + f5              : decrease the backlight 
shift + f6              : increase the backlight 
```
