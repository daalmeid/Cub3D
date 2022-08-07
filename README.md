# Cub3D
Creation of a "realistic" 3D maze using a 2D map and Raycasting.

### How to use it (WSL 2 steps, it should work fine using make on Linux):

First of all, you will need to install XMing. You can do so by following the next few steps (taken from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#getting-a-screen-on-windows-10-wsl2):

Install [XMing](https://sourceforge.net/projects/xming/), just keep clicking next, the defaults will do. After installing, you will see a little XMing icon in your icon tray. Now exit XMing, and open XLaunch, proceed with the following steps:
* Click Multiple windows and go to the next page;
* Click Start no client and go to the next page;
* Make sure that the No Access Control box is ticked and go to the next page;
* Click Save configuration and then Finish.

After XLaunch is up and runnig, run the following commands in your terminal:

```
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
```
followed by:
```
make
```
then run **./Cub3D**.
