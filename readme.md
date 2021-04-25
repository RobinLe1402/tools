# RobinLe Tools
This is a collection of small Windows tools I created.



## FilenameFriendlyClipboard
Changes the clipboard (if the current content is text compatible) to be usable as a filename under Microsoft Windows.

This is achieved by substituting disallowed characters by similar looking characters.

### Conversion table
```
/	-->	／
\	-->	＼
:	-->	：
*	-->	＊
?	-->	？
"	-->	''
<	-->	＜
>	-->	＞
|	-->	｜
```


## StartupDelete
Clears one directory based on the call parameters.
The idea is to have a directory that gets deleted on every computer startup - you can achieve this by creating a link to the programm in your computer's autostart folder (*%AppData%\Microsoft\Windows\Start Menu\Programs\Startup*).

### Syntax
```
StartupDelete.exe <Directory>
```
So a call could look like this:
```
StartupDelete.exe C:\TEMP
```
