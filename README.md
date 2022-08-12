# README

## introduce

This is a dwm I built myself and it works perfectly without any conflicts.

![dwm](https://user-images.githubusercontent.com/81478335/164265284-5b3eeee1-6e15-49d3-9205-3b82872fd695.png)

You can modify all configuration here by editing the [config.def.h](./config.def.h) file.

## how to install

To start using it is very simple, you need to clone the project:

```
$ git clone https://github.com/askfiy/dwm
$ cd dwm
$ sudo make install
```

Also you should download some dependencies:

```
$ yay -S xorg-xinit feh udisks2 udiskie pcmanfm
$ yay -S archlinuxcn/nerd-fonts-agave
$ yay -S libxft-bgra
$ yay -S st (you can also use my built st)
$ yay -S picom
$ yay -S ulauncher
$ yay -S alsa-utils (Manjaro does not need to be installed)
$ yay -S nvidia-prime (Manjaro does not need to be installed)
# Recommended to use flameshot screenshot (default)
$ yay -S flameshot
# Can choose this kind of screenshot (not perfect)
$ yay -S scrot
$ yay -S xclip
```

Set udsik2 to start automatically at boot:

```
$ sudo systemctl enable udisks2
```

## how to use

If you've never used dwm, you should read this simple tutorial.

I use Manjaro Linux and after installation we have 2 options to specify how to enter dwm:

- Start with the startx command（recommend）
- In the login interface, select dwm login

### startx run dwm (manjaro)

Entering the dwm via startx is a bit more complicated, but it's so convenient that you can completely forgo mouse clicks:

First, you need to open the /etc/default/grub file and make the following changes:

```
$ sudo nvim /etc/default/grub

# GRUB_CMDLINE_LINUX_DEFAULT="quiet apparmor=1 security=apparmor udev.log_priority=3"
GRUB_CMDLINE_LINUX_DEFAULT="text"
```

Then you need to execute the command:

```
$ sudo update-grub
```

Modify the startup level:

```
$ systemctl set-default multi-user.target

// If you want to start the GUI, you should run the following command
$ systemctl set-default graphical.target
```

Back up the ~/.xinitrc file:

```
$ mv ~/.xinitrc ~/.xinitrc.bak
```

Make a copy of the xinitrc file and make changes:

```
$ cp /etc/X11/xinit/xinitrc ~/.xinitrc
```

Add the following sentence:

```
exec dwm
```

After restarting your computer and entering your username and password, you can select dwm by typing:

```
$ startx
```

### arch startx

On arch linux, using it is as simple as, if you have newly installed arch and just want to use DWM you can check it out:

```
$ nvim ~/.xinitrc
```

Added content:

```
exec dwm
```

### login interface select dwm

If you want to select dwm in the login screen and enter (like i3wm), you can create a new file dwm.desktop in the /usr/share/xsessions/ directory and enter the following:

```
$ nvim /usr/share/xsessions/dwm.desktop

[Desktop Entry]
Encoding=UTF-8
Name=Dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
```

## startup script configuration

An autostart.sh file can be created in the $HOME/.script/dwm/ directory.

This file will be executed automatically after dwm starts successfully.

About my startup script, you can get it in the [askfiy/.script](https://github.com/askfiy/.script) repository.

## status bar configuration

The default dwm startup has no status bar, I uploaded a slstatus configuration that I use, you can find it in [askfiy/slstatus](https://github.com/askfiy/slstatus).

## tag management

For the default tags, I made some application classifications, so that some applications can be assigned to different tags at startup:

```
- tag 9：picgo、clash for windows
- tag 8：wine-deepin-qq、wine-deepin-wechat
```

These software are specially set for Chinese users, if you don't like them, you can make changes in the [config.def.h](./config.def.h) file and recompile at any time.

## enable Chinese support

I found that when using wechat, if the system language is not Chinese, it will produce garbled characters.

You can add the following 1 lines of code to your ~/.zshrc or ~/.bashrc file:

```
# set to Chinese language
export LANG="zh_CN.UTF-8"
```

Note that they need to be placed before the exec dwm statement, and also need to have Chinese font support.

## some keys

My custom keys:

```
modkey = super_L
modkey + [             ： switch display device to edp01
modkey + ]             ： switch display device to dp01
modkey + return        ： start up alacritty
modkey + shift + return： switch split screen position
modkey + o             ： open floating terminal (st)
modkey + q             ： kill current focus
modkey + +             ： increase the window spacing
modkey + -             ： decrease the window spacing
modkey + shift + r     ： restart dwm without exiting dwm
modkey + shift + q     ： now, you have to double click to exit dwm
alt_l  + a             ： start taking a screenshot

shift + fn + f1 : toggle volume
shift + fn + f2 : increase volume
shift + fn + f3 : decrease volume

shift + fn + f5 : decrease screen brightness
shift + fn + f6 : increase screen brightness

shift + fn + f10 : enable touchpad
shift + fn + f11 : disable touchpad
```

The screenshot files are saved in the /tmp/ directory, you can delete them with the following command:

```
$ rm -rf /tmp/*.png
```

## Patches used

- dwm-autostart-20161205-bb3bd6f.diff
- dwm-doublepressquit-6.3.diff
- dwm-fancybar-20200423-ed3ab6b.diff
- dwm-fullgaps-toggle-20200830.diff
- dwm-hide_vacant_tags-6.3.diff
- dwm-pertag-perseltag-6.2.diff
- dwm-restartsig-20180523-6.2.diff
- dwm-scratchpad-6.2.diff
- dwm-systray-6.3.diff
- dwm-viewontag-20210312-61bb8b2.diff
