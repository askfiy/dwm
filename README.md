This is my own compiled dwm.

No conflict, some patches installed:

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

You need to install some dependencies:

```
yay -S xorg-xinit feh udisks2 udiskie pcmanfm
yay -S archlinuxcn/nerd-fonts-agave
yay -S libxft-bgra
yay -S noto-fonts-emoji
yay -S alacritty-git
yay -S ulauncher
yay -S st
```

Set udisk2 to boot on boot:

```
sudo systemctl enable udisks2
```

After the download is complete, simply run the following command to install DWM:

```
sudo make clean install
```

You can write a startup script，This script is automatically executed after the DWM is loaded:

```
$HOME/.script/dwm/autostart.sh
```
