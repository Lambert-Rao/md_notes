---
title: "Arch linux"
layout: post
--- 

首先按照官方教程安装

安装常用软件

```
[root@archiso /]# pacman -S grub efibootmgr os-prober amd-ucode

[root@archiso /]# mkdir /boot/grub
[root@archiso /]# grub-mkconfig > /boot/grub/grub.cfg

[root@archiso /]# grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB

```



然后我安装了NetworkManager

之后推荐安装openssh，然后远程ssh配置

你需要clash或者其他代理软件，你需要TUN

pacman -S networkmanager git base-devel cmake xorg xorg-server 

```
pacman -S noto-fonts
yay -S noto-fonts-emoji
yay -S ttf-jetbrains-mono
```

pacman -S bat  dunst fd  flameshot gimp i3-wm i3blocks i3status  inkscape mpv neofetch neovide neovim picom polybar procs ranger ripgrep   zsh timeshift

yay -S microsoft-edge-dev-bin fcitx5  fcitx5-configtool  fcitx5-gtk  fcitx5-qt  fcitx5-rime typora 
