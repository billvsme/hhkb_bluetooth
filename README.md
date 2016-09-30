# hhkb_bluetooth
hhkb 蓝牙改造项目，本着尽量简单，少改动，少焊接，可以恢复的原则，提供2种方案。方法一其实就是一个usb转蓝牙模块，方法二真正的改造，把arduino作为主板

## 方案一
本质就是一个usb转蓝牙模块  
**材料**  

1. arduino uno
2. usb host shield 2.0
3. XM-04-HID-K (购买时候请搜索XM-04-HID-S，然后询问卖家需要XM-04-HID-K😂, 并且问他文档)

**连接图**  
**效果图**  

正常连接后，写入运行即可，是不是非常简单 😂,但是只是相当于做了一个蓝牙转化器。可以一步一步来。

## 方案二
**材料**  

1. arduino nano
2. B13B ZR
3. XM-04-HID-K
4. 迷你充电宝

**连接图**  
**效果图**  

把原本连接在hhkb主板上的线，连到ardunio上，ardunio解析后发送给蓝牙HID模块。
hhkb连接线参考: https://github.com/tmk/tmk_keyboard/blob/master/keyboard/hhkb/doc/HHKB.txt
